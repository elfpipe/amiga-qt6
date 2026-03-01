#ifndef QAMIGAOPENGLCONTEXT_p_h
#define QAMIGAOPENGLCONTEXT_p_h

// #include <GL/gl.h>
// #include <GL/glext.h>

#include <QtCore/qhash.h>
#include <qpa/qplatformopenglcontext.h>
#include <qpa/qplatformsurface.h>

#include "qamigawindow.h"
#include "qamigaoffscreensurface.h"

#include <proto/exec.h>
#include <inline4/ogles2.h>
#include <proto/ogles2.h>
#include <proto/graphics.h>

#ifdef glPolygonMode
#undef glPolygonMode
#endif

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
    struct Window *dummyW;
    // struct BitMap *dummyBM;

public:
    QAmigaOpenGLContext(QOpenGLContext *context) : QPlatformOpenGLContext(), aglContext(0), share(0), surface(0)
    {
        if(!OGLES2Library) { OGLES2Library = IExec->OpenLibrary("ogles2.library", 0);
            if(OGLES2Library) IOGLES2 = (struct OGLES2IFace *) IExec->GetInterface(OGLES2Library, "main", 1, NULL); }
        if(!OGLES2Library || !IOGLES2) { qFatal("ogles2.library not found. OpenGL ES2 rendering is not possible on this platform.\n"); exit(20); }
        noContexts++;

        this->context = context;

        QOpenGLContext *shareContext = context->shareContext();
        QAmigaOpenGLContext *newShare = shareContext ? static_cast<QAmigaOpenGLContext *>(shareContext->handle()) : 0;
        share = newShare ? newShare->aglContext : 0;

        // struct Screen *workbench = IIntuition->LockPubScreen(0);
		// dummyBM = IGraphics->AllocBitMapTags(64, 64, 0, BMATags_Friend, &workbench->BitMap, BMATags_Displayable, TRUE, TAG_DONE);

        dummyW = IIntuition->OpenWindowTags(NULL,
            WA_Title,				"",
            WA_SimpleRefresh,		TRUE,
            WA_InnerWidth,			640,
            WA_InnerHeight,			480,
            WA_BackFill, 			LAYERS_NOBACKFILL,
            WA_Hidden,              TRUE,    
            TAG_DONE);

        ULONG errCode = 0;
        aglContext = aglCreateContextTags2(&errCode, 
            OGLES2_CCT_WINDOW, dummyW,
            // OGLES2_CCT_BITMAP, dummyBM,
            share ? (int)OGLES2_CCT_SHARE_WITH : TAG_IGNORE, share, 
            OGLES2_CCT_DEPTH, 32,
            OGLES2_CCT_STENCIL, 8,
            OGLES2_CCT_VSYNC, 0,
            OGLES2_CCT_SINGLE_GET_ERROR_MODE, 1,
            TAG_DONE);
        qInfo() << "== OpenGL ==" << "\n" << 
                   "aglContext : " << aglContext << "\n";
    }

    ~QAmigaOpenGLContext()
    {
        if (aglContext) { aglDestroyContext(aglContext); }
        if (dummyW) { IIntuition->CloseWindow(dummyW); }
        if (--noContexts == 0 && OGLES2Library) {
            if(IOGLES2) IExec->DropInterface((struct Interface *)IOGLES2);
            IExec->CloseLibrary(OGLES2Library);
            OGLES2Library = 0;
        }
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

    void swapBuffers(QPlatformSurface *platformSurface) override
    {
        qInfo() << "== OpenGL ==" << "\n" << 
                   "swapBuffers" << "\n";
        makeCurrent(platformSurface);
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

        qInfo() << "== OpenGL ==" << "\n" << 
                   "aglContext : " << aglContext << "\n";

        if(!aglContext)
            return false;
        
        if (aglContext)
            aglMakeCurrent(aglContext);

        if (surface != platformSurface) {
            surface = platformSurface;
            struct Window *window = amigaWindow ? amigaWindow->intuitionWindow() : (offscreenSurface ? offscreenSurface->nativeHandle() : 0);
            if (!window)
                window = dummyW;

            if (window) {
                aglSetParamsTags2(
                    OGLES2_CCT_WINDOW, window,
                    TAG_DONE);
            }
        }

        if (newShare && newShare->aglContext != share) {
            share = newShare->aglContext;
            aglSetParamsTags2(
                OGLES2_CCT_SHARE_WITH, share,
                TAG_DONE);
        }
#if 0
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
#endif

        qInfo() << "== OpenGL ==" << "\n" << 
                   "makeCurrent EXIT" << "\n";

        return true;
    }

    void doneCurrent() override
    {
        aglMakeCurrent(nullptr);
    }

    QFunctionPointer getProcAddress(const char *procName) override;
};

QT_END_NAMESPACE

#endif
