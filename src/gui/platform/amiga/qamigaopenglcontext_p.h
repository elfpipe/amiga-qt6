#ifndef QAMIGAOPENGLCONTEXT_p_h
#define QAMIGAOPENGLCONTEXT_p_h

#include <QtCore/qhash.h>
#include <qpa/qplatformopenglcontext.h>
#include <qpa/qplatformsurface.h>
#include "qamigawindow_p.h"

#include <proto/exec.h>
#include <proto/ogles2.h>
#include <inline4/ogles2.h>
extern struct Library *OGLES2Library;

#include <proto/graphics.h>
#include <proto/intuition.h>

void aglActiveTexture(GLenum texture);
void aglAttachShader(GLuint program, GLuint shader);
void aglBindAttribLocation(GLuint program, GLuint index, const GLchar * name);
void aglBindBuffer(GLenum target, GLuint buffer);
void aglBindFramebuffer(GLenum target, GLuint framebuffer);
void aglBindRenderbuffer(GLenum target, GLuint renderbuffer);
void aglBindTexture(GLenum target, GLuint texture);
void aglBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void aglBlendEquation(GLenum mode);
void aglBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
void aglBlendFunc(GLenum sfactor, GLenum dfactor);
void aglBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
void aglBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
void aglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
GLenum aglCheckFramebufferStatus(GLenum target);
void aglClear(GLbitfield mask);
void aglClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void aglClearDepthf(GLfloat d);
void aglClearStencil(GLint s);
void aglColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
void aglCompileShader(GLuint shader);
void aglCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
void aglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
void aglCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
void aglCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLuint aglCreateProgram();
GLuint aglCreateShader(GLenum type);
void aglCullFace(GLenum mode);
void aglDeleteBuffers(GLsizei n, const GLuint * buffers);
void aglDeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
void aglDeleteProgram(GLuint program);
void aglDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
void aglDeleteShader(GLuint shader);
void aglDeleteTextures(GLsizei n, const GLuint * textures);
void aglDepthFunc(GLenum func);
void aglDepthMask(GLboolean flag);
void aglDepthRangef(GLfloat n, GLfloat f);
void aglDetachShader(GLuint program, GLuint shader);
void aglDisable(GLenum cap);
void aglDisableVertexAttribArray(GLuint index);
void aglDrawArrays(GLenum mode, GLint first, GLsizei count);
void aglDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices);
void aglEnable(GLenum cap);
void aglEnableVertexAttribArray(GLuint index);
void aglFinish();
void aglFlush();
void aglFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void aglFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void aglFrontFace(GLenum mode);
void aglGenBuffers(GLsizei n, GLuint * buffers);
void aglGenerateMipmap(GLenum target);
void aglGenFramebuffers(GLsizei n, GLuint * framebuffers);
void aglGenRenderbuffers(GLsizei n, GLuint * renderbuffers);
void aglGenTextures(GLsizei n, GLuint * textures);
void aglGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void aglGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void aglGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
GLint aglGetAttribLocation(GLuint program, const GLchar * name);
void aglGetBooleanv(GLenum pname, GLboolean * data);
void aglGetBufferParameteriv(GLenum target, GLenum pname, GLint * params);
GLenum aglGetError();
void aglGetFloatv(GLenum pname, GLfloat * data);
void aglGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params);
void aglGetIntegerv(GLenum pname, GLint * data);
void aglGetProgramiv(GLuint program, GLenum pname, GLint * params);
void aglGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void aglGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params);
void aglGetShaderiv(GLuint shader, GLenum pname, GLint * params);
void aglGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void aglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
void aglGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
const GLubyte *aglGetString(GLenum name);
void aglGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params);
void aglGetTexParameteriv(GLenum target, GLenum pname, GLint * params);
void aglGetUniformfv(GLuint program, GLint location, GLfloat * params);
void aglGetUniformiv(GLuint program, GLint location, GLint * params);
GLint aglGetUniformLocation(GLuint program, const GLchar * name);
void aglGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params);
void aglGetVertexAttribiv(GLuint index, GLenum pname, GLint * params);
void aglGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer);
void aglHint(GLenum target, GLenum mode);
GLboolean aglIsBuffer(GLuint buffer);
GLboolean aglIsEnabled(GLenum cap);
GLboolean aglIsFramebuffer(GLuint framebuffer);
GLboolean aglIsProgram(GLuint program);
GLboolean aglIsRenderbuffer(GLuint renderbuffer);
GLboolean aglIsShader(GLuint shader);
GLboolean aglIsTexture(GLuint texture);
void aglLineWidth(GLfloat width);
void aglLinkProgram(GLuint program);
void aglPixelStorei(GLenum pname, GLint param);
void aglPolygonOffset(GLfloat factor, GLfloat units);
void aglReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
void aglReleaseShaderCompiler();
void aglRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void aglSampleCoverage(GLfloat value, GLboolean invert);
void aglScissor(GLint x, GLint y, GLsizei width, GLsizei height);
void aglShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length);
void aglShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
void aglStencilFunc(GLenum func, GLint ref, GLuint mask);
void aglStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
void aglStencilMask(GLuint mask);
void aglStencilMaskSeparate(GLenum face, GLuint mask);
void aglStencilOp(GLenum fail, GLenum zfail, GLenum zpass);
void aglStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
void aglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
void aglTexParameterf(GLenum target, GLenum pname, GLfloat param);
void aglTexParameterfv(GLenum target, GLenum pname, const GLfloat * params);
void aglTexParameteri(GLenum target, GLenum pname, GLint param);
void aglTexParameteriv(GLenum target, GLenum pname, const GLint * params);
void aglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
void aglUniform1f(GLint location, GLfloat v0);
void aglUniform1fv(GLint location, GLsizei count, const GLfloat * value);
void aglUniform1i(GLint location, GLint v0);
void aglUniform1iv(GLint location, GLsizei count, const GLint * value);
void aglUniform2f(GLint location, GLfloat v0, GLfloat v1);
void aglUniform2fv(GLint location, GLsizei count, const GLfloat * value);
void aglUniform2i(GLint location, GLint v0, GLint v1);
void aglUniform2iv(GLint location, GLsizei count, const GLint * value);
void aglUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void aglUniform3fv(GLint location, GLsizei count, const GLfloat * value);
void aglUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
void aglUniform3iv(GLint location, GLsizei count, const GLint * value);
void aglUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void aglUniform4fv(GLint location, GLsizei count, const GLfloat * value);
void aglUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void aglUniform4iv(GLint location, GLsizei count, const GLint * value);
void aglUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void aglUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void aglUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void aglUseProgram(GLuint program);
void aglValidateProgram(GLuint program);
void aglVertexAttrib1f(GLuint index, GLfloat x);
void aglVertexAttrib1fv(GLuint index, const GLfloat * v);
void aglVertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
void aglVertexAttrib2fv(GLuint index, const GLfloat * v);
void aglVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
void aglVertexAttrib3fv(GLuint index, const GLfloat * v);
void aglVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void aglVertexAttrib4fv(GLuint index, const GLfloat * v);
void aglVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
void aglViewport(GLint x, GLint y, GLsizei width, GLsizei height);

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
        // shareContext = context->shareContext();

        if(!OGLES2Library) { OGLES2Library = IExec->OpenLibrary("ogles2.library", 0);
            if(OGLES2Library) IOGLES2 = (struct OGLES2IFace *) IExec->GetInterface(OGLES2Library, "main", 1, NULL); }
        if(!OGLES2Library) { printf("ogles2.library not found. OpenGL ES2 rendering is not possible on this platform.\n"); return; }
        noContexts++;

        QSurface *surface = shareContext ? shareContext->surface () : context->surface();

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

        if(shareContext) { printf("Creating a shared context.\n"); return; }

        bitmap = IGraphics->AllocBitMapTags(width, height, 32,
                                BMATags_PixelFormat, PIXF_A8R8G8B8,
                                BMATags_Displayable, TRUE,
                                TAG_DONE);
        if(!bitmap) printf("Failed to allocate bitmap.\n");

        if(IOGLES2) {
            ULONG errCode = 0, disp_width, disp_height;
            aglContext = aglCreateContextTags(&errCode, 
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
        printf("swapBuffers()\n");
        if(!IOGLES2) return;
        QAmigaOpenGLContext *share = this;
        if(shareContext)
            share = static_cast<QAmigaOpenGLContext *>(shareContext->handle());
        if(share && share->aglContext) { aglMakeCurrent(share->aglContext); }
#if 1
        QSurface *surface = /*shareContext ? shareContext->surface () :*/ platformSurface ? platformSurface->surface() : 0;
        // platformSurface = shareContext && surface ? surface->surfaceHandle() : platformSurface;
        QAmigaWindow *amigaWindow = dynamic_cast<QAmigaWindow *>(platformSurface);
        if(!amigaWindow) printf("swapBuffers : Failed to find  amiga window.\n");

        width = surface ? surface->size().width() : width;
        height = surface ? surface->size().height() : height;

        if(amigaWindow && amigaWindow->intuitionWindow() && share->bitmap) {
            printf("=========== BLIT ===========.\n");
            IGraphics->BltBitMapRastPort(
            share->bitmap,
            0, 0,
            amigaWindow->intuitionWindow()->RPort,
            0, 0,
            width, height,
            0xc0);
        }
#endif
        aglSwapBuffers();
    }
    bool makeCurrent(QPlatformSurface *platformSurface) override
    {
        printf("makeCurrent()\n");
        if(!IOGLES2) return false;
        QAmigaOpenGLContext *share = this;
        if(shareContext) {
            share = static_cast<QAmigaOpenGLContext *>(shareContext->handle());
            if(!share) printf("ERRRORRRR !!!!!!!!!!!!!!!!!!!!!!!! ===================.\n");
        }
        if(share && share->aglContext) { aglMakeCurrent(share->aglContext); } else printf("Errrorrr!!\n");

        // aglMakeCurrent(aglContext);
        
#if 1
        QSurface *surface = /*shareContext ? shareContext->surface () :*/ platformSurface ? platformSurface->surface() : 0;
        if(!surface) printf("ERROR AGAIN!!!!!!!!\n");
//        platformSurface = shareContext && surface ? surface->surfaceHandle() : platformSurface;
        // QAmigaWindow *amigawindow = dynamic_cast<QAmigaWindow *>(platformSurface);
        // if(!amigaWindow) printf("swapBuffers : Failed to find  amiga window.\n");

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

        if(bitmap) aglSetBitmap(bitmap); else printf("BIIIIIIG ERRROR!!!!\n");
#endif
        return true;


        // QSurface *surface = shareContext ? shareContext->surface () : platformSurface->surface();
        // platformSurface = shareContext ? surface->surfaceHandle() : platformSurface;
        // QamigaWindow *amiga = 0;
        // amiga = dynamic_cast<QamigaWindow *>(platformSurface);
 
        // if(!amiga) printf("Failed to find  amiga window.\n");

        // if(bitmap) IGraphics->FreeBitMap(bitmap);
        // bitmap = 0;
        // if(surface)
    }
    void doneCurrent() override
    {
        // if(bitmap) IGraphics->FreeBitMap(bitmap);
        // bitmap = 0;
    }
    QFunctionPointer getProcAddress(const char *procName) override;
};
#endif
