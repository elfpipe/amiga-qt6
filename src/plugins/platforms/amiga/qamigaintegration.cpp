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
#include "qamigawindow.h"
#include "qamigacommon.h"
#include "qamigaeventdispatcher.h"
#include "qamigaglcontext.h"

#include <QtGui/private/qfreetypefontdatabase_p.h>

#include <QtCore/qfile.h>
#include <QtCore/qjsonarray.h>
#include <QtCore/qjsondocument.h>
#include <QtCore/qjsonobject.h>
#include <QtCore/qjsonvalue.h>
#include <QtGui/private/qpixmap_raster_p.h>
#include <QtGui/private/qguiapplication_p.h>
#include <qpa/qplatforminputcontextfactory_p.h>
#include <qpa/qplatforminputcontext.h>
#include <qpa/qplatformtheme.h>
#include <qpa/qwindowsysteminterface.h>
#include <qpa/qplatformopenglcontext.h>

#include <qpa/qplatformservices.h>

#include <proto/intuition.h>

QT_BEGIN_NAMESPACE

class QCoreTextFontEngine;

QAbstractEventDispatcher *QAmigaIntegration::m_eventDispatcher = 0;
struct MsgPort *QAmigaIntegration::m_messagePort = 0;

QAmigaIntegration::QAmigaIntegration(const QStringList &paramList)
{
    m_fontDatabase.reset(new QFreeTypeFontDatabase());

#if QT_CONFIG(draganddrop)
    m_drag.reset(new QAmigaDrag);
#endif
    m_services.reset(new QPlatformServices);

    configure(paramList);
}

QAmigaIntegration::~QAmigaIntegration()
{
    for (auto screen : std::as_const(m_screens))
        QWindowSystemInterface::handleScreenRemoved(screen);

    if (m_messagePort) IExec->FreeSysObject (ASOT_PORT, m_messagePort);
}

struct MsgPort *QAmigaIntegration::messagePort() {
    return m_messagePort ? m_messagePort : m_messagePort = (struct MsgPort *)IExec->AllocSysObjectTags(ASOT_PORT, TAG_END);
}

/*
    The offscren platform plugin is configurable with a JSON configuration
    file. Write the config to disk and pass the file path as a platform argument:

        ./myapp -platform Amiga:configfile=/path/to/config.json

    The supported top-level config keys are:
    {
        "synchronousWindowSystemEvents": <bool>
        "windowFrameMargins": <bool>,
        "screens": [<screens>],
    }

    Screen:
    {
        "name" : string,
        "x": int,
        "y": int,
        "width": int,
        "height": int,
        "logicalDpi": int,
        "logicalBaseDpi": int,
        "dpr": double,
    }
*/
void QAmigaIntegration::configure(const QStringList& paramList)
{
    // Use config file configuring platform plugin, if one was specified
    bool hasConfigFile = false;
    QString configFilePath;
    for (const QString &param : paramList) {
        // Look for "configfile=/path/to/file/"
        QString configPrefix(QLatin1String("configfile="));
        if (param.startsWith(configPrefix)) {
            hasConfigFile = true;
            configFilePath= param.mid(configPrefix.length());
        }
    }

    // Create the default screen if there was no config file
    if (!hasConfigFile) {
        QAmigaScreen *amigaScreen = new QAmigaScreen(this);
        m_screens.append(amigaScreen);
        QWindowSystemInterface::handleScreenAdded(amigaScreen);
        return;
    }

    // Read config file
    if (configFilePath.isEmpty())
        qFatal("Missing file path for -configfile platform option");
    QFile configFile(configFilePath);
    if (!configFile.exists())
        qFatal("Could not find platform config file %s", qPrintable(configFilePath));
    if (!configFile.open(QIODevice::ReadOnly))
        qFatal("Could not open platform config file for reading %s, %s", qPrintable(configFilePath), qPrintable(configFile.errorString()));

    QByteArray json = configFile.readAll();
    QJsonParseError error;
    QJsonDocument config = QJsonDocument::fromJson(json, &error);
    if (config.isNull())
        qFatal("Platform config file parse error: %s", qPrintable(error.errorString()));

    // Apply configuration (create screens)
    bool synchronousWindowSystemEvents = config[QStringLiteral("synchronousWindowSystemEvents")].toBool(false);
    QWindowSystemInterface::setSynchronousWindowSystemEvents(synchronousWindowSystemEvents);
    m_windowFrameMarginsEnabled = config[QStringLiteral("windowFrameMargins")].toBool(true);
    QJsonArray screens = config[QStringLiteral("screens")].toArray();
    for (QJsonValue screenValue : screens) {
        QJsonObject screen  = screenValue.toObject();
        if (screen.isEmpty()) {
            qWarning("QAmigaIntegration::initializeWithPlatformArguments: empty screen object");
            continue;
        }
        QAmigaScreen *amigaScreen = new QAmigaScreen(this);
        amigaScreen->m_name = screen[QStringLiteral("name")].toString();
        amigaScreen->m_geometry = QRect(screen[QStringLiteral("x")].toInt(0), screen[QStringLiteral("y")].toInt(0),
                                            screen[QStringLiteral("width")].toInt(640), screen[QStringLiteral("height")].toInt(480));
        amigaScreen->m_logicalDpi = screen[QStringLiteral("logicalDpi")].toInt(96);
        amigaScreen->m_logicalBaseDpi = screen[QStringLiteral("logicalBaseDpi")].toInt(96);
        amigaScreen->m_dpr = screen[QStringLiteral("dpr")].toDouble(1.0);

        m_screens.append(amigaScreen);
        QWindowSystemInterface::handleScreenAdded(amigaScreen);
    }
}

void QAmigaIntegration::initialize()
{
    m_inputContext.reset(QPlatformInputContextFactory::create());
}

QPlatformInputContext *QAmigaIntegration::inputContext() const
{
    return m_inputContext.data();
}

bool QAmigaIntegration::hasCapability(QPlatformIntegration::Capability cap) const
{
    switch (cap) {
    case ThreadedPixmaps: return true;
    case MultipleWindows: return true;
    case RhiBasedRendering: return true;
    case RasterGLSurface: return true;
    default: return QPlatformIntegration::hasCapability(cap);
    }
}

QPlatformWindow *QAmigaIntegration::createPlatformWindow(QWindow *window) const
{
    char *env = getenv("QT6AMIGA_OPENGL");
    bool useOpenGL = (env && env[0] == '1') || window->surfaceType() == QWindow::OpenGLSurface;
    QPlatformWindow *w = new QAmigaWindow(window, m_windowFrameMarginsEnabled);
    if(useOpenGL)
        window->setSurfaceType(QSurface::RasterGLSurface);
    w->requestActivateWindow();
    return w;
}

QPlatformBackingStore *QAmigaIntegration::createPlatformBackingStore(QWindow *window) const
{
    char *env = getenv("QT6AMIGA_OPENGL");
    bool useOpenGL = env && env[0] == '1';
    if(window->surfaceType() == QWindow::OpenGLSurface || useOpenGL) {
        window->setSurfaceType(QSurface::RasterGLSurface);
        return new QAmigaGLBackingStore(window);
    }
    return new QAmigaBackingStore(window);
}

QAbstractEventDispatcher *QAmigaIntegration::createEventDispatcher() const
{
    if(!m_eventDispatcher)
        m_eventDispatcher = new QAmigaEventDispatcher;
    return m_eventDispatcher;
}

QPlatformNativeInterface *QAmigaIntegration::nativeInterface() const
{
    if (!m_nativeInterface)
        m_nativeInterface.reset(new QAmigaPlatformNativeInterface);
    return m_nativeInterface.get();
}

static QString themeName() { return QStringLiteral("amiga"); }

QStringList QAmigaIntegration::themeNames() const
{
    return QStringList(themeName());
}

// Restrict the styles to "fusion" to prevent native styles requiring native
// window handles (eg Windows Vista style) from being used.
class AmigaTheme : public QPlatformTheme
{
public:
    AmigaTheme() {}

    QVariant themeHint(ThemeHint h) const override
    {
        switch (h) {
        case StyleNames:
            return QVariant(QStringList(QStringLiteral("Fusion")));
        default:
            break;
        }
        return QPlatformTheme::themeHint(h);
    }

    virtual const QFont *font(Font type = SystemFont) const override
    {
        static QFont systemFont(QLatin1String("Sans Serif"), 9);
        static QFont fixedFont(QLatin1String("monospace"), 9);
        switch (type) {
        case QPlatformTheme::SystemFont:
            return &systemFont;
        case QPlatformTheme::FixedFont:
            return &fixedFont;
        default:
            return nullptr;
        }
    }
};

QPlatformTheme *QAmigaIntegration::createPlatformTheme(const QString &name) const
{
    return name == themeName() ? new AmigaTheme() : nullptr;
}

QPlatformFontDatabase *QAmigaIntegration::fontDatabase() const
{
    return m_fontDatabase.data();
}

#if QT_CONFIG(draganddrop)
QPlatformDrag *QAmigaIntegration::drag() const
{
    return m_drag.data();
}
#endif

QPlatformServices *QAmigaIntegration::services() const
{
    return m_services.data();
}

QPlatformOpenGLContext *QAmigaIntegration::createPlatformOpenGLContext(QOpenGLContext *context) const
{
    return new QAmigaOpenGLContext(context);
}

QPlatformOffscreenSurface *QAmigaIntegration::createPlatformOffscreenSurface(QOffscreenSurface *surface) const
{
    return new QAmigaOffscreenSurface(surface);
}

QList<QPlatformScreen *> QAmigaIntegration::screens() const
{
    return m_screens;
}

QT_END_NAMESPACE
