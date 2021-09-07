/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the plugins of the Qt Toolkit.
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

#include "qamigaintegration_p.h"
#include "qamigabackingstore_p.h"

#include <QtGui/private/qpixmap_raster_p.h>
#include <QtGui/private/qguiapplication_p.h>
// #include <qpa/qplatformwindow.h>
// #include <qpa/qwindowsysteminterface.h>

#include <QtGui/private/qfreetypefontdatabase_p.h>

#if QT_CONFIG(fontconfig)
#  include <QtGui/private/qgenericunixfontdatabase_p.h>
#  include <qpa/qplatformfontdatabase.h>
#endif

#if QT_CONFIG(freetype)
#include <QtGui/private/qfontengine_ft_p.h>
#endif

#define BOOL short
#include <proto/intuition.h>
#include <proto/keymap.h>
#include <proto/exec.h>

#include "kernel/qguiapplication.h"
#include "../../../corelib/kernel/qeventdispatcher_amiga_p.h"

QT_BEGIN_NAMESPACE

QAbstractEventDispatcher *QAmigaIntegration::m_eventDispatcher = 0;
struct MsgPort *QAmigaIntegration::m_messagePort = 0;

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

        struct TimeVal wait_tm = { 0, 0 };

        unsigned int listenSignals = 0;
        if (!canWait || (include_timers && d->timerList.timerWait(wait_tm))) {
            d->timerRequest->Request.io_Command = TR_ADDREQUEST;
            d->timerRequest->Time = wait_tm;

    //        printf("Sending IO Request to timer.device. Seconds : %lu , Microseconds : %lu\n", wait_tm.Seconds, wait_tm.Microseconds);

            IExec->SendIO((struct IORequest *)d->timerRequest);
            listenSignals |= 1 << d->timerPort->mp_SigBit;
        }

        struct MsgPort *userPort = QAmigaIntegration::messagePort();
        if (userPort) {
            listenSignals |= 1 << userPort->mp_SigBit;
        } else printf("No amiga windows.\n");

        listenSignals |= 1 << d->wakeupSignal;

        int nevents = 0;

        unsigned int caughtSignals = IExec->Wait(listenSignals);

        if (caughtSignals & 1 << d->wakeupSignal)
            printf("WAKE UP!!!!\n");

        if(!(caughtSignals & 1 << d->timerPort->mp_SigBit))
            IExec->AbortIO((struct IORequest *)d->timerRequest);

        if (include_timers && caughtSignals | 1 << d->timerPort->mp_SigBit) {
            nevents += d->activateTimers();
        }

        if(userPort) {
            if (caughtSignals & 1 << userPort->mp_SigBit) { //all Amiga windows use the same UserPort *
                while(struct IntuiMessage *message = (struct IntuiMessage *)IExec->GetMsg(userPort)) {
                    if (message) {
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
        }

        // return true if we handled events, false otherwise
        return QWindowSystemInterface::sendWindowSystemEvents(flags) || nevents > 0;
    }
private:
    QList<QAmigaWindow *> windows;
};

QAmigaWindow::QAmigaWindow(QWindow *window)
    : QPlatformWindow(window)
{
    const QRect rect = initialGeometry(window, window->geometry(), 640, 512);

    m_intuitionWindow = IIntuition->OpenWindowTags(0,
        WA_Left, rect.x(),
        WA_Top, rect.y(),
        WA_InnerWidth, rect.width(),
        WA_InnerHeight, rect.height(),  
        WA_MaxWidth, 1920,
        WA_MaxHeight, 1080,
        WA_IDCMP, IDCMP_CLOSEWINDOW|IDCMP_NEWSIZE|IDCMP_CHANGEWINDOW|IDCMP_MOUSEBUTTONS|IDCMP_EXTENDEDMOUSE|IDCMP_RAWKEY,
        WA_Flags, WFLG_SIZEGADGET | WFLG_DRAGBAR | WFLG_DEPTHGADGET    | WFLG_CLOSEGADGET | WFLG_ACTIVATE,
        WA_GimmeZeroZero, TRUE,
        WA_Title, "Qt Analog Clock",
        WA_PubScreenName, "Workbench",
        WA_UserPort, QAmigaIntegration::messagePort(),
        TAG_DONE );

    static_cast<QEventDispatcherAMIGAWindows *>(QAmigaIntegration::eventDispatcher())->registerWindow(this);
}

QAmigaWindow::~QAmigaWindow()
{
    IIntuition->CloseWindow(m_intuitionWindow);
    static_cast<QEventDispatcherAMIGAWindows *>(QAmigaIntegration::eventDispatcher())->unregisterWindow(this);
}

bool qt_swap_ctrl_and_amiga_keys = false;
int qt_wheel_sensitivity = 120;

Qt::KeyboardModifiers qualifierToModifier(UWORD qualifier) 
{
	Qt::KeyboardModifiers ret;

	if(qt_swap_ctrl_and_amiga_keys)
	{
		if(qualifier & IEQUALIFIER_CONTROL)
			ret |= Qt::MetaModifier;
		if (qualifier & IEQUALIFIER_LCOMMAND || qualifier & IEQUALIFIER_RCOMMAND)
			ret |= Qt::ControlModifier;
	}
	else
	{
		if(qualifier & IEQUALIFIER_CONTROL)
			ret |= Qt::ControlModifier;
		if (qualifier & IEQUALIFIER_LCOMMAND || qualifier & IEQUALIFIER_RCOMMAND)
			ret |= Qt::MetaModifier;
	}
	if(qualifier & IEQUALIFIER_LSHIFT || qualifier & IEQUALIFIER_RSHIFT)
		ret |= Qt::ShiftModifier;
	if (qualifier & IEQUALIFIER_LALT || qualifier & IEQUALIFIER_RALT)
		ret |= Qt::AltModifier;

	return ret;
}

void QAmigaWindow::processIntuiMessage(struct IntuiMessage *message) {
    Qt::KeyboardModifiers modifiers = qualifierToModifier(message->Qualifier);

    QPoint localPosition(message->MouseX - message->IDCMPWindow->BorderLeft, message->MouseY - message->IDCMPWindow->BorderTop);
    QPoint globalPosition(message->IDCMPWindow->LeftEdge + message->MouseX, message->IDCMPWindow->TopEdge + message->MouseY);

    switch(message->Class) {
        case IDCMP_CLOSEWINDOW :
            printf("Close window.\n");
            QWindowSystemInterface::handleCloseEvent(window());
            break;

        case IDCMP_NEWSIZE:
        case IDCMP_CHANGEWINDOW: {
            int x, y, w, h;
            IIntuition->GetWindowAttrs (message->IDCMPWindow, WA_Left, &x, WA_Top, &y, WA_InnerWidth, &w, WA_InnerHeight, &h, TAG_END);
            QPoint newpos(x, y);
            QSize newsize(w, h);

            const QRect newGeometry(QPoint(x, y), QSize(w, h));

            QWindowSystemInterface::handleGeometryChange(window(), newGeometry);
            QWindowSystemInterface::handleExposeEvent(window(), QRect(QPoint(0, 0), newGeometry.size()));

            QWindowSystemInterface::handleWindowStateChanged(window(), Qt::WindowNoState);
        }
        break;

        case IDCMP_MOUSEBUTTONS : {

            Qt::MouseButton button = Qt::NoButton;
            Qt::MouseButtons buttons = Qt::NoButton;
            QEvent::Type type;
            switch(message->Code) {
                case SELECTUP:
                case SELECTDOWN:
                    button = Qt::LeftButton;
                    buttons = Qt::LeftButton;
                    break;
                case MENUDOWN:
                case MENUUP:
                    button = Qt::RightButton;
                    buttons = Qt::RightButton;
                    break;
                case MIDDLEDOWN:
                case MIDDLEUP:
                    button = Qt::MiddleButton;
                    buttons = Qt::MiddleButton;
                    break;
                default:
                    break;
            }
            switch(message->Code) {
                case SELECTUP:
                case MIDDLEUP:
                case MENUUP:
                    type = QEvent::MouseButtonPress;
                    break;
                case MIDDLEDOWN:
                case SELECTDOWN:
                case MENUDOWN:
                    type = QEvent::MouseButtonRelease;
                    break;
                default:
                    break;
            }

            QWindowSystemInterface::handleMouseEvent(window(), localPosition, globalPosition, buttons, button, type, modifiers, Qt::MouseEventNotSynthesized);
        }
        break;

        case IDCMP_EXTENDEDMOUSE :
            if (message->Code == IMSGCODE_INTUIWHEELDATA) {
                struct IntuiWheelData *data = (struct IntuiWheelData *)message->IAddress;

                int deltax, deltay;
                int orientationx, orientationy;

    			if (data->WheelX) {
                    deltax = -data->WheelX * qt_wheel_sensitivity;
                    orientationx = 1;
    			}
    			if(data->WheelY) {
                    deltay = -data->WheelY * qt_wheel_sensitivity;
                    orientationy = 1;
			    }
                QWindowSystemInterface::handleWheelEvent(window(), localPosition, globalPosition, QPoint(deltax, deltay), QPoint(orientationx, orientationy), modifiers);
            }
            break;

        case IDCMP_RAWKEY : {
            QEvent::Type type = message->Code & 128 ? QEvent::KeyRelease : QEvent::KeyPress;

            QString text;
            int key = 0;
            int i = message->Code & (~128);
            switch(i)
            {
                case RAWKEY_CRSRUP:		key = Qt::Key_Up;       	break;
                case RAWKEY_CRSRDOWN:	key = Qt::Key_Down;     	break;
                case RAWKEY_CRSRRIGHT:	key = Qt::Key_Right;    	break;
                case RAWKEY_CRSRLEFT:	key = Qt::Key_Left;     	break;
                case RAWKEY_INSERT:		key = Qt::Key_Insert;   	break;
                case RAWKEY_HOME:		key = Qt::Key_Home;     	break;
                case RAWKEY_END:		key = Qt::Key_End;      	break;
                case RAWKEY_PAGEUP:		key = Qt::Key_PageUp;     	break;
                case RAWKEY_PAGEDOWN:	key = Qt::Key_PageDown;     break;
                case RAWKEY_LSHIFT:
                case RAWKEY_RSHIFT:		key = Qt::Key_Shift;    	break;
                case RAWKEY_LCTRL:		key = Qt::Key_Control;  	break;
                case RAWKEY_LALT:		key = Qt::Key_Alt;			break;
                case RAWKEY_RALT:		key = Qt::Key_AltGr;      	break;
                case RAWKEY_LCOMMAND:
                case RAWKEY_RCOMMAND:	key = Qt::Key_Meta;			break;
                case RAWKEY_F1: 		key = Qt::Key_F1;	 		break;
                case RAWKEY_F2: 		key = Qt::Key_F2;	 		break;
                case RAWKEY_F3: 		key = Qt::Key_F3;	 		break;
                case RAWKEY_F4: 		key = Qt::Key_F4;	 		break;
                case RAWKEY_F5: 		key = Qt::Key_F5; 			break;
                case RAWKEY_F6: 		key = Qt::Key_F6; 			break;
                case RAWKEY_F7: 		key = Qt::Key_F7; 			break;
                case RAWKEY_F8: 		key = Qt::Key_F8; 			break;
                case RAWKEY_F9: 		key = Qt::Key_F9; 			break;
                case RAWKEY_F10: 		key = Qt::Key_F10;	 		break;
                case RAWKEY_F11: 		key = Qt::Key_F11;	 		break;
                case RAWKEY_F12: 		key = Qt::Key_F12;	 		break;

                case RAWKEY_BACKSPACE:	key = Qt::Key_Backspace;	break;
                case RAWKEY_CAPSLOCK:	key = Qt::Key_CapsLock;		break;
                case RAWKEY_HELP:		key = Qt::Key_Help;			break;
                case RAWKEY_MENU:		key = Qt::Key_Menu;			break;
                    //media keys?
                case RAWKEY_PRINTSCR:
                case RAWKEY_BREAK:
                    break;
                    
                case RAWKEY_TAB:
                case RAWKEY_ENTER:
                case RAWKEY_RETURN:
                case RAWKEY_SPACE:
                case RAWKEY_ESC:
                case RAWKEY_DEL:
                default:
                {
                    struct InputEvent ie;
                    ie.ie_Class = IECLASS_RAWKEY;
                    ie.ie_SubClass = 0;
                    ie.ie_Code = message->Code;
                    ie.ie_Qualifier = message->Qualifier;
                    ie.ie_EventAddress = (APTR *)*((ULONG*)message->IAddress);
                    char buffer[80];
                    int actual = IKeymap->MapRawKey(&ie, buffer, 80, 0);
                    buffer[actual] = 0;

                    for (int j=0; j<actual; j++)
                        text += QString::fromLocal8Bit(buffer);

                    switch(i)
                    {
                        case RAWKEY_TAB:		key = Qt::Key_Tab;			break;
                        case RAWKEY_ENTER:		key = Qt::Key_Enter;		break;
                        case RAWKEY_RETURN:		key = Qt::Key_Return;		break;
                        case RAWKEY_SPACE:		key = Qt::Key_Space;		break;
                        case RAWKEY_ESC:		key = Qt::Key_Escape;		break;
                        case RAWKEY_DEL:		key = Qt::Key_Delete;		break;
                        default:
                            ie.ie_Qualifier = 0;
                            ie.ie_EventAddress = NULL;
                            actual = IKeymap->MapRawKey(&ie, buffer, 80, 0);
                            if(actual == 1)
                            {
                                char tmp = buffer[0];
                                if((tmp >= 0x20 && tmp <= 0x60) || (tmp >= 0x7b && tmp <= 0x7e))
                                    key = (int)tmp;
                                if(tmp >= 0x61 && tmp <= 0x7a)
                                    key = (int)(tmp - 0x20);
                            }
                            break;
                    }
                }
                break;
            }

            QWindowSystemInterface::handleKeyEvent(window(), type, key, modifiers, text);
        }
        break;

        default:
            break;
    }
    //IExec->ReplyMsg((struct Message *)message);
}

class QCoreTextFontEngine;

static const char debugBackingStoreEnvironmentVariable[] = "QT_DEBUG_BACKINGSTORE";

static inline unsigned parseOptions(const QStringList &paramList)
{
    unsigned options = 0;
    for (const QString &param : paramList) {
        if (param == QLatin1String("enable_fonts"))
            options |= QAmigaIntegration::EnableFonts;
        else if (param == QLatin1String("freetype"))
            options |= QAmigaIntegration::FreeTypeFontDatabase;
        else if (param == QLatin1String("fontconfig"))
            options |= QAmigaIntegration::FontconfigDatabase;
    }
    return options;
}

QAmigaIntegration::QAmigaIntegration(const QStringList &parameters)
    : m_fontDatabase(0)
    , m_options(parseOptions(parameters))
{
    if (qEnvironmentVariableIsSet(debugBackingStoreEnvironmentVariable)
        && qEnvironmentVariableIntValue(debugBackingStoreEnvironmentVariable) > 0) {
        m_options |= DebugBackingStore | EnableFonts;
    }

    m_primaryScreen = new QAmigaScreen();

    m_primaryScreen->mGeometry = QRect(0, 0, 240, 320);
    m_primaryScreen->mDepth = 32;
    m_primaryScreen->mFormat = QImage::Format_ARGB32_Premultiplied;

    QWindowSystemInterface::handleScreenAdded(m_primaryScreen);
}

QAmigaIntegration::~QAmigaIntegration()
{
    QWindowSystemInterface::handleScreenRemoved(m_primaryScreen);
    delete m_fontDatabase;
    // if (m_eventDispatcher) delete m_eventDispatcher; //this crashes. why?
    if (m_messagePort) IExec->FreeSysObject (ASOT_PORT, m_messagePort);
}

struct MsgPort *QAmigaIntegration::messagePort() {
    if(!m_messagePort) m_messagePort = (struct MsgPort *)IExec->AllocSysObjectTags(ASOT_PORT, TAG_END);
    return m_messagePort;
}

bool QAmigaIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case MultipleWindows: return true;
    case RhiBasedRendering: return false;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

// Dummy font database that does not scan the fonts directory to be
// used for command line tools like qmlplugindump that do not create windows
// unless DebugBackingStore is activated.
class DummyFontDatabase : public QPlatformFontDatabase
{
public:
    virtual void populateFontDatabase() override {}
};

QPlatformFontDatabase *QAmigaIntegration::fontDatabase() const
{
    if (!m_fontDatabase && (m_options & EnableFonts)) {
#if defined(Q_OS_WIN)
        if (m_options & FreeTypeFontDatabase) {
#  if QT_CONFIG(freetype)
            m_fontDatabase = new QWindowsFontDatabaseFT;
#  endif // freetype
        } else {
            m_fontDatabase = new QWindowsFontDatabase;
        }
#elif defined(Q_OS_DARWIN)
        if (!(m_options & FontconfigDatabase)) {
            if (m_options & FreeTypeFontDatabase) {
#  if QT_CONFIG(freetype)
                m_fontDatabase = new QCoreTextFontDatabaseEngineFactory<QFontEngineFT>;
#  endif // freetype
            } else {
                m_fontDatabase = new QCoreTextFontDatabaseEngineFactory<QCoreTextFontEngine>;
            }
        }
#endif

        if (!m_fontDatabase) {
#if QT_CONFIG(fontconfig)
            m_fontDatabase = new QGenericUnixFontDatabase;
#else
            m_fontDatabase = QPlatformIntegration::fontDatabase();
#endif
        }
    }
    if (!m_fontDatabase)
        m_fontDatabase = new DummyFontDatabase;
    return m_fontDatabase;
}

QPlatformWindow *QAmigaIntegration::createPlatformWindow(QWindow *window) const
{
    Q_UNUSED(window);
    QPlatformWindow *w = new QAmigaWindow(window);
    w->requestActivateWindow();
    return w;
}

QPlatformBackingStore *QAmigaIntegration::createPlatformBackingStore(QWindow *window) const
{
    return new QAmigaBackingStore(window);
}

QAbstractEventDispatcher *QAmigaIntegration::createEventDispatcher() const
{
    if(!m_eventDispatcher)
        m_eventDispatcher = new QEventDispatcherAMIGAWindows;
    return m_eventDispatcher;
}

QAmigaIntegration *QAmigaIntegration::instance()
{
    return static_cast<QAmigaIntegration *>(QGuiApplicationPrivate::platformIntegration());
}

QT_END_NAMESPACE
