#ifndef QAMIGAEVENTDISPATCHERWINDOWS_p_h
#define QAMIGAEVENTDISPTACHERWINDOWS_p_h

#include "qamigaintegration.h"
#include "qamigawindow.h"
#include "qamigacommon.h"

#include <qpa/qwindowsysteminterface.h>
#include <QtGui/private/qguiapplication_p.h>
#include <QtCore/private/qeventdispatcher_unix_p.h>

#include <proto/exec.h>
#include <proto/intuition.h>

QT_BEGIN_NAMESPACE

class QAmigaWindow;
class QAmigaEventDispatcher : public QEventDispatcherUNIX
{
    Q_DECLARE_PRIVATE(QEventDispatcherUNIX)

public:
    explicit QAmigaEventDispatcher(QObject *parent = nullptr)
        : QEventDispatcherUNIX(parent)
    {
    }

    void registerWindow(QAmigaWindow *window) {
        windows << window;
    }
    void unregisterWindow(QAmigaWindow *window) {
        windows.removeAt(windows.indexOf(window));
    }

    bool processEvents(QEventLoop::ProcessEventsFlags flags) override;

private:
    QList<QAmigaWindow *> windows;
};

QT_END_NAMESPACE

#endif