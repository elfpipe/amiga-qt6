/****************************************************************************
**
** Copyright (C) 2010 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial Usage
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Nokia.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qplatformdefs.h"

#include "qsharedmemory.h"
#include "qsharedmemory_p.h"
#include "qsystemsemaphore.h"
#include <qdir.h>
#include <qdebug.h>

#include <proto/exec.h>

#ifndef QT_NO_SHAREDMEMORY
QT_BEGIN_NAMESPACE

QSharedMemoryPrivate::QSharedMemoryPrivate()
    : QObjectPrivate(), memory(0), size(0), error(QSharedMemory::NoError),
#ifndef QT_NO_SYSTEMSEMAPHORE
      systemSemaphore(QString()), lockedByMe(false),
#endif
      amiga_key(0)
{
}

void QSharedMemoryPrivate::setErrorString(QLatin1String function)
{
	qDebug() << function;
}

/*!
    \internal

    If not already made create the handle used for accessing the shared memory.
*/
STRPTR QSharedMemoryPrivate::handle()
{
    // already made
    if (amiga_key)
        return amiga_key;

    // don't allow making handles on empty keys
    if (key.isEmpty()) {
        errorString = QSharedMemory::tr("%1: key is empty").arg(QLatin1String("QSharedMemory::handle:"));
        error = QSharedMemory::KeyError;
        qDebug() << "error:" << errorString;
        return 0;
    }

    QString keystr = makePlatformSafeKey(key);
    amiga_key = (STRPTR)IExec->AllocVecTags(1024, TAG_END);
    strcpy(amiga_key, (const char *)keystr.toLatin1());
    return amiga_key;
}

bool QSharedMemoryPrivate::cleanHandle()
{
    amiga_key = 0;
    return true;
}

bool QSharedMemoryPrivate::create(int size)
{
    // get handle
    if (!handle()) {
        return false;
    }

    // create
    uint32 err;
	aks = (struct amiga_key_struct *)IExec->AllocNamedMemoryTags(size+sizeof(amiga_key_struct), "Qt", amiga_key, ANMT_Error, &err, TAG_END);
	switch(err)
	{
		case ANMERROR_NOERROR:
			break;
		case ANMERROR_NOMEMORY:
	        errorString = QSharedMemory::tr("QSharedMemoryPrivate::create(): out of resources");
	        error = QSharedMemory::OutOfResources;
	        return false;
	    case ANMERROR_DUPLICATENAME:
	        errorString = QSharedMemory::tr("QSharedMemoryPrivate::create(): already exists");
	        error = QSharedMemory::AlreadyExists;
	        return false;
		default:
	        errorString = QSharedMemory::tr("QSharedMemoryPrivate::create(): unknown error!");
	        error = QSharedMemory::UnknownError;
	}
	if(aks)
	{
		aks->size = size;
		this->size = size;
		aks->count = 0;
		//memory = (void *)((uint32)aks + sizeof(struct amiga_key_struct));
	    return true;
	}
	return false;
}

bool QSharedMemoryPrivate::attach(QSharedMemory::AccessMode mode)
{
    // grab the shared memory segment id
    if (!handle())
        return false;
	
	aks = (struct amiga_key_struct *)IExec->FindNamedMemory("Qt", amiga_key);
	if(aks)
	{
		size = aks->size;
		aks->count++;
		memory = (void *)((uint32)aks + sizeof(struct amiga_key_struct));
		
	    return true;
	}
	else
		return false;
}

bool QSharedMemoryPrivate::detach()
{
	if(aks)
	{
		aks->count--;
		if(aks->count == 0)
		{
			IExec->FreeNamedMemory("Qt", amiga_key);
		}
	}
    memory = 0;
    return true;
}


QT_END_NAMESPACE

#endif // QT_NO_SHAREDMEMORY

