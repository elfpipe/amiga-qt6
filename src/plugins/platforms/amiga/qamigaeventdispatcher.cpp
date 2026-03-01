#include "qamigaeventdispatcher.h"

bool QAmigaEventDispatcher::processEvents(QEventLoop::ProcessEventsFlags flags)
{
    Q_D(QEventDispatcherUNIX);
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
    listenSignals |= 1 << d->wakeupSignal;

    if (!canWait || (include_timers && d->timerList.timerWait(wait_tm)))
        tm = &wait_tm;

    struct MsgPort *intuitionPort = QAmigaIntegration::messagePort();
    if (intuitionPort) {
        listenSignals |= 1 << intuitionPort->mp_SigBit;
    }

    d->pollfds.clear();
    d->pollfds.reserve(include_notifiers ? d->socketNotifiers.size() : 0);

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

    if (include_timers)
        nevents += d->activateTimers();

    if (intuitionPort) {
        while (struct IntuiMessage *msg = (struct IntuiMessage *)IExec->GetMsg(intuitionPort)) {
            struct IntuiMessage msgCopy = *msg;
            nevents++;
            bool replied = false;
            if (msgCopy.Class == IDCMP_NEWSIZE || msgCopy.Class == IDCMP_CHANGEWINDOW) {
                IExec->ReplyMsg((struct Message *)msg);
                replied = true;
            }

            QAmigaWindow *target = nullptr;
            for (int i = 0; i < windows.size(); i++) {
                if (windows.at(i)->intuitionWindow() == msgCopy.IDCMPWindow) {
                    target = windows.at(i);
                    break;
                }
            }

            if (target)
                target->processIntuiMessage(&msgCopy);

            if (!replied)
                IExec->ReplyMsg((struct Message *)msg);
        }
    }

    return QWindowSystemInterface::sendWindowSystemEvents(flags) || nevents > 0;
}