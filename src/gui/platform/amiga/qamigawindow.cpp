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

#include "qamigawindow_p.h"
#include "qamigacommon_p.h"
#include "qamigaeventdispatcherwindows_p.h"

#include <qpa/qplatformscreen.h>
#include <qpa/qwindowsysteminterface.h>

#include <private/qwindow_p.h>

#define BOOL short
#include <proto/intuition.h>
#include <proto/keymap.h>
#include <proto/exec.h>

QT_BEGIN_NAMESPACE

QAmigaWindow::QAmigaWindow(QWindow *window, bool frameMarginsEnabled)
    : QPlatformWindow(window)
    , m_positionIncludesFrame(false)
    , m_visible(false)
    , m_pendingGeometryChangeOnShow(true)
    , m_frameMarginsRequested(frameMarginsEnabled)
    , m_intuitionWindow(0)
{
    QRect rect = initialGeometry(window, window->geometry(), 320, 240);

    if (window->windowState() == Qt::WindowNoState) {
        setGeometry(windowGeometry());
    } else {
        setWindowState(window->windowStates());

        setVisible(true);
        setGeometry(rect);
    }

    static WId counter = 0;
    m_winId = ++counter;

    m_windowForWinIdHash[m_winId] = this;
}

QAmigaWindow::~QAmigaWindow()
{
    if (QAmigaScreen::windowContainingCursor == this)
        QAmigaScreen::windowContainingCursor = nullptr;
    m_windowForWinIdHash.remove(m_winId);

    closeWindow();
}

void QAmigaWindow::openWindow()
{
    if(m_intuitionWindow) IIntuition->CloseWindow(m_intuitionWindow);
    m_intuitionWindow = 0;

    //if(window()->surfaceType() == QSurface::Offscreen) return;

    m_normalGeometry = windowFrameGeometry();

    bool frameless = 
                    window()->flags() & Qt::FramelessWindowHint
                    || window()->type() == Qt::Tool
                    || window()->type() == Qt::Popup
                    || window()->type() == Qt::ToolTip
                    || window()->type() == Qt::SplashScreen
                    || window()->type() == Qt::Desktop
                    || window()->type() == Qt::SubWindow;

    m_intuitionWindow = IIntuition->OpenWindowTags(0,
        WA_Left, m_normalGeometry.x(),
        WA_Top, m_normalGeometry.y(),
        WA_Width, m_normalGeometry.width(),
        WA_Height, m_normalGeometry.height(),  
        WA_MaxWidth, 1920,
        WA_MaxHeight, 1080,
        WA_IDCMP, IDCMP_CLOSEWINDOW|IDCMP_NEWSIZE|IDCMP_CHANGEWINDOW|IDCMP_MOUSEBUTTONS|IDCMP_MOUSEMOVE|IDCMP_EXTENDEDMOUSE|IDCMP_RAWKEY,
        WA_Flags, ( frameless ? 0 : WFLG_SIZEGADGET | WFLG_DRAGBAR | WFLG_DEPTHGADGET    | WFLG_CLOSEGADGET ) | WFLG_ACTIVATE,
        WA_GimmeZeroZero, TRUE,
        frameless ? TAG_IGNORE : WA_Title, strdup(window()->title().toLocal8Bit().constData()),
        WA_ScreenTitle, "Qt 6.2.0 - welcome to true happiness... :)",
        WA_PubScreenName, "Workbench",
        WA_Borderless, frameless ? TRUE : FALSE,
        WA_ToolBox, window()->type() == Qt::ToolTip ? TRUE : FALSE,
        WA_ReportMouse, TRUE,
        WA_UserPort, QAmigaIntegration::messagePort(),
        TAG_DONE );

    static_cast<QEventDispatcherAMIGAWindows *>(QAmigaIntegration::eventDispatcher())->registerWindow(this);

}

void QAmigaWindow::closeWindow()
{
    if(m_intuitionWindow) {
        IIntuition->CloseWindow(m_intuitionWindow);
        static_cast<QEventDispatcherAMIGAWindows *>(QAmigaIntegration::eventDispatcher())->unregisterWindow(this);
        m_intuitionWindow = 0;
    }
}

void QAmigaWindow::setGeometry(const QRect &rect)
{
    if (window()->windowState() != Qt::WindowNoState)
        return;

    m_positionIncludesFrame = qt_window_private(window())->positionPolicy == QWindowPrivate::WindowFrameInclusive;

    setFrameMarginsEnabled(m_frameMarginsRequested);
    setGeometryImpl(rect);

    m_normalGeometry = windowFrameGeometry();

    if(m_intuitionWindow)
        IIntuition->SetWindowAttrs(m_intuitionWindow,
                                WA_Left, m_normalGeometry.x(),
                                WA_Top, m_normalGeometry.y(),
                                WA_Width, m_normalGeometry.width(),
                                WA_Height, m_normalGeometry.height(),
                                TAG_DONE);
}

void QAmigaWindow::setGeometryImpl(const QRect &rect)
{
    QRect adjusted = rect;
    if (adjusted.width() <= 0)
        adjusted.setWidth(1);
    if (adjusted.height() <= 0)
        adjusted.setHeight(1);

    if (m_positionIncludesFrame) {
        adjusted.adjust(-m_margins.left(), -m_margins.top(), m_margins.right(), m_margins.bottom());
    } else {
        // make sure we're not placed off-screen
        if (adjusted.left() < m_margins.left())
            adjusted.translate(m_margins.left(), 0);
        if (adjusted.top() < m_margins.top())
            adjusted.translate(0, m_margins.top());
    }

    QPlatformWindow::setGeometry(adjusted);

    if (m_visible) {
        QWindowSystemInterface::handleGeometryChange(window(), adjusted);
        QWindowSystemInterface::handleExposeEvent(window(), QRect(QPoint(), adjusted.size()));
    } else {
        m_pendingGeometryChangeOnShow = true;
    }
}

void QAmigaWindow::setVisible(bool visible)
{
    if (visible == m_visible)
        return;

    if (visible) {
        if (window()->type() != Qt::ToolTip)
            QWindowSystemInterface::handleWindowActivated(window());

        if (m_pendingGeometryChangeOnShow) {
            m_pendingGeometryChangeOnShow = false;
            QWindowSystemInterface::handleGeometryChange(window(), geometry());
        }
    }

    if (visible) {
        QRect rect(QPoint(), geometry().size());
        QWindowSystemInterface::handleExposeEvent(window(), rect);
    } else {
        QWindowSystemInterface::handleExposeEvent(window(), QRegion());
    }

    m_visible = visible;

    if(visible) openWindow();
    else closeWindow();
}

void QAmigaWindow::requestActivateWindow()
{
    if (m_visible)
        QWindowSystemInterface::handleWindowActivated(window());
}

WId QAmigaWindow::winId() const
{
    return m_winId;
}

QMargins QAmigaWindow::frameMargins() const
{
    return m_margins;
}

void QAmigaWindow::setFrameMarginsEnabled(bool enabled)
{
    //first, open dummy window to read dimensions
    struct Window *dummy = IIntuition->OpenWindowTags(0,
        WA_Flags, WFLG_SIZEGADGET | WFLG_DRAGBAR | WFLG_DEPTHGADGET    | WFLG_CLOSEGADGET | WFLG_ACTIVATE,
        WA_Title, "Qt Analog Clock",
        WA_Left, 0,
        WA_Top, 0,
        WA_Width, 640,
        WA_Height, 512,
        WA_Hidden, TRUE,
        TAG_DONE);

    bool frameless = 
            window()->flags() & Qt::FramelessWindowHint
                    || window()->type() == Qt::Tool
                    || window()->type() == Qt::Popup
                    || window()->type() == Qt::ToolTip
                    || window()->type() == Qt::SplashScreen
                    || window()->type() == Qt::Desktop
                    || window()->type() == Qt::SubWindow;

    if (enabled
        && !frameless
        && (parent() == nullptr)) {
        m_margins = QMargins(dummy->BorderLeft, dummy->BorderTop, dummy->BorderRight, dummy->BorderBottom);
    } else {
        m_margins = QMargins(0, 0, 0, 0);
    }
    IIntuition->CloseWindow(dummy);
}

void QAmigaWindow::setWindowState(Qt::WindowStates state)
{
    setFrameMarginsEnabled(m_frameMarginsRequested && !(state & Qt::WindowFullScreen));
    m_positionIncludesFrame = false;

    if (state & Qt::WindowMinimized)
        ; // nothing to do
    else if (state & Qt::WindowFullScreen)
        setGeometryImpl(screen()->geometry());
    else if (state & Qt::WindowMaximized)
        setGeometryImpl(screen()->availableGeometry().adjusted(m_margins.left(), m_margins.top(), -m_margins.right(), -m_margins.bottom()));
    else
        setGeometryImpl(m_normalGeometry);

    QWindowSystemInterface::handleWindowStateChanged(window(), state);
}

QAmigaWindow *QAmigaWindow::windowForWinId(WId id)
{
    return m_windowForWinIdHash.value(id, 0);
}

QHash<WId, QAmigaWindow *> QAmigaWindow::m_windowForWinIdHash;

bool qt_swap_ctrl_and_amiga_keys = false;
int qt_wheel_sensitivity = 120;

Qt::KeyboardModifiers qualifiersToModifiers(UWORD qualifier) 
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

static Qt::MouseButtons buttons = Qt::NoButton;

void QAmigaWindow::processIntuiMessage(struct IntuiMessage *message) {
    Qt::KeyboardModifiers modifiers = qualifiersToModifiers(message->Qualifier);

    QPoint localPosition(message->MouseX - message->IDCMPWindow->BorderLeft, message->MouseY - message->IDCMPWindow->BorderTop);
    QPoint globalPosition(message->IDCMPWindow->LeftEdge + message->MouseX,
                            message->IDCMPWindow->TopEdge + message->MouseY);

    switch(message->Class) {
        case IDCMP_CLOSEWINDOW :
            QWindowSystemInterface::handleCloseEvent(window());
            break;

        case IDCMP_NEWSIZE:
        case IDCMP_CHANGEWINDOW: {
            int x, y, w, h;
            IIntuition->GetWindowAttrs (message->IDCMPWindow, WA_Left, &x, WA_Top, &y, WA_InnerWidth, &w, WA_InnerHeight, &h, TAG_END);
            const QRect newGeometry(QPoint(x+message->IDCMPWindow->BorderLeft, y+message->IDCMPWindow->BorderTop), QSize(w, h));

            QWindowSystemInterface::handleGeometryChange(window(), newGeometry);
            QWindowSystemInterface::handleExposeEvent(window(), QRect(QPoint(0, 0), newGeometry.size()));

            QWindowSystemInterface::handleWindowStateChanged(window(), Qt::WindowNoState);
        }
        break;

        case IDCMP_MOUSEMOVE : {
            QWindowSystemInterface::handleMouseEvent(window(), localPosition, globalPosition, buttons, Qt::NoButton, QEvent::MouseMove, modifiers, Qt::MouseEventNotSynthesized);
        }
        break;

        case IDCMP_MOUSEBUTTONS : {
            Qt::MouseButton button = Qt::NoButton;
            QEvent::Type type;
            switch(message->Code) {
                case SELECTDOWN:
                    button = Qt::LeftButton;
                    buttons |= Qt::LeftButton;
                    type = QEvent::MouseButtonPress;
                    break;
                case SELECTUP:
                    button = Qt::LeftButton;
                    buttons &= ~Qt::LeftButton;
                    type = QEvent::MouseButtonRelease;
                    break;
                case MENUDOWN:
                    button = Qt::RightButton;
                    buttons |= Qt::RightButton;
                    type = QEvent::MouseButtonPress;
                    break;
                case MENUUP:
                    button = Qt::RightButton;
                    buttons &= ~Qt::RightButton;
                    type = QEvent::MouseButtonRelease;
                    break;
                case MIDDLEDOWN:
                    button = Qt::MiddleButton;
                    buttons |= Qt::MiddleButton;
                    type = QEvent::MouseButtonPress;
                    break;
                case MIDDLEUP:
                    button = Qt::MiddleButton;
                    buttons &= ~Qt::MiddleButton;
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

                int pixeldeltax, pixeldeltay;
                int angledeltax, angledeltay;

                pixeldeltax = data->WheelX;
                pixeldeltay = data->WheelY;
                angledeltax = data->WheelX * 120;
                angledeltay = data->WheelY * 120;

                QWindowSystemInterface::handleWheelEvent(window(), localPosition, globalPosition, QPoint(pixeldeltax, pixeldeltay), QPoint(angledeltax, angledeltay), modifiers);
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
}

QT_END_NAMESPACE
