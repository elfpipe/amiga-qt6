/****************************************************************************
**
** Copyright (C) 2021 The Qt Company Ltd.
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

#include <qelapsedtimer.h>
#include <qcoreapplication.h>

#include "private/qcore_unix_p.h"
#include "private/qtimerinfo_amiga_p.h"
#include "private/qobject_p.h"
#include "private/qabstracteventdispatcher_p.h"

#include <devices/timer.h>
#include <proto/exec.h>

#ifdef QTIMERINFO_DEBUG
#  include <QDebug>
#  include <QThread>
#endif

#include <sys/times.h>

QT_BEGIN_NAMESPACE

Q_CORE_EXPORT bool qt_disable_lowpriority_timers=false;

/*
 * Internal functions for manipulating timer data structures.  The
 * timerBitVec array is used for keeping track of timer identifiers.
 */

QTimerInfoList::QTimerInfoList()
{
    printf("Creating TimerInfoList.\n");
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

    firstTimerInfo = nullptr;
}

QTimerInfoList::~QTimerInfoList() {
    IExec->CloseDevice ((struct IORequest *)timerRequest);
    IExec->FreeSysObject (ASOT_IOREQUEST, timerRequest);
    IExec->FreeSysObject (ASOT_PORT, timerPort);
}

struct TimeVal QTimerInfoList::updateCurrentTime()
{
    timerRequest->Request.io_Command = TR_GETSYSTIME;
    IExec->DoIO((struct IORequest *)timerRequest);

//    printf("DoIO request for timer.device returned Seconds : %lu , Microseconds : %lu\n", timerRequest->Time.Seconds, timerRequest->Time.Microseconds);

    currentTime = timerRequest->Time;
    return currentTime;
}

void QTimerInfoList::repairTimersIfNeeded()
{
}

/*
  insert timer info into list
*/
inline bool operator<(const TimeVal &v1, const TimeVal v2) {
    return v1.Seconds < v2.Seconds || (v1.Seconds == v2.Seconds && v1.Microseconds < v2.Microseconds);
}

void QTimerInfoList::timerInsert(QTimerInfo *ti)
{
    int index = size();
    while (index--) {
        const QTimerInfo * const t = at(index);
        if (!(ti->timeout < t->timeout))
            break;
    }
    insert(index+1, ti);
}

inline struct TimeVal operator-=(struct TimeVal &v1, struct TimeVal &v2) {
    v1.Seconds -= v2.Seconds;
    if(v1.Microseconds < v2.Microseconds) {
        v1.Seconds--;
        v1.Microseconds += 1000 * 1000;
    }
    v1.Microseconds -= v2.Microseconds;
    return v1;
}

inline struct TimeVal operator-(struct TimeVal &v1, struct TimeVal &v2) {
    struct TimeVal v3 = v1;
    return v3 -= v2;
}

inline struct TimeVal &operator+=(struct TimeVal &t1, int ms)
{
    t1.Seconds += ms / 1000;
    t1.Microseconds += (ms % 1000) * 1000;
    return t1;
}

inline struct TimeVal operator+(const struct TimeVal &t1, int ms)
{
    struct TimeVal t2 = t1;
    return t2 += ms;
}
#ifdef QTIMERINFO_DEBUG
QDebug operator<<(QDebug s, timeval tv)
{
    QDebugStateSaver saver(s);
    s.nospace() << tv.Seconds << "." << qSetFieldWidth(6) << qSetPadChar(QChar(48)) << tv.Microseconds << Qt::reset;
    return s;
}
QDebug operator<<(QDebug s, Qt::TimerType t)
{
    QDebugStateSaver saver(s);
    s << (t == Qt::PreciseTimer ? "P" :
          t == Qt::CoarseTimer ? "C" : "VC");
    return s;
}
#endif
static void calculateNextTimeout(QTimerInfo *t, struct TimeVal currentTime)
{
    t->timeout += t->interval;
    if (t->timeout < currentTime) {
        t->timeout = currentTime;
        t->timeout += t->interval;
    }
}
/*
  Returns the time to wait for the next timer, or null if no timers
  are waiting.
*/
bool QTimerInfoList::timerWait(struct TimeVal &tv)
{
    struct TimeVal currentTime = updateCurrentTime();
    repairTimersIfNeeded();

    // Find first waiting timer not already active
    QTimerInfo *t = nullptr;
    for (QTimerInfoList::const_iterator it = constBegin(); it != constEnd(); ++it) {
        if (!(*it)->activateRef) {
            t = *it;
            break;
        }
    }

    if (!t)
      return false;

    if (currentTime < t->timeout) {
        // time to wait
        tv = t->timeout - currentTime;
    } else {
        // no time to wait
        tv.Seconds  = 0;
        tv.Microseconds = 0;
    }

    return true;
}

/*
  Returns the timer's remaining time in milliseconds with the given timerId, or
  null if there is nothing left. If the timer id is not found in the list, the
  returned value will be -1. If the timer is overdue, the returned value will be 0.
*/
int QTimerInfoList::timerRemainingTime(int timerId)
{
    struct TimeVal currentTime = updateCurrentTime();
    repairTimersIfNeeded();
    struct TimeVal tm = {0, 0};

    for (int i = 0; i < count(); ++i) {
        QTimerInfo *t = at(i);
        if (t->id == timerId) {
            if (currentTime < t->timeout) {
                // time to wait
                t->timeout - currentTime;
                return tm.Seconds*1000 + tm.Microseconds/1000;
            } else {
                return 0;
            }
        }
    }

#ifndef QT_NO_DEBUG
    qWarning("QTimerInfoList::timerRemainingTime: timer id %i not found", timerId);
#endif

    return -1;
}

void QTimerInfoList::registerTimer(int timerId, qint64 interval, Qt::TimerType timerType, QObject *object)
{
    QTimerInfo *t = new QTimerInfo;
    t->id = timerId;
    t->interval = interval;
    t->timerType = timerType;
    t->obj = object;
    t->activateRef = nullptr;

    struct TimeVal expected = updateCurrentTime() + interval;

t->timeout = expected;
    timerInsert(t);

#ifdef QTIMERINFO_DEBUG
    t->expected = expected;
    t->cumulativeError = 0;
    t->count = 0;
    if (t->timerType != Qt::PreciseTimer)
    qDebug() << "timer" << t->timerType << Qt::hex <<t->id << Qt::dec << "interval" << t->interval << "expected at"
            << t->expected << "will fire first at" << t->timeout;
#endif
}

bool QTimerInfoList::unregisterTimer(int timerId)
{
    // set timer inactive
    for (int i = 0; i < count(); ++i) {
        QTimerInfo *t = at(i);
        if (t->id == timerId) {
            // found it
            removeAt(i);
            if (t == firstTimerInfo)
                firstTimerInfo = nullptr;
            if (t->activateRef)
                *(t->activateRef) = nullptr;
            delete t;
            return true;
        }
    }
    // id not found
    return false;
}

bool QTimerInfoList::unregisterTimers(QObject *object)
{
    if (isEmpty())
        return false;
    for (int i = 0; i < count(); ++i) {
        QTimerInfo *t = at(i);
        if (t->obj == object) {
            // object found
            removeAt(i);
            if (t == firstTimerInfo)
                firstTimerInfo = nullptr;
            if (t->activateRef)
                *(t->activateRef) = nullptr;
            delete t;
            // move back one so that we don't skip the new current item
            --i;
        }
    }
    return true;
}

QList<QAbstractEventDispatcher::TimerInfo> QTimerInfoList::registeredTimers(QObject *object) const
{
    QList<QAbstractEventDispatcher::TimerInfo> list;
    for (int i = 0; i < count(); ++i) {
        const QTimerInfo * const t = at(i);
        if (t->obj == object) {
            list << QAbstractEventDispatcher::TimerInfo(t->id,
                                                        (t->timerType == Qt::VeryCoarseTimer
                                                         ? t->interval * 1000
                                                         : t->interval),
                                                        t->timerType);
        }
    }
    return list;
}

/*
    Activate pending timers, returning how many where activated.
*/
int QTimerInfoList::activateTimers()
{
    if (qt_disable_lowpriority_timers || isEmpty())
        return 0; // nothing to do

    int n_act = 0, maxCount = 0;
    firstTimerInfo = nullptr;

    struct TimeVal currentTime = updateCurrentTime();
    // qDebug() << "Thread" << QThread::currentThreadId() << "woken up at" << currentTime;
    repairTimersIfNeeded();


    // Find out how many timer have expired
    for (QTimerInfoList::const_iterator it = constBegin(); it != constEnd(); ++it) {
        if (currentTime < (*it)->timeout)
            break;
        maxCount++;
    }

    //fire the timers.
    while (maxCount--) {
        if (isEmpty())
            break;

        QTimerInfo *currentTimerInfo = constFirst();
        if (currentTime < currentTimerInfo->timeout)
            break; // no timer has expired

        if (!firstTimerInfo) {
            firstTimerInfo = currentTimerInfo;
        } else if (firstTimerInfo == currentTimerInfo) {
            // avoid sending the same timer multiple times
            break;
        } else if (currentTimerInfo->interval <  firstTimerInfo->interval
                   || currentTimerInfo->interval == firstTimerInfo->interval) {
            firstTimerInfo = currentTimerInfo;
        }

        // remove from list
        removeFirst();

#ifdef QTIMERINFO_DEBUG
        float diff;
        if (currentTime < currentTimerInfo->expected) {
            // early
            timeval early = currentTimerInfo->expected - currentTime;
            diff = -(early.Seconds + early.Microseconds / 1000000.0);
        } else {
            timeval late = currentTime - currentTimerInfo->expected;
            diff = late.Seconds + late.Microseconds / 1000000.0;
        }
        currentTimerInfo->cumulativeError += diff;
        ++currentTimerInfo->count;
        if (currentTimerInfo->timerType != Qt::PreciseTimer)
        qDebug() << "timer" << currentTimerInfo->timerType << Qt::hex << currentTimerInfo->id << Qt::dec << "interval"
                << currentTimerInfo->interval << "firing at" << currentTime
                << "(orig" << currentTimerInfo->expected << "scheduled at" << currentTimerInfo->timeout
                << ") off by" << diff << "activation" << currentTimerInfo->count
                << "avg error" << (currentTimerInfo->cumulativeError / currentTimerInfo->count);
#endif

        // determine next timeout time
        calculateNextTimeout(currentTimerInfo, currentTime);

        // reinsert timer
        timerInsert(currentTimerInfo);
        if (currentTimerInfo->interval > 0)
            n_act++;

        // Send event, but don't allow it to recurse:
        if (!currentTimerInfo->activateRef) {
            currentTimerInfo->activateRef = &currentTimerInfo;

            QTimerEvent e(currentTimerInfo->id);
            QCoreApplication::sendEvent(currentTimerInfo->obj, &e);

            // Storing currentTimerInfo's address in its activateRef allows the
            // handling of that event to clear this local variable on deletion
            // of the object it points to - if it didn't, clear activateRef:
            if (currentTimerInfo)
                currentTimerInfo->activateRef = nullptr;
        }
    }

    firstTimerInfo = nullptr;
    // qDebug() << "Thread" << QThread::currentThreadId() << "activated" << n_act << "timers";
    return n_act;
}

QT_END_NAMESPACE
