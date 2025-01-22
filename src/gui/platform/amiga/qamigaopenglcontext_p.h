#ifndef QAMIGAOPENGLCONTEXT_p_h
#define QAMIGAOPENGLCONTEXT_p_h

#include <QtCore/qhash.h>
#include <qpa/qplatformopenglcontext.h>
#include <qpa/qplatformsurface.h>
#include "qamigawindow_p.h"
#include "qamigaoffscreensurface_p.h"

#include <proto/exec.h>
#include <proto/ogles2.h>

QT_BEGIN_NAMESPACE

extern struct Library *OGLES2Library;
extern struct OGLES2IFace *IOGLES2;

class QAmigaOpenGLContext : public QPlatformOpenGLContext
{
private:
    static int noContexts;
    
private:
    void *aglContext, *share;
    QOpenGLContext *context;
    QPlatformSurface *surface;

public:
    QAmigaOpenGLContext(QOpenGLContext *context) : QPlatformOpenGLContext(), aglContext(0), share(0), surface(0) //, bitmap(0), shareContext(0), window(0)
    {
#if 1
        if(!OGLES2Library) { OGLES2Library = IExec->OpenLibrary("ogles2.library", 0);
            if(OGLES2Library) IOGLES2 = (struct OGLES2IFace *) IExec->GetInterface(OGLES2Library, "main", 1, NULL); }
        if(!OGLES2Library) { qFatal("ogles2.library not found. OpenGL ES2 rendering is not possible on this platform.\n"); exit(20); }
        noContexts++;
        this->context = context;
#endif
    }

    ~QAmigaOpenGLContext()
    {
        if (aglContext) { aglDestroyContext(aglContext); }
#if 1
        if (--noContexts == 0 && OGLES2Library) {
            if(IOGLES2) IExec->DropInterface((struct Interface *)IOGLES2);
            IExec->CloseLibrary(OGLES2Library);
            OGLES2Library = 0;
        }
#endif
    }

    QSurfaceFormat format() const override
    {
        QSurfaceFormat format;
        format.setRenderableType(QSurfaceFormat::OpenGLES);
        format.setRedBufferSize(8);
        format.setGreenBufferSize(8);
        format.setBlueBufferSize(8);
        format.setAlphaBufferSize(8);
        return format;
    }

    void swapBuffers(QPlatformSurface */*platformSurface*/) override
    {
        aglSwapBuffers();
    }

    bool isSharing() const override
    {
        return context->shareContext();
    }

    bool makeCurrent(QPlatformSurface *platformSurface) override
    {
        QOpenGLContext *shareContext = context->shareContext();
        QAmigaOpenGLContext *newShare = shareContext ? static_cast<QAmigaOpenGLContext *>(shareContext->handle()) : 0;

        QAmigaWindow *amigaWindow = dynamic_cast<QAmigaWindow *>(platformSurface);
        QAmigaOffscreenSurface *offscreenSurface = dynamic_cast<QAmigaOffscreenSurface *>(platformSurface);
        
        if (surface != platformSurface || newShare->aglContext != share) {
            surface = platformSurface;
            share = newShare->aglContext;

            if (amigaWindow) amigaWindow->setGl(true);

            if(IOGLES2 && (offscreenSurface || amigaWindow)) {
                if (aglContext) aglDestroyContext(aglContext);
                aglContext = 0;
                ULONG errCode = 0;
                aglContext = aglCreateContextTags2(&errCode, 
                    offscreenSurface ? TAG_IGNORE : (int)OGLES2_CCT_WINDOW, amigaWindow ? amigaWindow->intuitionWindow() : offscreenSurface->nativeHandle(),
                    offscreenSurface ? (int)OGLES2_CCT_MODEID : TAG_IGNORE, 0,
                    share ? (int)OGLES2_CCT_SHARE_WITH : TAG_IGNORE, share, 
                    OGLES2_CCT_DEPTH, 32,
                    OGLES2_CCT_STENCIL, 8,
                    OGLES2_CCT_VSYNC, 0,
                    OGLES2_CCT_SINGLE_GET_ERROR_MODE, 1,
                    TAG_DONE);
            }
        }

        if(aglContext) {
            aglMakeCurrent(aglContext);
            return true;
        }
        return false;
    }

    void doneCurrent() override
    {
    }

    QFunctionPointer getProcAddress(const char *procName) override;
};

QT_END_NAMESPACE

#endif
