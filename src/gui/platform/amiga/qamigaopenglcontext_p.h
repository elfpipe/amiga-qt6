#ifndef QAMIGAOPENGLCONTEXT_p_h
#define QAMIGAOPENGLCONTEXT_p_h

#include <QtCore/qhash.h>
#include <qpa/qplatformopenglcontext.h>
#include <qpa/qplatformsurface.h>
#include "qamigawindow_p.h"

#include <proto/exec.h>
#include <proto/ogles2.h>

#include <proto/graphics.h>
#include <proto/intuition.h>

QT_BEGIN_NAMESPACE

extern struct Library *OGLES2Library;
extern struct OGLES2IFace *IOGLES2;

class QAmigaOpenGLContext : public QPlatformOpenGLContext
{
private:
    static int noContexts;

private:
    void *aglContext;
    struct BitMap *bitmap;
    QOpenGLContext *shareContext;

private:
    int width, height;
    struct Window *window;

public:
    QAmigaOpenGLContext(QOpenGLContext *context) : QPlatformOpenGLContext(), aglContext(0), bitmap(0), shareContext(0), window(0)
    {
        if(!OGLES2Library) { OGLES2Library = IExec->OpenLibrary("ogles2.library", 0);
            if(OGLES2Library) IOGLES2 = (struct OGLES2IFace *) IExec->GetInterface(OGLES2Library, "main", 1, NULL); }
        if(!OGLES2Library) { printf("ogles2.library not found. OpenGL ES2 rendering is not possible on this platform.\n"); return; }
        noContexts++;

        QSurface *surface = 0; //shareContext ? shareContext->surface () : context->surface();

        width = surface ? surface->size().width() : 320;
        height = surface ? surface->size().height() : 240;
        
        // if(surface) printf("Opening window for context surface.\n");

		// window=IIntuition->OpenWindowTags(NULL,
		// 						WA_Title,				"Qt6 OpenGL",
		// 						WA_Activate,			TRUE,
		// 						WA_RMBTrap,				TRUE,
		// 						WA_DragBar,				TRUE,
		// 						WA_DepthGadget,			TRUE,
		// 						WA_SimpleRefresh,		TRUE,
		// 						WA_SizeGadget,			TRUE,
		// 						WA_CloseGadget,			TRUE,
		// 						WA_IDCMP,				IDCMP_REFRESHWINDOW | IDCMP_NEWSIZE | 
		// 												IDCMP_CLOSEWINDOW | IDCMP_RAWKEY,
		// 						WA_InnerWidth,			width,
		// 						WA_InnerHeight,			height,
		// 						WA_MinWidth,			100,
		// 						WA_MinHeight,			100,
		// 						WA_MaxWidth,			2048,
		// 						WA_MaxHeight,			2048,
		// 						WA_BackFill, 			LAYERS_NOBACKFILL,
		// 						TAG_DONE);

        bitmap = IGraphics->AllocBitMapTags(width, height, 32,
                                BMATags_PixelFormat, PIXF_A8R8G8B8,
                                BMATags_Displayable, TRUE,
                                TAG_DONE);
        if(!bitmap) printf("Failed to allocate bitmap.\n");

        if(IOGLES2) {
            ULONG errCode = 0, disp_width, disp_height;
            aglContext = aglCreateContextTags2(&errCode, 
                // OGLES2_CCT_WINDOW, window,
                // OGLES2_CCT_MODEID, 0,
                OGLES2_CCT_BITMAP, bitmap,
				OGLES2_CCT_DEPTH,32,
				OGLES2_CCT_STENCIL,8,
				OGLES2_CCT_VSYNC,0,
				OGLES2_CCT_SINGLE_GET_ERROR_MODE,1,
				OGLES2_CCT_GET_WIDTH,&disp_width,
				OGLES2_CCT_GET_HEIGHT,&disp_height,
                TAG_DONE);
            if (aglContext == 0 || errCode) {
                printf("Error opening OpenGL context. Code : %d.\n", errCode);
            } else aglMakeCurrent(aglContext);
        }
        printf("Successfully created context. (0x%x)\n", (void *)aglContext);
    }
    ~QAmigaOpenGLContext()
    {
        printf("Destroy context.(0x%x)\n",(void *)aglContext);
        if(aglContext) { aglMakeCurrent(aglContext); aglDestroyContext(aglContext); }
        printf("Destroy bitmap.\n");
        if(bitmap) IGraphics->FreeBitMap(bitmap);
        if(window) IIntuition->CloseWindow(window);
        if(--noContexts == 0 && OGLES2Library) {
            printf("Closing ogles2.library.\n");
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
        QSurface *surface = platformSurface ? platformSurface->surface() : 0;
        QAmigaWindow *amigaWindow = dynamic_cast<QAmigaWindow *>(platformSurface);

        QAmigaOpenGLContext *share = this;
        if(shareContext) share = static_cast<QAmigaOpenGLContext *>(shareContext->handle());

        if(amigaWindow && amigaWindow->intuitionWindow() && bitmap) {
            IGraphics->BltBitMapRastPort(
            bitmap,
            0, 0,
            amigaWindow->intuitionWindow()->RPort,
            0, 0,
            width, height,
            0xc0);
        }
        aglSwapBuffers();
    }
    bool makeCurrent(QPlatformSurface *platformSurface) override
    {
        QAmigaOpenGLContext *share = this;
        if(shareContext) {
            share = static_cast<QAmigaOpenGLContext *>(shareContext->handle());
        }
        if(aglContext) { printf("MakeCurrent.\n"); aglMakeCurrent(aglContext); }

        QSurface *surface = platformSurface ? platformSurface->surface() : 0;

        int newWidth = surface ? surface->size().width() : width;
        int newHeight = surface ? surface->size().height() : height;

        if(newWidth != width || newHeight != height) {
            if(bitmap) IGraphics->FreeBitMap(bitmap);
            bitmap = IGraphics->AllocBitMapTags(newWidth, newHeight, 32,
                        BMATags_PixelFormat, PIXF_A8R8G8B8,
                        BMATags_Displayable, TRUE,
                        TAG_DONE);
        }
        width = newWidth;
        height = newHeight;

        if(bitmap) aglSetBitmap(bitmap);
        return true;
    }
    void doneCurrent() override
    {
    }
    QFunctionPointer getProcAddress(const char *procName) override;
};

QT_END_NAMESPACE

#endif
