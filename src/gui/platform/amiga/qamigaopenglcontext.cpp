#include "qamigaopenglcontext_p.h"
#include <proto/ogles2.h>

QT_BEGIN_NAMESPACE

int QAmigaOpenGLContext::noContexts = 0;
struct Library *OGLES2Library;
struct OGLES2IFace *IOGLES2;

QFunctionPointer QAmigaOpenGLContext::getProcAddress(const char *procName)
{
    return QFunctionPointer(aglGetProcAddress(procName));
}

QT_END_NAMESPACE