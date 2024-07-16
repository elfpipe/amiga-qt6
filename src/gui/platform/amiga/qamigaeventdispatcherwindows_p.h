#ifndef QAMIGAEVENTDISPATCHERWINDOWS_p_h
#define QAMIGAEVENTDISPTACHERWINDOWS_p_h

#include "qamigaintegration_p.h"
#include "qamigawindow_p.h"
#include "qamigacommon_p.h"

#include "../../../corelib/kernel/qeventdispatcher_amiga_p.h"

#include <qpa/qwindowsysteminterface.h>
#include <QtGui/private/qguiapplication_p.h>

#include <proto/intuition.h>

QT_BEGIN_NAMESPACE

class QAmigaWindow;
class QEventDispatcherAMIGAWindows : public QEventDispatcherAMIGA
{
    Q_DECLARE_PRIVATE(QEventDispatcherAMIGA)

public:
    explicit QEventDispatcherAMIGAWindows(QObject *parent = nullptr)
        : QEventDispatcherAMIGA(parent)
    {
    }

    void registerWindow(QAmigaWindow *window) {
        windows << window;
    }
    void unregisterWindow(QAmigaWindow *window) {
        windows.removeAt(windows.indexOf(window));
    }

    bool processEvents(QEventLoop::ProcessEventsFlags flags) override
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

        struct MsgPort *intuitionPort = QAmigaIntegration::messagePort();
        if (intuitionPort) {
            listenSignals |= 1 << intuitionPort->mp_SigBit;
        } else printf("No amiga windows.\n");

        listenSignals |= 1 << d->wakeupSignal;

        d->pollfds.clear();
        d->pollfds.reserve(1 + (include_notifiers ? d->socketNotifiers.size() : 0));

        if (include_notifiers)
            for (auto it = d->socketNotifiers.cbegin(); it != d->socketNotifiers.cend(); ++it)
                d->pollfds.append(qt_make_pollfd(it.key(), it.value().events()));

        int nevents = 0;




        


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











        if (listenSignals & 1 << d->wakeupSignal)
            {} //printf("WAKE UP!!!!\n");

        // if(!(caughtSignals & 1 << d->timerPort->mp_SigBit))
        //     IExec->AbortIO((struct IORequest *)d->timerRequest);


        if (include_timers)
            nevents += d->activateTimers();


        if (include_notifiers)
            nevents += d->activateSocketNotifiers();



        if(intuitionPort) {
            if (listenSignals & 1 << intuitionPort->mp_SigBit) { //all Amiga windows use the same UserPort *
                while(struct IntuiMessage *message = (struct IntuiMessage *)IExec->GetMsg(intuitionPort)) {
                    for(int i = 0; i < windows.size(); i++) {
                        QAmigaWindow *current = windows.at(i);
                        if(current && current->intuitionWindow() == message->IDCMPWindow) {
                            struct IntuiMessage messageCopy = *message;
                            IExec->ReplyMsg((struct Message *)message);
                            current->processIntuiMessage(&messageCopy);
                        }
                    }
                }
            }
        }

        // return true if we handled events, false otherwise
        return QWindowSystemInterface::sendWindowSystemEvents(flags) || nevents > 0;
    }
private:
    QList<QAmigaWindow *> windows;
};

QT_END_NAMESPACE

#endif