/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
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

#ifndef QAMIGAEVENTDISPATCHER_H
#define QAMIGAEVENTDISPATCHER_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "QtCore/qabstracteventdispatcher.h"
#include "QtCore/qlist.h"
#include "private/qabstracteventdispatcher_p.h"
#include "private/qcore_unix_p.h"
#include "QtCore/qvarlengtharray.h"
#include "private/qtimerinfo_unix_p.h"

#include <proto/exec.h>
#include <devices/timer.h>

QT_BEGIN_NAMESPACE

class QAmigaEventDispatcherPrivate;

class Q_CORE_EXPORT QAmigaEventDispatcher : public QAbstractEventDispatcher
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QAmigaEventDispatcher)

public:
    explicit QAmigaEventDispatcher(QObject *parent = nullptr);
    ~QAmigaEventDispatcher();

    bool processEvents(QEventLoop::ProcessEventsFlags flags) override;

    void registerSocketNotifier(QSocketNotifier *notifier) override;
    void unregisterSocketNotifier(QSocketNotifier *notifier) override;

    void registerTimer(int timerId, qint64 interval, Qt::TimerType timerType, QObject *object) final;
    bool unregisterTimer(int timerId) final;
    bool unregisterTimers(QObject *object) final;
    QList<TimerInfo> registeredTimers(QObject *object) const final;

    int remainingTime(int timerId) final;

    void wakeUp() override;
    void interrupt() final;

protected:
    QAmigaEventDispatcher(QAmigaEventDispatcherPrivate &dd, QObject *parent = nullptr);
};

class Q_CORE_EXPORT QAmigaEventDispatcherPrivate : public QAbstractEventDispatcherPrivate
{
    Q_DECLARE_PUBLIC(QAmigaEventDispatcher)

public:
    QAmigaEventDispatcherPrivate();
    ~QAmigaEventDispatcherPrivate();

    int activateTimers();

    QTimerInfoList timerList;
    QAtomicInt interrupt; // bool

    struct MsgPort *timerPort;
    struct TimeRequest *timerRequest;
};

QT_END_NAMESPACE

#endif // QEVENTDISPATCHER_UNIX_P_H
