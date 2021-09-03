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

#include "qamigaeventdispatcher.h"
#include <private/qthread_p.h>
#include <private/qcoreapplication_p.h>
#include <private/qcore_unix_p.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef QT_NO_EVENTFD
#  include <sys/eventfd.h>
#endif

QT_BEGIN_NAMESPACE

QAmigaEventDispatcherPrivate::QAmigaEventDispatcherPrivate()
{
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
}

QAmigaEventDispatcherPrivate::~QAmigaEventDispatcherPrivate()
{
    // cleanup timers
    qDeleteAll(timerList);
}

int QAmigaEventDispatcherPrivate::activateTimers()
{
    return timerList.activateTimers();
}


QAmigaEventDispatcher::QAmigaEventDispatcher(QObject *parent)
    : QAbstractEventDispatcher(*new QAmigaEventDispatcherPrivate, parent)
{ }

QAmigaEventDispatcher::QAmigaEventDispatcher(QAmigaEventDispatcherPrivate &dd, QObject *parent)
    : QAbstractEventDispatcher(dd, parent)
{ }

QAmigaEventDispatcher::~QAmigaEventDispatcher()
{ }

void QAmigaEventDispatcher::registerSocketNotifier(QSocketNotifier *notifier) {
    Q_UNUSED(notifier);
}

void QAmigaEventDispatcher::unregisterSocketNotifier(QSocketNotifier *notifier) {
    Q_UNUSED(notifier);
}

/*!
    \internal
*/
void QAmigaEventDispatcher::registerTimer(int timerId, qint64 interval, Qt::TimerType timerType, QObject *obj)
{
    Q_D(QAmigaEventDispatcher);
    d->timerList.registerTimer(timerId, interval, timerType, obj);
}

/*!
    \internal
*/
bool QAmigaEventDispatcher::unregisterTimer(int timerId)
{
    Q_D(QAmigaEventDispatcher);
    return d->timerList.unregisterTimer(timerId);
}

/*!
    \internal
*/
bool QAmigaEventDispatcher::unregisterTimers(QObject *object)
{
    Q_D(QAmigaEventDispatcher);
    return d->timerList.unregisterTimers(object);
}

QList<QAmigaEventDispatcher::TimerInfo>
QAmigaEventDispatcher::registeredTimers(QObject *object) const
{
    if (!object) {
        qWarning("QAmigaEventDispatcher:registeredTimers: invalid argument");
        return QList<TimerInfo>();
    }

    Q_D(const QAmigaEventDispatcher);
    return d->timerList.registeredTimers(object);
}

/*****************************************************************************
 QEventDispatcher implementations for AMIGAAAAAAAAAA.....!!
 *****************************************************************************/


bool QAmigaEventDispatcher::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    Q_D(QAmigaEventDispatcher);
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

    struct TimeVal wait_tm = { 0, 0 };

    unsigned int listenSignals = 0;
    if (!canWait || (include_timers && d->timerList.timerWait(wait_tm))) {
        d->timerRequest->Request.io_Command = TR_ADDREQUEST;
        d->timerRequest->Time = wait_tm;

        printf("Sending IO Request to timer.device. Seconds : %lu , Microseconds : %lu\n", wait_tm.Seconds, wait_tm.Microseconds);

        IExec->SendIO((struct IORequest *)d->timerRequest);
        listenSignals |= 1 << d->timerPort->mp_SigBit;
    }

    int nevents = 0;

    unsigned int caughtSignals = IExec->Wait(listenSignals);

    if(!caughtSignals & 1 << d->timerPort->mp_SigBit)
        IExec->AbortIO((struct IORequest *)d->timerRequest);

    if (include_timers && caughtSignals | 1 << d->timerPort->mp_SigBit) {
        printf("Timer event\n");
        nevents += d->activateTimers();
    }
    // return true if we handled events, false otherwise
    return (nevents > 0);
}

int QAmigaEventDispatcher::remainingTime(int timerId)
{
    Q_D(QAmigaEventDispatcher);
    return d->timerList.timerRemainingTime(timerId);
}

void QAmigaEventDispatcher::wakeUp()
{
    Q_D(QAmigaEventDispatcher);
}

void QAmigaEventDispatcher::interrupt()
{
    Q_D(QAmigaEventDispatcher);
    d->interrupt.storeRelaxed(1);
    wakeUp();
}

QT_END_NAMESPACE

#include "moc_qamigaeventdispatcher.cpp"
