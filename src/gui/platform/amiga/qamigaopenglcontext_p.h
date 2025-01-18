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

#define QAMIGAOPENGL_USE_WINDOW_DIRECT      0
#define QAMIGAOPENGL_USE_SCREEN_DIRECT      0
#define QAMIGAOPENGL_USE_BITMAP_TO_WINDOW   1

extern struct Screen *qt_intuition_screen;

class QAmigaOpenGLContext : public QPlatformOpenGLContext
{
private:
    static int noContexts;

private:
    void *aglContext;
    // struct BitMap *bitmap;
    QOpenGLContext *context;
    QAmigaWindow *window;

private:
    // int width, height;
    // struct Window *window;

public:
    QAmigaOpenGLContext(QOpenGLContext *context) : QPlatformOpenGLContext(), aglContext(0), window(0) //, bitmap(0), shareContext(0), window(0)
    {
        if(!OGLES2Library) { OGLES2Library = IExec->OpenLibrary("ogles2.library", 0);
            if(OGLES2Library) IOGLES2 = (struct OGLES2IFace *) IExec->GetInterface(OGLES2Library, "main", 1, NULL); }
        if(!OGLES2Library) { qFatal("ogles2.library not found. OpenGL ES2 rendering is not possible on this platform.\n"); exit(20); }
        noContexts++;
        this->context = context;

//         QSurface *surface = 0; //shareContext ? shareContext->surface () : context->surface();

//         width = surface ? surface->size().width() : 640;
//         height = surface ? surface->size().height() : 480;
        
//         // if(surface) printf("Opening window for context surface.\n");

// 		window = IIntuition->OpenWindowTags(NULL,
// 								WA_Title,				"Qt6 OpenGL",
// 								WA_Activate,			TRUE,
// 								WA_RMBTrap,				TRUE,
// 								WA_DragBar,				TRUE,
// 								WA_DepthGadget,			TRUE,
// 								WA_SimpleRefresh,		TRUE,
// 								WA_SizeGadget,			TRUE,
// 								WA_CloseGadget,			TRUE,
// 								WA_IDCMP,				IDCMP_REFRESHWINDOW | IDCMP_NEWSIZE | 
// 														IDCMP_CLOSEWINDOW | IDCMP_RAWKEY,
// 								// WA_Width,			1920,
// 								// WA_Height,			1080,
// 								WA_Width,			width,
// 								WA_Height,			height,
// 								// WA_MaxWidth,			2048,
// 								// WA_MaxHeight,			2048,
// 								WA_BackFill, 			LAYERS_NOBACKFILL,

// #if QAMIGAOPENGL_USE_BITMAP_TO_WINDOW
//                                 WA_Hidden,              TRUE,
// #endif
// 								TAG_DONE);


// 		qt_intuition_screen = IIntuition->OpenScreenTags (NULL,
// 													SA_LikeWorkbench, TRUE,
// 													SA_Depth, 32,
// 													SA_Type, CUSTOMSCREEN,
// 													// SA_PubName, qt_public_screen,
// 													// SA_Title, "Qt 4.7.0",
// 													SA_ShowTitle, FALSE,
// 													//SA_Quiet, TRUE,
// 													  TAG_END);

//         bitmap = IGraphics->AllocBitMapTags(width, height, 0,
//                                             BMATags_Friend,         window->RPort->BitMap,
//                                             // BMATags_Friend,         &qt_intuition_screen->BitMap,
//                                             BMATags_Displayable,    TRUE,
//                                             TAG_DONE);

//         // bitmap = IGraphics->AllocBitMapTags(width, height, 32,
//         //                         BMATags_PixelFormat, PIXF_A8R8G8B8,
//         //                         BMATags_Displayable, TRUE,
//         //                         TAG_DONE);
//         // if(!bitmap) printf("Failed to allocate bitmap.\n");

//         if(IOGLES2) {
//             ULONG errCode = 0, disp_width, disp_height;
//             aglContext = aglCreateContextTags2(&errCode, 
//                 // OGLES2_CCT_WINDOW, window,
//                 // OGLES2_CCT_MODEID, 0,
//                 OGLES2_CCT_BITMAP, bitmap,
//                 // OGLES2_CCT_BITMAP, window->RPort->BitMap,
// 				OGLES2_CCT_DEPTH,32,
// 				OGLES2_CCT_STENCIL,8,
// 				OGLES2_CCT_VSYNC,0,
// 				OGLES2_CCT_SINGLE_GET_ERROR_MODE,1,
// 				OGLES2_CCT_GET_WIDTH,&disp_width,
// 				OGLES2_CCT_GET_HEIGHT,&disp_height,
//                 // OGLES2_CCT_RESIZE_VIEWPORT, TRUE,
//                 TAG_DONE);
//             if (aglContext == 0 || errCode) {
//                 printf("Error opening OpenGL context. Code : %d.\n", errCode); exit(20);
//             } else aglMakeCurrent(aglContext);
//                 // glClear(GL_COLOR_BUFFER_BIT);
//                 // glViewport(0, 0, disp_width, disp_height);
//                 // glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
//             printf("Successfully created context. (0x%x) (%d x %d)\n", (void *)aglContext, disp_width, disp_height);
//         }
    }
    ~QAmigaOpenGLContext()
    {
        if (aglContext) { aglDestroyContext(aglContext); }
        // if (window) window->setGl(false);
        if (--noContexts == 0 && OGLES2Library) {
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

    void swapBuffers(QPlatformSurface */*platformSurface*/) override
    {
        aglSwapBuffers();
    }

    bool makeCurrent(QPlatformSurface *platformSurface) override
    {
        QOpenGLContext *shareContext = context->shareContext();
        if (shareContext) {
            QAmigaOpenGLContext *share = static_cast<QAmigaOpenGLContext *>(shareContext->handle());
           if(share) return share->makeCurrent(platformSurface);
        }

        QAmigaWindow *amigaWindow = dynamic_cast<QAmigaWindow *>(platformSurface);

        if(amigaWindow && window != amigaWindow) {
            window = amigaWindow;
            window->setGl(true);
            if(IOGLES2) {
                if(aglContext) aglDestroyContext(aglContext);
                aglContext = 0;
                ULONG errCode = 0;
                aglContext = aglCreateContextTags2(&errCode, 
                    OGLES2_CCT_WINDOW, window->intuitionWindow(),
                    OGLES2_CCT_DEPTH,32,
                    OGLES2_CCT_STENCIL,8,
                    OGLES2_CCT_VSYNC,0,
                    OGLES2_CCT_SINGLE_GET_ERROR_MODE,1,
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
        // aglMakeCurrent(0);
    }

    QFunctionPointer getProcAddress(const char *procName) override;
};

QT_END_NAMESPACE

#endif
