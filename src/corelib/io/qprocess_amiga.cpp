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

//#define QPROCESS_DEBUG
#include "qdebug.h"

#ifndef QT_NO_PROCESS

#if defined QPROCESS_DEBUG
#include "qstring.h"
#include <ctype.h>

/*
    Returns a human readable representation of the first \a len
    characters in \a data.
*/
QT_BEGIN_NAMESPACE
static QByteArray qt_prettyDebug(const char *data, int len, int maxSize)
{
    if (!data) return "(null)";
    QByteArray out;
    for (int i = 0; i < len; ++i) {
        char c = data[i];
        if (isprint(c)) {
            out += c;
        } else switch (c) {
        case '\n': out += "\\n"; break;
        case '\r': out += "\\r"; break;
        case '\t': out += "\\t"; break;
        default:
            QString tmp;
            tmp.sprintf("\\%o", c);
            out += tmp.toLatin1();
        }
    }

    if (len < maxSize)
        out += "...";

    return out;
}
QT_END_NAMESPACE
#endif

#include "qplatformdefs.h"

#include "qprocess.h"
#include "qprocess_p.h"

//#include <private/qcoreapplication_p.h>
//#include <private/qthread_p.h>
#include <qfile.h>
#include <qfileinfo.h>
#include <qlist.h>
#include <qmap.h>
#include <qmutex.h>
//#include <qsemaphore.h>
#include <qthread.h>
#include <qelapsedtimer.h>

#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include <proto/exec.h>
#include <proto/dos.h>

#include <QString>
#include <QList>

QT_BEGIN_NAMESPACE

QString qt_unix_to_amiga_path_name (const QString &upath)
{
	bool startswithroot = upath.startsWith (QLatin1String("/"));
	QStringList splitlist = upath.split (QLatin1String("/"));
	QString drive;
	QString result;
	int i;

	if (startswithroot)
	{
		drive = splitlist.at(1) + QLatin1String(":");
		i = 2;
		result = drive;
	}
	else
		i = 0;

	for ( ; i < splitlist.size(); i++)
	{
		if (splitlist.at(i) == QLatin1String("."))
			continue;
		if (splitlist.at(i) == QLatin1String(".."))
		{
			result.append (QLatin1String("/"));
			continue;
		}
		result.append (splitlist.at(i));
		if (i != splitlist.size() - 1)
			result.append (QLatin1String("/"));
	}
	return result;
}

QT_BEGIN_INCLUDE_NAMESPACE
extern char **environ;
QT_END_INCLUDE_NAMESPACE

QProcessEnvironment QProcessEnvironment::systemEnvironment()
{
    QProcessEnvironment env;
    // const char *entry;
    // for (int count = 0; (entry = environ[count]); ++count) {
    //     const char *equal = strchr(entry, '=');
    //     if (!equal)
    //         continue;

    //     QByteArray name(entry, equal - entry);
    //     QByteArray value(equal + 1);
    //     env.d->vars.insert(QProcessEnvironmentPrivate::Key(name),
    //                        QProcessEnvironmentPrivate::Value(value));
    // }
    return env;
}

QAmigaPipeNotifier::~QAmigaPipeNotifier()
{}

struct QProcessInfo {
	QProcessPrivate *priv;
    int serialNumber;
};

class QProcessManager : public QThread
{
    Q_OBJECT
public:
    QProcessManager();
    ~QProcessManager();

    void run();
    void add(QProcess *process);
    void remove(QProcess *process);
    void lock();
    void unlock();

private:
    QMutex mutex;
    QMap<int, QProcessInfo *> children;
};

struct qt_processMsg
{
	struct Message msg;
	QProcessPrivate *d;
};

static struct MsgPort *qt_processPort = 0;

Q_GLOBAL_STATIC(QMutex, processManagerGlobalMutex)

static QProcessManager *processManager() {
    // The constructor of QProcessManager should be called only once
    // so we cannot use Q_GLOBAL_STATIC directly for QProcessManager
    QMutex *mutex = processManagerGlobalMutex();
    QMutexLocker locker(mutex);
    static QProcessManager processManager;
    return &processManager;
}

QProcessManager::QProcessManager()
{
	IDOS->AddBuffers("PIPE:", 100);
#if defined (QPROCESS_DEBUG)
    qDebug() << "QProcessManager::QProcessManager()";
#endif
}

QProcessManager::~QProcessManager()
{
	terminate();
    wait();

    qDeleteAll(children.values());
    children.clear();
    
    if(qt_processPort)
    	IExec->FreeSysObject(ASOT_PORT, qt_processPort);
    qt_processPort = 0;
}

void QProcessManager::run()
{
	qt_processPort = IExec->AllocSysObjectTags(ASOT_PORT, TAG_DONE);

    forever {
#if defined (QPROCESS_DEBUG)
        qDebug() << "QProcessManager::run() waiting for children to die";
#endif

		struct qt_processMsg *msg = 0;
		IExec->WaitPort(qt_processPort);
		while((msg = (struct qt_processMsg *)IExec->GetMsg(qt_processPort)))
		{
			IExec->DebugPrintF("Got a MSG!\n");
			QProcessPrivate *d = msg->d;
			//QProcess *q = d->q_func();
			IExec->FreeSysObject(ASOT_MESSAGE, msg);
			if(d)
			{
				char data = '@';
				IDOS->Write(d->deathPipe[1], &data, 1);
				if(IDOS->GetFileSize(d->stdoutChannel.pipe[0]) > 0)
					emit d->stdoutChannel.notifier->activated();
				if(IDOS->GetFileSize(d->stderrChannel.pipe[0]) > 0)
					emit d->stderrChannel.notifier->activated();
				emit d->deathnotifier->activated();
				return;				
			}
		}
    }
}

static QBasicAtomicInt idCounter = Q_BASIC_ATOMIC_INITIALIZER(1);

void QProcessManager::add(QProcess *process)
{
#if defined (QPROCESS_DEBUG)
    qDebug() << "QProcessManager::add() adding aproc" << (void *)aproc << "process" << process;
#endif

    // insert a new info structure for this process
    QProcessInfo *info = new QProcessInfo;
    QProcessPrivate *priv = process->d_func();
    info->priv = priv;

    int serial = idCounter.fetchAndAddRelaxed(1);
    priv->serial = serial;
    children.insert(serial, info);
}

void QProcessManager::remove(QProcess *process)
{
    QMutexLocker locker(&mutex);

    int serial = process->d_func()->serial;
    QProcessInfo *info = children.value(serial);
    if (!info)
        return;

#if defined (QPROCESS_DEBUG)
    qDebug() << "QProcessManager::remove() removing amigaProcess" << info->amigaProcess << "process" << info->process;
#endif

    children.remove(serial);
    delete info;
}

void QProcessManager::lock()
{
    mutex.lock();
}

void QProcessManager::unlock()
{
    mutex.unlock();
}

int amiga_pipe(BPTR fd[2])
{
	struct ExamineData *data;
	char filename[120];
	char filename2[120];
	int ret=0;

	fd[1] = IDOS->Open ("PIPE:/4096/8/UNIQUE", MODE_NEWFILE);
	if (fd[1] == NULL)
	{
		printf("DOS couldn't open PIPE:/UNIQUE\n");
		return(-1);
	}
	data = IDOS->ExamineObjectTags(EX_FileHandleInput, fd[1], TAG_END);
	if (data == NULL)
	{
		IDOS->PrintFault(IDOS->IoErr(),NULL); /* failure - why ? */
		IDOS->Close(fd[1]);
		return(-1);
	}

	strlcpy(filename, "PIPE:", sizeof(filename));
	strlcat(filename, data->Name, sizeof(filename));
	IDOS->FreeDosObject(DOS_EXAMINEDATA, data);

	strlcpy(filename2, filename, sizeof(filename));
	//strlcat(filename2, "/NOBLOCK", sizeof(filename2));
	//printf("pipe(): [0] = \"%s\" [1] = \"%s\"\n", filename, filename2);
	fd[0] = IDOS->Open (filename2, MODE_OLDFILE);
	IDOS->SetBlockingMode (fd[0], SBM_NON_BLOCKING);


	if (fd[0] == NULL)
	{
		IDOS->Close(fd[1]);
		printf("DOS couldn't open %s\n", filename2);
		return(-1);
	}
	return (0);
}

void amiga_closepipe(BPTR fd[2])
{
	if(fd[0] > 0) { IDOS->Close(fd[0]); fd[0] = -1; }
	if(fd[1] > 0) { IDOS->Close(fd[1]); fd[1] = -1; }
}

void QProcessPrivate::destroyPipe(Q_PIPE *pipe)
{
	amiga_closepipe(pipe);
}

void QProcessPrivate::closeChannel(Channel *channel)
{
    delete channel->notifier;
    channel->notifier = nullptr;

    destroyPipe(channel->pipe);
}

void QProcessPrivate::cleanup()
{
    q_func()->setProcessState(QProcess::NotRunning);

    closeChannels();
    delete stateNotifier;
    stateNotifier = nullptr;
    destroyPipe(childStartedPipe);
    pid = 0;
    if (forkfd != -1) {
        /*qt_safe_*/close(forkfd);
        forkfd = -1;
    }
}

/*
    Create the pipes to a QProcessPrivate::Channel.

    This function must be called in order: stdin, stdout, stderr
*/

bool QProcessPrivate::openChannel(Channel &channel)
{
    Q_Q(QProcess);

    if (&channel == &stderrChannel && processChannelMode == QProcess::MergedChannels) {
        channel.pipe[0] = INVALID_Q_PIPE;
        channel.pipe[1] = INVALID_Q_PIPE;
        return true;
    }

    if (channel.type == Channel::Normal) {
        // we're piping this channel to our own process
        amiga_pipe(channel.pipe);

        if (1) {//threadData->eventDispatcher) {
            if (&channel == &stdinChannel) {
				// do nothing
				;
            } else {
            	QAmigaPipeNotifier *notifier = new QAmigaPipeNotifier;
                const char *receiver;
                if (&channel == &stdoutChannel)
                    receiver = SLOT(_q_canReadStandardOutput());
                else
                    receiver = SLOT(_q_canReadStandardError());
                QObject::connect(notifier, SIGNAL(activated()),
                                 q, receiver);
            }
        }

        return true;
    }
	return false;
}

#if 0
static char **_q_dupEnvironment(const QHash<QByteArray, QByteArray> &environment, int *envc)
{
    *envc = 0;
    if (environment.isEmpty())
        return 0;

    // if LD_LIBRARY_PATH exists in the current environment, but
    // not in the environment list passed by the programmer, then
    // copy it over.
#if defined(Q_OS_MAC)
    static const char libraryPath[] = "DYLD_LIBRARY_PATH";
#else
    static const char libraryPath[] = "LD_LIBRARY_PATH";
#endif
    const QByteArray envLibraryPath = qgetenv(libraryPath);
    bool needToAddLibraryPath = !envLibraryPath.isEmpty() &&
                                !environment.contains(libraryPath);

    char **envp = new char *[environment.count() + 2];
    envp[environment.count()] = 0;
    envp[environment.count() + 1] = 0;

    QHash<QByteArray, QByteArray>::ConstIterator it = environment.constBegin();
    const QHash<QByteArray, QByteArray>::ConstIterator end = environment.constEnd();
    for ( ; it != end; ++it) {
        QByteArray key = it.key();
        QByteArray value = it.value();
        key.reserve(key.length() + 1 + value.length());
        key.append('=');
        key.append(value);

        envp[(*envc)++] = ::strdup(key.constData());
    }

    if (needToAddLibraryPath)
        envp[(*envc)++] = ::strdup(QByteArray(libraryPath) + '=' +
                                 envLibraryPath);
    return envp;
}
#endif

STATIC VOID ASM qt_exitfunc(	REG(D0, LONG return_code),
							 	REG(D1, LONG exit_data))
{
	struct QProcessPrivate *priv = (QProcessPrivate *)exit_data;
	priv->processState = QProcess::NotRunning;
	priv->exitCode = return_code;
	if(qt_processPort)
	{
		struct qt_processMsg *msg = (struct qt_processMsg *)IExec->AllocSysObjectTags(ASOT_MESSAGE, ASOMSG_Size, sizeof(struct qt_processMsg), TAG_DONE);
		msg->d = priv;
		IExec->PutMsg(qt_processPort, (struct Message *)msg);
	}
}

/* A child process that waits for 10 seconds then exits. */
STATIC int32 newprocesschildproc(STRPTR *args UNUSED, int32 arglen UNUSED,
	                       struct ExecBase *sysbase)
{
	struct QProcessPrivate *priv = IDOS->GetEntryData();
	int ret = IDOS->SystemTags(priv->fullCommand,
								SYS_Input,			IDOS->Input(),
								SYS_Output,			IDOS->Output(),
								SYS_Error,			IDOS->ErrorOutput(),
								NP_StackSize,	1000000,
								TAG_END);
	if(ret < 0)
		IExec->DebugPrintF("IDOS->SystemTags FAILED!\n");
	else
		IExec->DebugPrintF("IDOS->SystemTags SUCCEDED!\n");

	priv->processState = QProcess::NotRunning;
	priv->exitCode = ret;
	if(qt_processPort)
	{
		struct qt_processMsg *msg = (struct qt_processMsg *)IExec->AllocSysObjectTags(ASOT_MESSAGE, ASOMSG_Size, sizeof(struct qt_processMsg), TAG_DONE);
		msg->d = priv;
		IExec->PutMsg(qt_processPort, (struct Message *)msg);
	}
	return ret;
}


extern QString qt_unix_to_amiga_path_name(const QString&);

void QProcessPrivate::startProcess()
{
    Q_Q(QProcess);

#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::startProcess()");
#endif

    processManager()->start();

    // Initialize pipes
    if (!openChannel(stdinChannel) ||
        !openChannel(stdoutChannel) ||
        !openChannel(stderrChannel))
        return;

    amiga_pipe(childStartedPipe);
    amiga_pipe(deathPipe);

	deathnotifier->disconnect();
	QObject::connect(deathnotifier, SIGNAL(activated()), q, SLOT(_q_processDied()));

    // Start the process (platform dependent)
    q->setProcessState(QProcess::Starting);

    // Encode the program name
	QString full = qt_unix_to_amiga_path_name(program);
    for(int i = 0; i < arguments.size(); i++)
    {
        QString s = arguments[i];
    	full += " ";
    	full += "\"";
    	full += s;
    	full += "\"";
    }

#if 0
    // Duplicate the environment.
    int envc = 0;
    char **envp = 0;
    if (environment.d.constData())
        envp = _q_dupEnvironment(environment.d.constData()->hash, &envc);
#endif

    // Start the process manager, and fork off the child process.
    processManager()->lock();

	fullCommand = strdup(full.toLocal8Bit().constData());
	qDebug() << "fullCommand = " << fullCommand;

	struct Process *me = (struct Process *)IExec->FindTask(NULL);
	BPTR currentDirLock = IDOS->Lock(qt_unix_to_amiga_path_name(workingDirectory).toLocal8Bit().constData(), SHARED_LOCK);	
	if(!currentDirLock)
		currentDirLock = me->pr_CurrentDir;

#if 0
	if(!IDOS->CreateNewProcTags( 
		NP_Entry, newprocesschildproc, 

		NP_Child, TRUE,
		NP_EntryData, this,

		NP_Input, stdinChannel.pipe[0],
		NP_CloseInput, FALSE,
		NP_Output, (processChannelMode == QProcess::ForwardedChannels ? IDOS->Input() : stdoutChannel.pipe[1]),
		NP_CloseOutput, FALSE,
		NP_Error, (processChannelMode == QProcess::ForwardedChannels
					? IDOS->ErrorOutput()
					: (processChannelMode == QProcess::MergedChannels ? stdoutChannel.pipe[1] : stderrChannel.pipe[1]) ),
		NP_CloseError, FALSE,

		NP_CurrentDir, currentDirLock,

	    TAG_DONE))
	{
		IDOS->PrintFault(IDOS->IoErr(), "startnewprocess: ");
	}
#else
	BPTR in = IDOS->DupFileHandle(stdinChannel.pipe[0]);
	BPTR out = IDOS->DupFileHandle( (processChannelMode == QProcess::ForwardedChannels ? IDOS->Input() : stdoutChannel.pipe[1]) );
	BPTR err = IDOS->DupFileHandle( (processChannelMode == QProcess::ForwardedChannels
														? IDOS->ErrorOutput()
														: (processChannelMode == QProcess::MergedChannels ? stdoutChannel.pipe[1] : stderrChannel.pipe[1]) ));
	int ret = IDOS->SystemTags(fullCommand,
								SYS_Asynch,			TRUE,
								SYS_Input,			in,
								SYS_Output,			out,
								SYS_Error,			err,
								NP_Child, TRUE,
								NP_CurrentDir, currentDirLock,
								NP_StackSize,	1000000,
								NP_ExitCode, qt_exitfunc,
								NP_ExitData, this,
								TAG_END);

	IExec->DebugPrintF("QProcess: IDOS->SystemTags return code: %d\n", ret);
#endif

    // Register the child. In the mean time, we can get a SIGCHLD, so we need
    // to keep the lock held to avoid a race to catch the child.
    processManager()->add(q);
    processManager()->unlock();
}

bool QProcessPrivate::processStarted(QString *errorMessage)
{
	return (processState != QProcess::NotRunning);
}

qint64 QProcessPrivate::bytesAvailableInChannel(const Channel *channel) const
{
    int nbytes = IDOS->GetFileSize(channel->pipe[0]);
    qint64 available = (qint64) nbytes;

#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::bytesAvailableFromStdout() == %lld", available);
#endif
    return available;
}
/*
qint64 QProcessPrivate::bytesAvailableFromStderr() const
{
    int nbytes = IDOS->GetFileSize(stderrChannel.pipe[0]);
    qint64 available = (qint64) nbytes;

#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::bytesAvailableFromStderr() == %lld", available);
#endif
    return available;
}
*/

//    qint64 readFromChannel(const Channel *channel, char *data, qint64 maxlen);

qint64 QProcessPrivate::readFromChannel(const Channel *channel, char *data, qint64 maxlen)
{
	qint64 bytesRead = (qint64)IDOS->Read(channel->pipe[0], data, maxlen);
#if defined QPROCESS_DEBUG
    qDebug("QProcessPrivate::readFromStdout(%p \"%s\", %lld) == %lld",
           data, qt_prettyDebug(data, bytesRead, 16).constData(), maxlen, bytesRead);
#endif
    return bytesRead;
}
/*
qint64 QProcessPrivate::readFromStderr(char *data, qint64 maxlen)
{
    qint64 bytesRead = (qint64)IDOS->Read(stderrChannel.pipe[0], data, maxlen);
#if defined QPROCESS_DEBUG
    qDebug("QProcessPrivate::readFromStderr(%p \"%s\", %lld) == %lld",
           data, qt_prettyDebug(data, bytesRead, 16).constData(), maxlen, bytesRead);
#endif
    return bytesRead;
}
*/
#if 0
static void qt_ignore_sigpipe()
{
    // Set to ignore SIGPIPE once only.
    static QBasicAtomicInt atom = Q_BASIC_ATOMIC_INITIALIZER(0);
    if (atom.testAndSetRelaxed(0, 1)) {
#if 0
        struct sigaction noaction;
        memset(&noaction, 0, sizeof(noaction));
        noaction.sa_handler = SIG_IGN;
        ::sigaction(SIGPIPE, &noaction, 0);
#endif
    }
}
#endif

/*! \reimp
*/
qint64 QProcess::writeData(const char *data, qint64 len)
{
    Q_D(QProcess);

    if (d->stdinChannel.closed) {
#if defined QPROCESS_DEBUG
        qDebug("QProcess::writeData(%p \"%s\", %lld) == 0 (write channel closing)",
               data, QtDebugUtils::toPrintable(data, len, 16).constData(), len);
#endif
        return 0;
    }

    d->write(data, len);
    if (d->stdinChannel.notifier)
        d->stdinChannel.notifier->setEnabled(true);

#if defined QPROCESS_DEBUG
    qDebug("QProcess::writeData(%p \"%s\", %lld) == %lld (written to buffer)",
           data, QtDebugUtils::toPrintable(data, len, 16).constData(), len, len);
#endif
    return len;
}

bool QProcessPrivate::_q_canWrite()
{
    if (writeBuffer.isEmpty()) {
        if (stdinChannel.notifier)
            stdinChannel.notifier->setEnabled(false);
#if defined QPROCESS_DEBUG
        qDebug("QProcessPrivate::canWrite(), not writing anything (empty write buffer).");
#endif
        return false;
    }

    const bool writeSucceeded = writeToStdin();

    if (writeBuffer.isEmpty() && stdinChannel.closed)
        closeWriteChannel();
    else if (stdinChannel.notifier)
        stdinChannel.notifier->setEnabled(!writeBuffer.isEmpty());

    return writeSucceeded;
}

bool QProcessPrivate::writeToStdin() //const char *data, qint64 maxlen)
{
    //qt_ignore_sigpipe();

    const char *data = writeBuffer.readPointer();
    const qint64 bytesToWrite = writeBuffer.nextDataBlockSize();

    qint64 written = (qint64)IDOS->Write(stdinChannel.pipe[1], data, bytesToWrite);
#if defined QPROCESS_DEBUG
    qDebug("QProcessPrivate::writeToStdin(), write(%p \"%s\", %lld) == %lld", data,
           QtDebugUtils::toPrintable(data, bytesToWrite, 16).constData(), bytesToWrite, written);
    if (written == -1)
        qDebug("QProcessPrivate::writeToStdin(), failed to write (%ls)", qUtf16Printable(qt_error_string(errno)));
#endif
    if (written == -1) {
        // If the O_NONBLOCK flag is set and If some data can be written without blocking
        // the process, write() will transfer what it can and return the number of bytes written.
        // Otherwise, it will return -1 and set errno to EAGAIN
        if (errno == EAGAIN)
            return true;

        closeChannel(&stdinChannel);
        setErrorAndEmit(QProcess::WriteError);
        return false;
    }
    writeBuffer.free(written);
    if (!emittedBytesWritten && written != 0) {
        emittedBytesWritten = true;
        emit q_func()->bytesWritten(written);
        emittedBytesWritten = false;
    }
    return true;
}

void QProcessPrivate::terminateProcess()
{
#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::killProcess()");
#endif
	//we can't kill it, only send it a break
	if (pid)
		IExec->Signal(pid, SIGBREAKF_CTRL_C);
}

void QProcessPrivate::killProcess()
{
#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::killProcess()");
#endif
    if (pid)
		IExec->Signal(pid, SIGBREAKF_CTRL_C);
        //::kill(pid_t(pid), SIGKILL);
}

#if 0
static int select_msecs(int nfds, fd_set *fdread, fd_set *fdwrite, int timeout)
{
    if (timeout < 0)
        return qt_safe_select(nfds, fdread, fdwrite, 0, 0);

    struct timeval tv;
    tv.tv_sec = timeout / 1000;
    tv.tv_usec = (timeout % 1000) * 1000;
    return qt_safe_select(nfds, fdread, fdwrite, 0, &tv);
}
#endif

/*
   Returns the difference between msecs and elapsed. If msecs is -1,
   however, -1 is returned.
*/
#if 0
static int qt_timeout_value(int msecs, int elapsed)
{
    if (msecs == -1)
        return -1;

    int timeout = msecs - elapsed;
    return timeout < 0 ? 0 : timeout;
}
#endif

bool QProcessPrivate::waitForStarted(const QDeadlineTimer &deadline)
{
    const qint64 msecs = deadline.remainingTime();
#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::waitForStarted(%lld) waiting for child to start (fd = %d)",
           msecs, childStartedPipe[0]);
#endif
/*
    pollfd pfd = qt_make_pollfd(childStartedPipe[0], POLLIN);

    if (qt_poll_msecs(&pfd, 1, msecs) == 0) {
        setError(QProcess::Timedout);
#if defined (QPROCESS_DEBUG)
        qDebug("QProcessPrivate::waitForStarted(%lld) == false (timed out)", msecs);
#endif
        return false;
    }

    bool startedEmitted = _q_startupNotification();
#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::waitForStarted() == %s", startedEmitted ? "true" : "false");
#endif
    return startedEmitted;
    */
   return true;
}

//    bool waitForReadyRead(const QDeadlineTimer &deadline);

bool QProcessPrivate::waitForReadyRead(const QDeadlineTimer &deadline)
{
    Q_Q(QProcess);
#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::waitForReadyRead(%lld)", deadline.remainingTime());
#endif

int msecs = deadline.remainingTime();

    QElapsedTimer stopWatch;
    stopWatch.start();

	bool ended = false;
	int outsize = 0;
	int errorsize = 0;
	while(stopWatch.elapsed() < msecs || msecs == -1)
	{
		outsize = IDOS->GetFileSize(stdoutChannel.pipe[0]);
		errorsize = IDOS->GetFileSize(stderrChannel.pipe[0]);
		char dummy;
		int bytes = IDOS->Read(deathPipe[0], &dummy, 1);
		if(bytes > 0)
		{
			ended = true;
			break;
		}
		if(outsize > 0 || errorsize > 0)
			break;
		IDOS->Delay(50);
	}
	if(outsize > 0)
		_q_canReadStandardOutput();
	if(errorsize > 0)
		_q_canReadStandardError();

	if(ended)
		_q_processDied();
	else
		_q_canWrite();
	
	return (outsize > 0 || errorsize > 0);
}

bool QProcessPrivate::waitForBytesWritten(const QDeadlineTimer &deadline)
{
#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::waitForBytesWritten(%lld)", deadline.remainingTime());
#endif
int msecs = deadline.remainingTime();

    QElapsedTimer stopWatch;
    stopWatch.start();

	bool ended = false;
	int outsize = 0;
	int errorsize = 0;
	while(stopWatch.elapsed() < msecs || msecs == -1)
	{
		outsize = IDOS->GetFileSize(stdoutChannel.pipe[0]);
		errorsize = IDOS->GetFileSize(stderrChannel.pipe[0]);
		char dummy;
		int bytes = IDOS->Read(deathPipe[0], &dummy, 1);
		if(bytes > 0)
		{
			ended = true;
			break;
		}
		if(outsize > 0 || errorsize > 0)
			break;
		IDOS->Delay(50);
	}
	if(outsize > 0)
		_q_canReadStandardOutput();
	if(errorsize > 0)
		_q_canReadStandardError();

	if(ended)
		_q_processDied();
	else
		_q_canWrite();
		
	return (outsize > 0 || errorsize > 0);
}

bool QProcessPrivate::waitForFinished(const QDeadlineTimer &deadline)
{
#if defined (QPROCESS_DEBUG)
    qDebug("QProcessPrivate::waitForFinished(%lld)", deadline.remainingTime());
#endif
int msecs = deadline.remainingTime();

    QElapsedTimer stopWatch;
    stopWatch.start();

	if (processState == QProcess::NotRunning)
		return true;

	bool ended = false;
	while(stopWatch.elapsed() < msecs || msecs == -1)
	{
		char dummy;
		int bytes = IDOS->Read(deathPipe[0], &dummy, 1);
		if(bytes > 0)
		{
			ended = true;
			break;
		}
		IDOS->Delay(50);
	}

	if(IDOS->GetFileSize(stdoutChannel.pipe[0]) > 0)
		_q_canReadStandardOutput();
	if(IDOS->GetFileSize(stderrChannel.pipe[0]) > 0)
		_q_canReadStandardError();

	if(ended)
	{
		_q_processDied();
        return true;
	}
	_q_canWrite();
	return false;
}

// bool QProcessPrivate::waitForWrite(int msecs)
// {
// /*
//     fd_set fdwrite;
//     FD_ZERO(&fdwrite);
//     FD_SET(stdinChannel.pipe[1], &fdwrite);
//     return select_msecs(stdinChannel.pipe[1] + 1, 0, &fdwrite, msecs < 0 ? 0 : msecs) == 1;
// */
// 	//blaa...
// 	return true;
// }

// void QProcessPrivate::findExitCode()
// {
//     Q_Q(QProcess);
//     processManager()->remove(q);
// }

void QProcessPrivate::waitForDeadChild()
{
    Q_Q(QProcess);
    //this is of course 100% unsafe...
}


    bool QProcessPrivate::startDetached(qint64 *pPid)

//bool QProcessPrivate::startDetached(const QString &program, const QStringList &arguments, const QString &workingDirectory, qint64 *pid)
{
//qDebug() << "startDetached: " << workingDirectory << program << arguments << ";";
    //processManager()->start();

    QByteArray encodedWorkingDirectory = QFile::encodeName(workingDirectory);

    // const CharPointerList argv(resolveExecutable(program), arguments);
    // const CharPointerList envp(environment.d.constData());

	QString args (arguments.join(" "));
	QString full = workingDirectory;
	if(full.length() && !full.endsWith(':') && !full.endsWith('/'))
		full += '/';
	full += program;
	full += " ";
	full += args;
	char *command = strdup(full.toLocal8Bit().constData());
	
	BPTR in = IDOS->Open("nil:", MODE_OLDFILE);
	BPTR out = IDOS->Open("nil:", MODE_NEWFILE);
	BPTR err = IDOS->Open("nil:", MODE_NEWFILE);
	int ret = IDOS->SystemTags(command,
								SYS_Asynch,		TRUE,
								SYS_Input,			in,
								SYS_Output,			out,
								SYS_Error,			err,
								//NP_ExitCode,	qt_exitfunc,
								NP_CloseError,	TRUE,
								NP_StackSize,	1000000,
								//NP_NotifyOnDeathSigTask, NULL,
								TAG_END);

#if 0
    // To catch the startup of the child
    int startedPipe[2];
    qt_safe_pipe(startedPipe);
    // To communicate the pid of the child
    int pidPipe[2];
    qt_safe_pipe(pidPipe);

    pid_t childPid = qt_fork();
    if (childPid == 0) {
        struct sigaction noaction;
        memset(&noaction, 0, sizeof(noaction));
        noaction.sa_handler = SIG_IGN;
        ::sigaction(SIGPIPE, &noaction, 0);

        ::setsid();

        qt_safe_close(startedPipe[0]);
        qt_safe_close(pidPipe[0]);

        pid_t doubleForkPid = qt_fork();
        if (doubleForkPid == 0) {
            qt_safe_close(pidPipe[1]);

            if (!encodedWorkingDirectory.isEmpty())
                QT_CHDIR(encodedWorkingDirectory.constData());

            char **argv = new char *[arguments.size() + 2];
            for (int i = 0; i < arguments.size(); ++i) {
#ifdef Q_OS_MAC
                argv[i + 1] = ::strdup(arguments.at(i).toUtf8().constData());
#else
                argv[i + 1] = ::strdup(arguments.at(i).toLocal8Bit().constData());
#endif
            }
            argv[arguments.size() + 1] = 0;

            if (!program.contains(QLatin1Char('/'))) {
                const QString path = QString::fromLocal8Bit(::getenv("PATH"));
                if (!path.isEmpty()) {
                    QStringList pathEntries = path.split(QLatin1Char(':'));
                    for (int k = 0; k < pathEntries.size(); ++k) {
                        QByteArray tmp = QFile::encodeName(pathEntries.at(k));
                        if (!tmp.endsWith('/')) tmp += '/';
                        tmp += QFile::encodeName(program);
                        argv[0] = tmp.data();
                        qt_safe_execv(argv[0], argv);
                    }
                }
            } else {
                QByteArray tmp = QFile::encodeName(program);
                argv[0] = tmp.data();
                qt_safe_execv(argv[0], argv);
            }

            struct sigaction noaction;
            memset(&noaction, 0, sizeof(noaction));
            noaction.sa_handler = SIG_IGN;
            ::sigaction(SIGPIPE, &noaction, 0);

            // '\1' means execv failed
            char c = '\1';
            qt_safe_write(startedPipe[1], &c, 1);
            qt_safe_close(startedPipe[1]);
            ::_exit(1);
        } else if (doubleForkPid == -1) {
            struct sigaction noaction;
            memset(&noaction, 0, sizeof(noaction));
            noaction.sa_handler = SIG_IGN;
            ::sigaction(SIGPIPE, &noaction, 0);

            // '\2' means internal error
            char c = '\2';
            qt_safe_write(startedPipe[1], &c, 1);
        }

        qt_safe_close(startedPipe[1]);
        qt_safe_write(pidPipe[1], (const char *)&doubleForkPid, sizeof(pid_t));
        QT_CHDIR("/");
        ::_exit(1);
    }

    qt_safe_close(startedPipe[1]);
    qt_safe_close(pidPipe[1]);

    if (childPid == -1) {
        qt_safe_close(startedPipe[0]);
        qt_safe_close(pidPipe[0]);
        return false;
    }

    char reply = '\0';
    int startResult = qt_safe_read(startedPipe[0], &reply, 1);
    int result;
    qt_safe_close(startedPipe[0]);
    qt_safe_waitpid(childPid, &result, 0);
    bool success = (startResult != -1 && reply == '\0');
    if (success && pid) {
        pid_t actualPid = 0;
        if (qt_safe_read(pidPipe[0], (char *)&actualPid, sizeof(pid_t)) == sizeof(pid_t)) {
            *pid = actualPid;
        } else {
            *pid = 0;
        }
    }
    qt_safe_close(pidPipe[0]);
    return success;
#endif
	return false;
}

void QProcessPrivate::initializeProcessManager()
{
    (void) processManager();
}

QT_END_NAMESPACE

#include "qprocess_amiga.moc"

#endif // QT_NO_PROCESS
