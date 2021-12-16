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

#include "qsystemsemaphore.h"
#include "qsystemsemaphore_p.h"

#include <qdebug.h>

#ifndef QT_NO_SYSTEMSEMAPHORE

#include <string.h>

QT_BEGIN_NAMESPACE

QSystemSemaphorePrivate::QSystemSemaphorePrivate() :
        amiga_sem(0), createdSemaphore(false), error(QSystemSemaphore::NoError)
{
}

void QSystemSemaphorePrivate::setErrorString(const QString &function)
{
        errorString = QLatin1String("QSystemSemaphore: unknown error!");
        error = QSystemSemaphore::UnknownError;
#if defined QSYSTEMSEMAPHORE_DEBUG
        qDebug() << errorString << "key" << key;
#endif
}

/*!
    \internal

    Setup unix_key
 */
struct AmigaSemaphore *QSystemSemaphorePrivate::handle(QSystemSemaphore::AccessMode mode)
{
    if (key.isEmpty()){
        errorString = QLatin1String("QSystemSemaphore: key is empty");
        error = QSystemSemaphore::KeyError;
        return 0;
    }

    if (0 != amiga_sem)
        return amiga_sem;

	struct AmigaSemaphore *temp = (struct AmigaSemaphore *)IExec->FindSemaphore(key.toLocal8Bit().constData());
	if(temp)
	{
		if(mode == QSystemSemaphore::Create)
		{
			errorString = QLatin1String("QSystemSemaphore::handle: requested key already exists in the system, called with mode==Create");
			error = QSystemSemaphore::AlreadyExists;
			return 0;
		}
		if(temp->qtKey != 0x12345678)
		{
			errorString = QLatin1String("QSystemSemaphore::handle: existing semaphore is not Qt!");
			error = QSystemSemaphore::NotFound;
			return 0;
		}
		createdSemaphore = false;
		amiga_sem = temp;
		return temp;
	}

    // Get semaphore
    amiga_sem = (struct AmigaSemaphore *)IExec->AllocMem(sizeof(struct AmigaSemaphore), MEMF_PUBLIC|MEMF_CLEAR);
    if (!amiga_sem)
    {
		errorString = QLatin1String("QSystemSemaphore::handle: out of mem!");
		error = QSystemSemaphore::OutOfResources;
        return 0;
    }
    amiga_sem->qtKey = 0x12345678;
	amiga_sem->semaphore.ss_Link.ln_Pri = 0;
	amiga_sem->semaphore.ss_Link.ln_Name = strdup(key.toLocal8Bit().constData());
	createdSemaphore = true;
	if(initialValue >= 0)
	{
		amiga_sem->initialValue = initialValue;
		amiga_sem->currentValue = initialValue;
	}
	else
		qDebug() << "QSystemSemaphore::handle(): negative initial value!";
	
	IExec->AddSemaphore((struct SignalSemaphore *)amiga_sem);
	
    return amiga_sem;
}

/*!
    \internal

    Cleanup the unix_key
 */
void QSystemSemaphorePrivate::cleanHandle()
{
    if (createdSemaphore && amiga_sem)
    {
		IExec->RemSemaphore((struct SignalSemaphore *)amiga_sem);
		IExec->ObtainSemaphore((struct SignalSemaphore *)amiga_sem);
		IExec->ReleaseSemaphore((struct SignalSemaphore *)amiga_sem);
		
        createdSemaphore = false;
    }
	amiga_sem = 0;
}

/*!
    \internal
 */
bool QSystemSemaphorePrivate::modifySemaphore(int count)
{
qDebug() << "modifySemaphore";

    if (0 == handle())
        return false;

	if(count == 0)
		return true;
	
	int newValue = amiga_sem->currentValue + count;
	if(newValue > amiga_sem->initialValue || newValue < 0)
	{
		errorString = QLatin1String("QSystemSemaphore::modify: count out of range!");
		error = QSystemSemaphore::PermissionDenied;
        return false;
    }
	if(count < 0)
		for(int i = 0; i > count; i--)
			IExec->ObtainSemaphore((struct SignalSemaphore *)amiga_sem);
	if(count > 0)
		for(int i = 0; i < count; i++)
			IExec->ReleaseSemaphore((struct SignalSemaphore *)amiga_sem);
	amiga_sem->currentValue = newValue;
	
    return true;
}


QT_END_NAMESPACE

#endif // QT_NO_SYSTEMSEMAPHORE
