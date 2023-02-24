/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Copyright (C) 2016 Intel Corporation.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qplatformdefs.h"

#include "qcoreapplication.h"
#include "qpair.h"
#include "qsocketnotifier.h"
#include "qthread.h"
#include "qelapsedtimer.h"

#include "qeventdispatcher_amiga_p.h"

#include <private/qthread_p.h>
#include <private/qcoreapplication_p.h>
#include <private/qcore_unix_p.h>

#include <proto/intuition.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef QT_NO_EVENTFD
#  include <sys/eventfd.h>
#endif

#include <proto/bsdsocket.h>

QT_BEGIN_NAMESPACE

static const char *socketType(QSocketNotifier::Type type)
{
    switch (type) {
    case QSocketNotifier::Read:
        return "Read";
    case QSocketNotifier::Write:
        return "Write";
    case QSocketNotifier::Exception:
        return "Exception";
    }

    Q_UNREACHABLE();
}

QEventDispatcherAMIGAPrivate::QEventDispatcherAMIGAPrivate()
{
    printf("Creating EventDispatcherPrivate.\n");
    timerPort = (struct MsgPort *)IExec->AllocSysObjectTags(ASOT_PORT, TAG_END);
    if(timerPort == 0) {
        qWarning("Failed to allocate message port for timer.device communication. Exit.\n");
        QCoreApplication::quit();
    }
    timerRequest = (struct TimeRequest *)IExec->AllocSysObjectTags(ASOT_IOREQUEST,
        ASOIOR_Size, sizeof(struct TimeRequest),
        ASOIOR_ReplyPort, timerPort,
        TAG_END);
    if(!timerRequest) {
        qWarning("Failed to allocate message structure for timer.device communication. Exit.\n");
        QCoreApplication::quit();
    }
    unsigned int error = IExec->OpenDevice("timer.device", UNIT_MICROHZ, (struct IORequest *)timerRequest, 0);
    if(error) {
        qWarning("Error opening timer.device for communication. Exit.\n");
        QCoreApplication::quit();
    }
    wakeupSignal = IExec->AllocSignal(-1);
    me = IExec->FindTask(0);
}

QEventDispatcherAMIGAPrivate::~QEventDispatcherAMIGAPrivate()
{
    IExec->CloseDevice ((IORequest *)timerRequest);
    IExec->FreeSysObject(ASOT_IOREQUEST, timerRequest);
    IExec->FreeSysObject(ASOT_PORT, timerPort);
    IExec->FreeSignal(wakeupSignal);
    // cleanup timers
    qDeleteAll(timerList);
}

int QEventDispatcherAMIGAPrivate::activateTimers()
{
    return timerList.activateTimers();
}


QEventDispatcherAMIGA::QEventDispatcherAMIGA(QObject *parent)
    : QAbstractEventDispatcher(*new QEventDispatcherAMIGAPrivate, parent)
{ }

QEventDispatcherAMIGA::QEventDispatcherAMIGA(QEventDispatcherAMIGAPrivate &dd, QObject *parent)
    : QAbstractEventDispatcher(dd, parent)
{ }

QEventDispatcherAMIGA::~QEventDispatcherAMIGA()
{ }

void QEventDispatcherAMIGAPrivate::setSocketNotifierPending(QSocketNotifier *notifier)
{
    Q_ASSERT(notifier);

    if (pendingNotifiers.contains(notifier))
        return;

    pendingNotifiers << notifier;
}

void QEventDispatcherAMIGAPrivate::markPendingSocketNotifiers()
{
    for (const pollfd &pfd : qAsConst(pollfds)) {
        if (pfd.fd < 0 || pfd.revents == 0)
            continue;

        auto it = socketNotifiers.find(pfd.fd);
        Q_ASSERT(it != socketNotifiers.end());

        const QSocketNotifierSetUNIX &sn_set = it.value();

        static const struct {
            QSocketNotifier::Type type;
            short flags;
        } notifiers[] = {
            { QSocketNotifier::Read,      POLLIN  | POLLHUP | POLLERR },
            { QSocketNotifier::Write,     POLLOUT | POLLHUP | POLLERR },
            { QSocketNotifier::Exception, POLLPRI | POLLHUP | POLLERR }
        };

        for (const auto &n : notifiers) {
            QSocketNotifier *notifier = sn_set.notifiers[n.type];

            if (!notifier)
                continue;

            if (pfd.revents & POLLNVAL) {
                qWarning("QSocketNotifier: Invalid socket %d with type %s, disabling...",
                         it.key(), socketType(n.type));
                notifier->setEnabled(false);
            }

            if (pfd.revents & n.flags)
                setSocketNotifierPending(notifier);
        }
    }

    pollfds.clear();
}

int QEventDispatcherAMIGAPrivate::activateSocketNotifiers()
{
    qInfo() << "activateSocketNotifiers";
    markPendingSocketNotifiers();
    qInfo() << "check(1)";

    if (pendingNotifiers.isEmpty()) {
        qInfo() << "pendingNotifiers is empty";
        return 0;
    }

    int n_activated = 0;
    QEvent event(QEvent::SockAct);

    while (!pendingNotifiers.isEmpty()) {
        QSocketNotifier *notifier = pendingNotifiers.takeFirst();
        qInfo() << "send QEvent::SockAct";
        QCoreApplication::sendEvent(notifier, &event);
        ++n_activated;
    }

    return n_activated;
}

void QEventDispatcherAMIGA::registerSocketNotifier(QSocketNotifier *notifier)
{
    Q_ASSERT(notifier);
    int sockfd = notifier->socket();
    QSocketNotifier::Type type = notifier->type();
#if 1 //ndef QT_NO_DEBUG
    if (notifier->thread() != thread() || thread() != QThread::currentThread()) {
        qWarning("QSocketNotifier: socket notifiers cannot be enabled from another thread");
        return;
    }
#endif

    Q_D(QEventDispatcherAMIGA);
    QSocketNotifierSetUNIX &sn_set = d->socketNotifiers[sockfd];

    if (sn_set.notifiers[type] && sn_set.notifiers[type] != notifier)
        qWarning("%s: Multiple socket notifiers for same socket %d and type %s",
                 Q_FUNC_INFO, sockfd, socketType(type));

    sn_set.notifiers[type] = notifier;
}

void QEventDispatcherAMIGA::unregisterSocketNotifier(QSocketNotifier *notifier)
{
    Q_ASSERT(notifier);
    int sockfd = notifier->socket();
    QSocketNotifier::Type type = notifier->type();
#ifndef QT_NO_DEBUG
    if (notifier->thread() != thread() || thread() != QThread::currentThread()) {
        qWarning("QSocketNotifier: socket notifier (fd %d) cannot be disabled from another thread.\n"
                "(Notifier's thread is %s(%p), event dispatcher's thread is %s(%p), current thread is %s(%p))",
                sockfd,
                notifier->thread() ? notifier->thread()->metaObject()->className() : "QThread", notifier->thread(),
                thread() ? thread()->metaObject()->className() : "QThread", thread(),
                QThread::currentThread() ? QThread::currentThread()->metaObject()->className() : "QThread", QThread::currentThread());
        return;
    }
#endif

    Q_D(QEventDispatcherAMIGA);

    d->pendingNotifiers.removeOne(notifier);

    auto i = d->socketNotifiers.find(sockfd);
    if (i == d->socketNotifiers.end())
        return;

    QSocketNotifierSetUNIX &sn_set = i.value();

    if (sn_set.notifiers[type] == nullptr)
        return;

    if (sn_set.notifiers[type] != notifier) {
        qWarning("%s: Multiple socket notifiers for same socket %d and type %s",
                 Q_FUNC_INFO, sockfd, socketType(type));
        return;
    }

    sn_set.notifiers[type] = nullptr;

    if (sn_set.isEmpty())
        d->socketNotifiers.erase(i);
}

/*!
    \internal
*/
void QEventDispatcherAMIGA::registerTimer(int timerId, qint64 interval, Qt::TimerType timerType, QObject *obj)
{
    Q_D(QEventDispatcherAMIGA);
    d->timerList.registerTimer(timerId, interval, timerType, obj);
}

/*!
    \internal
*/
bool QEventDispatcherAMIGA::unregisterTimer(int timerId)
{
    Q_D(QEventDispatcherAMIGA);
    return d->timerList.unregisterTimer(timerId);
}

/*!
    \internal
*/
bool QEventDispatcherAMIGA::unregisterTimers(QObject *object)
{
    Q_D(QEventDispatcherAMIGA);
    return d->timerList.unregisterTimers(object);
}

QList<QEventDispatcherAMIGA::TimerInfo>
QEventDispatcherAMIGA::registeredTimers(QObject *object) const
{
    if (!object) {
        qWarning("QEventDispatcherAMIGA:registeredTimers: invalid argument");
        return QList<TimerInfo>();
    }

    Q_D(const QEventDispatcherAMIGA);
    return d->timerList.registeredTimers(object);
}

#define QT_POLL_READ_MASK   (POLLIN | POLLRDNORM)
#define QT_POLL_WRITE_MASK  (POLLOUT | POLLWRNORM | POLLWRBAND)
#define QT_POLL_EXCEPT_MASK (POLLPRI | POLLRDBAND)
#define QT_POLL_ERROR_MASK  (POLLERR | POLLNVAL)
#define QT_POLL_EVENTS_MASK (QT_POLL_READ_MASK | QT_POLL_WRITE_MASK | QT_POLL_EXCEPT_MASK)

static inline int qt_poll_prepare(struct pollfd *fds, nfds_t nfds,
                                  fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
    int max_fd = -1;

    FD_ZERO(read_fds);
    FD_ZERO(write_fds);
    FD_ZERO(except_fds);

    for (nfds_t i = 0; i < nfds; i++) {
        if (fds[i].fd >= FD_SETSIZE) {
            errno = EINVAL;
            return -1;
        }

        if ((fds[i].fd < 0) || (fds[i].revents & QT_POLL_ERROR_MASK))
            continue;

        if (fds[i].events & QT_POLL_READ_MASK)
            FD_SET(fds[i].fd, read_fds);

        if (fds[i].events & QT_POLL_WRITE_MASK)
            FD_SET(fds[i].fd, write_fds);

        if (fds[i].events & QT_POLL_EXCEPT_MASK)
            FD_SET(fds[i].fd, except_fds);

        if (fds[i].events & QT_POLL_EVENTS_MASK)
            max_fd = qMax(max_fd, fds[i].fd);
    }

    return max_fd + 1;
}

static inline void qt_poll_examine_ready_read(struct pollfd &pfd)
{
    int res;
    char data;

    // EINTR_LOOP(res, ::recv(pfd.fd, &data, sizeof(data), MSG_PEEK));
    int err = 0;
    res =  ISocket->recv(pfd.fd, &data, sizeof(data), MSG_PEEK);
    ISocket->SocketBaseTags(SBTM_GETREF(SBTC_ERRNO), &err, TAG_END);
    const int error = (res < 0) ? err : 0;

    if (res == 0) {
        pfd.revents |= POLLHUP;
    } else if (res > 0 || error == ENOTSOCK || error == ENOTCONN) {
        pfd.revents |= QT_POLL_READ_MASK & pfd.events;
    } else {
        switch (error) {
        case ESHUTDOWN:
        case ECONNRESET:
        case ECONNABORTED:
        case ENETRESET:
            pfd.revents |= POLLHUP;
            break;
        default:
            pfd.revents |= POLLERR;
            break;
        }
    }
}

static inline int qt_poll_sweep(struct pollfd *fds, nfds_t nfds,
                                fd_set *read_fds, fd_set *write_fds, fd_set *except_fds)
{
qInfo() << "qt_poll_sweep";
    int result = 0;

    for (nfds_t i = 0; i < nfds; i++) {
        if (fds[i].fd < 0)
            continue;

        if (FD_ISSET(fds[i].fd, read_fds))
            qt_poll_examine_ready_read(fds[i]);
            // fds[i].revents |= QT_POLL_READ_MASK & fds[i].events;

        if (FD_ISSET(fds[i].fd, write_fds))
            fds[i].revents |= QT_POLL_WRITE_MASK & fds[i].events;

        if (FD_ISSET(fds[i].fd, except_fds))
            fds[i].revents |= QT_POLL_EXCEPT_MASK & fds[i].events;

        if (fds[i].revents != 0)
            result++;
    }

    return result;
}

/*****************************************************************************
 QEventDispatcherAMIGA implementations for AMIGAAAAAAAAAA.....!!
 *****************************************************************************/


bool QEventDispatcherAMIGA::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    Q_D(QEventDispatcherAMIGA);
    d->interrupt.storeRelaxed(0);

    // we are awake, broadcast it
    emit awake();

    auto threadData = d->threadData.loadRelaxed();
    QCoreApplicationPrivate::sendPostedEvents(nullptr, 0, threadData);

    const bool include_timers = (flags & QEventLoop::X11ExcludeTimers) == 0;
    const bool include_notifiers = (flags & QEventLoop::ExcludeSocketNotifiers) == 0;
    const bool wait_for_events = (flags & QEventLoop::WaitForMoreEvents) != 0;

    const bool canWait = (threadData->canWaitLocked()
                          && !d->interrupt.loadRelaxed()
                          && wait_for_events);

    if (canWait)
        emit aboutToBlock();

    if (d->interrupt.loadRelaxed())
        return false;

    // timespec *tm = nullptr;
    struct timeval *tm = nullptr;
    struct TimeVal wait_tm = { 0, 0 };

    unsigned int listenSignals = 0;
    if (!canWait || (include_timers && d->timerList.timerWait(wait_tm))) {
//         d->timerRequest->Request.io_Command = TR_ADDREQUEST;
//         d->timerRequest->Time = wait_tm;

// //        printf("Sending IO Request to timer.device. Seconds : %lu , Microseconds : %lu\n", wait_tm.Seconds, wait_tm.Microseconds);

//         IExec->SendIO((struct IORequest *)d->timerRequest);
//         listenSignals |= 1 << d->timerPort->mp_SigBit;

        tm = (struct timeval*)&wait_tm;
    }

    listenSignals |= 1 << d->wakeupSignal;

    fd_set read_fds, write_fds, except_fds;

    d->pollfds.clear();
    d->pollfds.reserve(1 + (include_notifiers ? d->socketNotifiers.size() : 0));

    if (include_notifiers)
        for (auto it = d->socketNotifiers.cbegin(); it != d->socketNotifiers.cend(); ++it)
            d->pollfds.append(qt_make_pollfd(it.key(), it.value().events()));

    // This must be last, as it's popped off the end below
    // d->pollfds.append(d->threadPipe.prepare());

    int nevents = 0;

#if 0
    unsigned int caughtSignals = IExec->Wait(listenSignals);
#elif 1
    int max_fd = qt_poll_prepare(d->pollfds.data(), d->pollfds.size(), &read_fds, &write_fds, &except_fds);
    int error = 0;
    int numfds;
    do {
        // timeval tv = {1, 0};
        // if(!tm) tm = &tv;
// qInfo() << "Calling WaitSelect, max_fd == " << max_fd;
        // int numfds = waitselect(max_fd, &read_fds, &write_fds, &except_fds, tm, &listenSignals);
        numfds = ISocket->WaitSelect(max_fd, &read_fds, &write_fds, &except_fds, tm, (ULONG*)&listenSignals);

// qInfo() << "WaitSelect returned : " << numfds;
        if(numfds < 0 ) ISocket->SocketBaseTags(SBTM_GETREF(SBTC_ERRNO), &error, TAG_END);
        unsigned int caughtSignals = listenSignals;
    } while (numfds == -1 && (error == EINTR || error == EAGAIN));

    if (numfds > 0)
        qt_poll_sweep(d->pollfds.data(), d->pollfds.size(), &read_fds, &write_fds, &except_fds);

#else
    timespec ts, *tsp = nullptr;
    if(tm) {
        ts = timevalToTimespec(*tm);
        tsp = &ts;
    }
    switch (qt_safe_poll(d->pollfds.data(), d->pollfds.size(), tsp, (ULONG*)&listenSignals)) {
    case -1:
        perror("qt_safe_poll");
        break;
    case 0:
        break;
    default:
        qInfo() << "poll";
        // nevents += d->threadPipe.check(d->pollfds.takeLast());
        if (include_notifiers)
            nevents += d->activateSocketNotifiers();
        break;
    }
#endif

    // if(!(caughtSignals & 1 << d->timerPort->mp_SigBit))
    //     IExec->AbortIO((struct IORequest *)d->timerRequest);

    if (include_timers) { // && caughtSignals | 1 << d->timerPort->mp_SigBit) {
        nevents += d->activateTimers();
    }

    if (include_notifiers)
        nevents += d->activateSocketNotifiers();

    // return true if we handled events, false otherwise
    return (nevents > 0);
}

int QEventDispatcherAMIGA::remainingTime(int timerId)
{
    Q_D(QEventDispatcherAMIGA);
    return d->timerList.timerRemainingTime(timerId);
}

void QEventDispatcherAMIGA::wakeUp()
{
    Q_D(QEventDispatcherAMIGA);
    IExec->Signal(d->me, 1 << d->wakeupSignal);
}

void QEventDispatcherAMIGA::interrupt()
{
    Q_D(QEventDispatcherAMIGA);
    d->interrupt.storeRelaxed(1);
    wakeUp();
}

QT_END_NAMESPACE

#include "moc_qeventdispatcher_amiga_p.cpp"
