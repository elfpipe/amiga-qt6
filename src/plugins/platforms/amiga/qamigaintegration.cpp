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

#include "qamigaintegration.h"
#include "qamigabackingstore.h"

#include <QtGui/private/qpixmap_raster_p.h>
#include <QtGui/private/qguiapplication_p.h>
#include <qpa/qplatformwindow.h>
#include <qpa/qwindowsysteminterface.h>

#include <QtGui/private/qfreetypefontdatabase_p.h>

#if QT_CONFIG(fontconfig)
#  include <QtGui/private/qgenericunixfontdatabase_p.h>
#  include <qpa/qplatformfontdatabase.h>
#endif

#if QT_CONFIG(freetype)
#include <QtGui/private/qfontengine_ft_p.h>
#endif

#include "qamigaeventdispatcher.h"

#define BOOL short
#include <proto/intuition.h>

QT_BEGIN_NAMESPACE

QAmigaWindow::QAmigaWindow(QWindow *window)
    : QPlatformWindow(window)
{
    const QRect rect = initialGeometry(window, window->geometry(), 640, 512);

    intuitionWindow = IIntuition->OpenWindowTags(0,
        WA_Left, rect.x(),
        WA_Top, rect.y(),
        WA_InnerWidth, rect.width(),
        WA_InnerHeight, rect.height(),
        WA_IDCMP, IDCMP_CLOSEWINDOW,
        WA_Flags, WFLG_SIZEGADGET | WFLG_DRAGBAR | WFLG_DEPTHGADGET    | WFLG_CLOSEGADGET | WFLG_ACTIVATE,
        WA_GimmeZeroZero, TRUE,
        WA_Title, "Qt Analog Clock",
        WA_PubScreenName, "Workbench",
        TAG_DONE );
}

QAmigaWindow::~QAmigaWindow()
{
    IIntuition->CloseWindow(intuitionWindow);
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
    return new QAmigaEventDispatcher;
}

QAmigaIntegration *QAmigaIntegration::instance()
{
    return static_cast<QAmigaIntegration *>(QGuiApplicationPrivate::platformIntegration());
}

QT_END_NAMESPACE
