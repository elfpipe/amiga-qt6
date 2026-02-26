#include "qamigaglcontext.h"
#include <proto/ogles2.h>

QT_BEGIN_NAMESPACE

int QAmigaOpenGLContext::noContexts = 0;
struct Library *OGLES2Library;
struct OGLES2IFace *IOGLES2;

struct Screen *qt_intuition_screen = 0;

QFunctionPointer QAmigaOpenGLContext::getProcAddress(const char *procName)
{
    return QFunctionPointer(aglGetProcAddress(procName));
}

QT_END_NAMESPACE