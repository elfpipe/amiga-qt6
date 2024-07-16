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

// #include <proto/intuition.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef QT_NO_EVENTFD
#  include <sys/eventfd.h>
#endif

// #include <proto/bsdsocket.h>

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
    // timerRequest = (struct TimeRequest *)IExec->AllocSysObjectTags(ASOT_IOREQUEST,
    //     ASOIOR_Size, sizeof(struct TimeRequest),
    //     ASOIOR_ReplyPort, timerPort,
    //     TAG_END);
    // if(!timerRequest) {
    //     qWarning("Failed to allocate message structure for timer.device communication. Exit.\n");
    //     QCoreApplication::quit();
    // }
    // unsigned int error = IExec->OpenDevice("timer.device", UNIT_MICROHZ, (struct IORequest *)timerRequest, 0);
    // if(error) {
    //     qWarning("Error opening timer.device for communication. Exit.\n");
    //     QCoreApplication::quit();
    // }
    wakeupSignal = IExec->AllocSignal(-1);
    me = IExec->FindTask(0);
}

QEventDispatcherAMIGAPrivate::~QEventDispatcherAMIGAPrivate()
{
    // IExec->CloseDevice ((IORequest *)timerRequest);
    // IExec->FreeSysObject(ASOT_IOREQUEST, timerRequest);
    // IExec->FreeSysObject(ASOT_PORT, timerPort);
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
#ifndef QT_NO_DEBUG
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

    timespec *tm = nullptr;
    timespec wait_tm = { 0, 0 };

    unsigned int listenSignals = 0;

    if (!canWait || (include_timers && d->timerList.timerWait(wait_tm)))
        tm = &wait_tm;

    listenSignals |= 1 << d->wakeupSignal;

    d->pollfds.clear();
    d->pollfds.reserve(1 + (include_notifiers ? d->socketNotifiers.size() : 0));

    if (include_notifiers)
        for (auto it = d->socketNotifiers.cbegin(); it != d->socketNotifiers.cend(); ++it)
            d->pollfds.append(qt_make_pollfd(it.key(), it.value().events()));

    int nevents = 0;

    switch (qt_safe_poll(d->pollfds.data(), d->pollfds.size(), tm, &listenSignals)) {
    case -1:
        perror("qt_safe_poll");
        break;
    case 0:
        break;
    default:
        if (include_notifiers)
            nevents += d->activateSocketNotifiers();
        break;
    }

    if (include_timers) {
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
