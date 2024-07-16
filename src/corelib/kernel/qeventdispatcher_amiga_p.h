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

#ifndef QEventDispatcherAMIGA_H
#define QEventDispatcherAMIGA_H

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

class QEventDispatcherAMIGAPrivate;
class AmigaIntuitionMessageHandler;

struct Q_CORE_EXPORT QSocketNotifierSetUNIX final
{
    inline QSocketNotifierSetUNIX() noexcept;

    inline bool isEmpty() const noexcept;
    inline short events() const noexcept;

    QSocketNotifier *notifiers[3];
};

class Q_CORE_EXPORT QEventDispatcherAMIGA : public QAbstractEventDispatcher
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QEventDispatcherAMIGA)

public:
    explicit QEventDispatcherAMIGA(QObject *parent = nullptr);
    ~QEventDispatcherAMIGA();

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
    QEventDispatcherAMIGA(QEventDispatcherAMIGAPrivate &dd, QObject *parent = nullptr);
};

class Q_CORE_EXPORT QEventDispatcherAMIGAPrivate : public QAbstractEventDispatcherPrivate
{
    Q_DECLARE_PUBLIC(QEventDispatcherAMIGA)

public:
    QEventDispatcherAMIGAPrivate();
    ~QEventDispatcherAMIGAPrivate();

    int activateTimers();

    void markPendingSocketNotifiers();
    int activateSocketNotifiers();
    void setSocketNotifierPending(QSocketNotifier *notifier);

    QList<pollfd> pollfds;

    QHash<int, QSocketNotifierSetUNIX> socketNotifiers;
    QList<QSocketNotifier *> pendingNotifiers;

    QTimerInfoList timerList;
    QAtomicInt interrupt; // bool

    struct MsgPort *timerPort;
    struct TimeRequest *timerRequest;
    uint8 wakeupSignal;
    struct Task *me;
};

inline QSocketNotifierSetUNIX::QSocketNotifierSetUNIX() noexcept
{
    notifiers[0] = nullptr;
    notifiers[1] = nullptr;
    notifiers[2] = nullptr;
}

inline bool QSocketNotifierSetUNIX::isEmpty() const noexcept
{
    return !notifiers[0] && !notifiers[1] && !notifiers[2];
}

inline short QSocketNotifierSetUNIX::events() const noexcept
{
    short result = 0;

    if (notifiers[0])
        result |= POLLIN;

    if (notifiers[1])
        result |= POLLOUT;

    if (notifiers[2])
        result |= POLLPRI;

    return result;
}

QT_END_NAMESPACE

#endif // QEventDispatcherAMIGA_UNIX_P_H
