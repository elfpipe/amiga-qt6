/****************************************************************************
**
** Copyright (C) 2020 The Qt Company Ltd.
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

#include "qamigaoffscreensurface_p.h"

QT_BEGIN_NAMESPACE

QAmigaOffscreenSurface::QAmigaOffscreenSurface(QOffscreenSurface *offscreenSurface)
    : QPlatformOffscreenSurface(offscreenSurface)
{
    QSize size = offscreenSurface->size();
    m_surface = IIntuition->OpenWindowTags(NULL,
								WA_Title,				"",
								WA_SimpleRefresh,		TRUE,
								WA_InnerWidth,			800, //size.width(),
								WA_InnerHeight,			600, //size.height(),
								WA_BackFill, 			LAYERS_NOBACKFILL,
                                // WA_Hidden,              TRUE,
    
								TAG_DONE);
 		// int32 w=400, h=400;
		// const char titleStrBase[] = "Hello OpenGLES2";
		// m_surface=IIntuition->OpenWindowTags(NULL,
		// 						WA_Title,				titleStrBase,
		// 						WA_Activate,			TRUE,
		// 						WA_RMBTrap,				TRUE,
		// 						WA_DragBar,				TRUE,
		// 						WA_DepthGadget,			TRUE,
		// 						WA_SimpleRefresh,		TRUE,
		// 						WA_SizeGadget,			TRUE,
		// 						WA_CloseGadget,			TRUE,
		// 						WA_IDCMP,				IDCMP_REFRESHWINDOW | IDCMP_NEWSIZE | 
		// 												IDCMP_CLOSEWINDOW | IDCMP_RAWKEY,
		// 						WA_InnerWidth,			w,
		// 						WA_InnerHeight,			h,
		// 						WA_MinWidth,			100,
		// 						WA_MinHeight,			100,
		// 						WA_MaxWidth,			2048,
		// 						WA_MaxHeight,			2048,
		// 						WA_BackFill, 			LAYERS_NOBACKFILL,
		// 						TAG_DONE);
}

QAmigaOffscreenSurface::~QAmigaOffscreenSurface()
{
    IIntuition->CloseWindow(m_surface);
}

QSurfaceFormat QAmigaOffscreenSurface::format() const
{
    QSurfaceFormat format;
    format.setRenderableType(QSurfaceFormat::OpenGLES);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    return format;
}

bool QAmigaOffscreenSurface::isValid() const
{
    return m_surface != 0;
}

QT_END_NAMESPACE

