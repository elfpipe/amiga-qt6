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

#ifndef QAmigaCOMMON_H
#define QAmigaCOMMON_H

#include <qpa/qplatformbackingstore.h>
#if QT_CONFIG(draganddrop)
#include <qpa/qplatformdrag.h>
#endif
#include <qpa/qplatformintegration.h>
#include <qpa/qplatformnativeinterface.h>
#include <qpa/qplatformscreen.h>
#include <qpa/qplatformwindow.h>

#include <qscopedpointer.h>
#include <qimage.h>
#include <qhash.h>

QT_BEGIN_NAMESPACE

class QAmigaIntegration;
class QAmigaScreen : public QPlatformScreen
{
public:
    QAmigaScreen(const QAmigaIntegration *integration);

    QRect geometry() const override { return m_geometry; }
    int depth() const override { return 32; }
    QImage::Format format() const override { return QImage::Format_RGB32; }
    QDpi logicalDpi() const override { return QDpi(m_logicalDpi, m_logicalDpi); }
    QDpi logicalBaseDpi() const override { return QDpi(m_logicalBaseDpi, m_logicalBaseDpi); }
    qreal devicePixelRatio() const override { return m_dpr; }
    QString name() const override { return m_name; }
    QPlatformCursor *cursor() const override { return m_cursor.data(); }
    QList<QPlatformScreen *> virtualSiblings() const override;

    QPixmap grabWindow(WId window, int x, int y, int width, int height) const override;

    static QPlatformWindow *windowContainingCursor;

public:
    QString m_name;
    QRect m_geometry;
    int m_logicalDpi = 96;
    int m_logicalBaseDpi= 96;
    qreal m_dpr = 1;
    QScopedPointer<QPlatformCursor> m_cursor;
    const QAmigaIntegration *m_integration;
};

#if QT_CONFIG(draganddrop)
class QAmigaDrag : public QPlatformDrag
{
public:
    Qt::DropAction drag(QDrag *) override { return Qt::IgnoreAction; }
};
#endif

class QAmigaBackingStore : public QPlatformBackingStore
{
public:
    QAmigaBackingStore(QWindow *window);
    ~QAmigaBackingStore();

    QPaintDevice *paintDevice() override;
    void flush(QWindow *window, const QRegion &region, const QPoint &offset) override;
    void resize(const QSize &size, const QRegion &staticContents) override;
    bool scroll(const QRegion &area, int dx, int dy) override;

    QPixmap grabWindow(WId window, const QRect &rect) const;
    QImage toImage() const override { return m_image; }

    static QAmigaBackingStore *backingStoreForWinId(WId id);

private:
    void clearHash();

    QImage m_image;
    QHash<WId, QRect> m_windowAreaHash;

    static QHash<WId, QAmigaBackingStore *> m_backingStoreForWinIdHash;
};

class QAmigaPlatformNativeInterface : public QPlatformNativeInterface
{
public:
    ~QAmigaPlatformNativeInterface();
};

QT_END_NAMESPACE

#endif