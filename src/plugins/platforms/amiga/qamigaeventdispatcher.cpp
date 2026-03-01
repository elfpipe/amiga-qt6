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
    } else printf("No amiga windows.\n");

    d->pollfds.clear();
    d->pollfds.reserve(1 + (include_notifiers ? d->socketNotifiers.size() : 0));

    if (include_notifiers)
        for (auto it = d->socketNotifiers.cbegin(); it != d->socketNotifiers.cend(); ++it)
            d->pollfds.append(qt_make_pollfd(it.key(), it.value().events()));

    int nevents = 0;



// // This must be last, as it's popped off the end below
// d->pollfds.append(d->threadPipe.prepare());

    


    // unsigned int caughtSignals = IExec->Wait(listenSignals);


switch (qt_safe_poll(d->pollfds.data(), d->pollfds.size(), tm, &listenSignals)) {
case -1:
    perror("qt_safe_poll");
    break;
case 0:
    break;
default:
    // nevents += d->threadPipe.check(d->pollfds.takeLast());
    if (include_notifiers)
        nevents += d->activateSocketNotifiers();
    break;
}










    // if (listenSignals & 1 << d->wakeupSignal)
    //     {} //printf("WAKE UP!!!!\n");

    // if(!(caughtSignals & 1 << d->timerPort->mp_SigBit))
    //     IExec->AbortIO((struct IORequest *)d->timerRequest);


    if (include_timers)
        nevents += d->activateTimers();


    if (include_notifiers)
        nevents += d->activateSocketNotifiers();



    if(intuitionPort) {
        // Drain the port regardless of listenSignals, as Wait() might have missed it 
        // or other signals might have arrived.
        while(struct IntuiMessage *message = (struct IntuiMessage *)IExec->GetMsg(intuitionPort)) {
            struct IntuiMessage messageCopy = *message;
            nevents++;

            QAmigaWindow *target = nullptr;
            for(int i = 0; i < windows.size(); i++) {
                if(windows.at(i)->intuitionWindow() == messageCopy.IDCMPWindow) {
                    target = windows.at(i);
                    break;
                }
            }

            // Early Reply strategy: Reply to certain events immediately to prevent Intuition deadlocks
            // when we call window attribute getters during processing.
            if (message->Class == IDCMP_NEWSIZE || message->Class == IDCMP_CHANGEWINDOW) {
                IExec->ReplyMsg((struct Message *)message);
                message = nullptr; // Don't reply twice
            }

            if(target) {
                target->processIntuiMessage(&messageCopy);
            }

            if (message)
                IExec->ReplyMsg((struct Message *)message);
        }
    }

    // return true if we handled events, false otherwise
    return QWindowSystemInterface::sendWindowSystemEvents(flags) || nevents > 0;
}