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

void Q_GUI_EXPORT aglActiveTexture(GLenum texture);
void Q_GUI_EXPORT aglAttachShader(GLuint program, GLuint shader);
void Q_GUI_EXPORT aglBindAttribLocation(GLuint program, GLuint index, const GLchar * name);
void Q_GUI_EXPORT aglBindBuffer(GLenum target, GLuint buffer);
void Q_GUI_EXPORT aglBindFramebuffer(GLenum target, GLuint framebuffer);
void Q_GUI_EXPORT aglBindRenderbuffer(GLenum target, GLuint renderbuffer);
void Q_GUI_EXPORT aglBindTexture(GLenum target, GLuint texture);
void Q_GUI_EXPORT aglBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void Q_GUI_EXPORT aglBlendEquation(GLenum mode);
void Q_GUI_EXPORT aglBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
void Q_GUI_EXPORT aglBlendFunc(GLenum sfactor, GLenum dfactor);
void Q_GUI_EXPORT aglBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha);
void Q_GUI_EXPORT aglBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage);
void Q_GUI_EXPORT aglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
GLenum Q_GUI_EXPORT aglCheckFramebufferStatus(GLenum target);
void Q_GUI_EXPORT aglClear(GLbitfield mask);
void Q_GUI_EXPORT aglClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
void Q_GUI_EXPORT aglClearDepthf(GLfloat d);
void Q_GUI_EXPORT aglClearStencil(GLint s);
void Q_GUI_EXPORT aglColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
void Q_GUI_EXPORT aglCompileShader(GLuint shader);
void Q_GUI_EXPORT aglCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data);
void Q_GUI_EXPORT aglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data);
void Q_GUI_EXPORT aglCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
void Q_GUI_EXPORT aglCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
GLuint Q_GUI_EXPORT aglCreateProgram();
GLuint Q_GUI_EXPORT aglCreateShader(GLenum type);
void Q_GUI_EXPORT aglCullFace(GLenum mode);
void Q_GUI_EXPORT aglDeleteBuffers(GLsizei n, const GLuint * buffers);
void Q_GUI_EXPORT aglDeleteFramebuffers(GLsizei n, const GLuint * framebuffers);
void Q_GUI_EXPORT aglDeleteProgram(GLuint program);
void Q_GUI_EXPORT aglDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers);
void Q_GUI_EXPORT aglDeleteShader(GLuint shader);
void Q_GUI_EXPORT aglDeleteTextures(GLsizei n, const GLuint * textures);
void Q_GUI_EXPORT aglDepthFunc(GLenum func);
void Q_GUI_EXPORT aglDepthMask(GLboolean flag);
void Q_GUI_EXPORT aglDepthRangef(GLfloat n, GLfloat f);
void Q_GUI_EXPORT aglDetachShader(GLuint program, GLuint shader);
void Q_GUI_EXPORT aglDisable(GLenum cap);
void Q_GUI_EXPORT aglDisableVertexAttribArray(GLuint index);
void Q_GUI_EXPORT aglDrawArrays(GLenum mode, GLint first, GLsizei count);
void Q_GUI_EXPORT aglDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices);
void Q_GUI_EXPORT aglEnable(GLenum cap);
void Q_GUI_EXPORT aglEnableVertexAttribArray(GLuint index);
void Q_GUI_EXPORT aglFinish();
void Q_GUI_EXPORT aglFlush();
void Q_GUI_EXPORT aglFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
void Q_GUI_EXPORT aglFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
void Q_GUI_EXPORT aglFrontFace(GLenum mode);
void Q_GUI_EXPORT aglGenBuffers(GLsizei n, GLuint * buffers);
void Q_GUI_EXPORT aglGenerateMipmap(GLenum target);
void Q_GUI_EXPORT aglGenFramebuffers(GLsizei n, GLuint * framebuffers);
void Q_GUI_EXPORT aglGenRenderbuffers(GLsizei n, GLuint * renderbuffers);
void Q_GUI_EXPORT aglGenTextures(GLsizei n, GLuint * textures);
void Q_GUI_EXPORT aglGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void Q_GUI_EXPORT aglGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name);
void Q_GUI_EXPORT aglGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders);
GLint Q_GUI_EXPORT aglGetAttribLocation(GLuint program, const GLchar * name);
void Q_GUI_EXPORT aglGetBooleanv(GLenum pname, GLboolean * data);
void Q_GUI_EXPORT aglGetBufferParameteriv(GLenum target, GLenum pname, GLint * params);
GLenum Q_GUI_EXPORT aglGetError();
void Q_GUI_EXPORT aglGetFloatv(GLenum pname, GLfloat * data);
void Q_GUI_EXPORT aglGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params);
void Q_GUI_EXPORT aglGetIntegerv(GLenum pname, GLint * data);
void Q_GUI_EXPORT aglGetProgramiv(GLuint program, GLenum pname, GLint * params);
void Q_GUI_EXPORT aglGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void Q_GUI_EXPORT aglGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params);
void Q_GUI_EXPORT aglGetShaderiv(GLuint shader, GLenum pname, GLint * params);
void Q_GUI_EXPORT aglGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog);
void Q_GUI_EXPORT aglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision);
void Q_GUI_EXPORT aglGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source);
const GLubyte Q_GUI_EXPORT *aglGetString(GLenum name);
void Q_GUI_EXPORT aglGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params);
void Q_GUI_EXPORT aglGetTexParameteriv(GLenum target, GLenum pname, GLint * params);
void Q_GUI_EXPORT aglGetUniformfv(GLuint program, GLint location, GLfloat * params);
void Q_GUI_EXPORT aglGetUniformiv(GLuint program, GLint location, GLint * params);
GLint Q_GUI_EXPORT aglGetUniformLocation(GLuint program, const GLchar * name);
void Q_GUI_EXPORT aglGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params);
void Q_GUI_EXPORT aglGetVertexAttribiv(GLuint index, GLenum pname, GLint * params);
void Q_GUI_EXPORT aglGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer);
void Q_GUI_EXPORT aglHint(GLenum target, GLenum mode);
GLboolean Q_GUI_EXPORT aglIsBuffer(GLuint buffer);
GLboolean Q_GUI_EXPORT aglIsEnabled(GLenum cap);
GLboolean Q_GUI_EXPORT aglIsFramebuffer(GLuint framebuffer);
GLboolean Q_GUI_EXPORT aglIsProgram(GLuint program);
GLboolean Q_GUI_EXPORT aglIsRenderbuffer(GLuint renderbuffer);
GLboolean Q_GUI_EXPORT aglIsShader(GLuint shader);
GLboolean Q_GUI_EXPORT aglIsTexture(GLuint texture);
void Q_GUI_EXPORT aglLineWidth(GLfloat width);
void Q_GUI_EXPORT aglLinkProgram(GLuint program);
void Q_GUI_EXPORT aglPixelStorei(GLenum pname, GLint param);
void Q_GUI_EXPORT aglPolygonOffset(GLfloat factor, GLfloat units);
void Q_GUI_EXPORT aglReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels);
void Q_GUI_EXPORT aglReleaseShaderCompiler();
void Q_GUI_EXPORT aglRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
void Q_GUI_EXPORT aglSampleCoverage(GLfloat value, GLboolean invert);
void Q_GUI_EXPORT aglScissor(GLint x, GLint y, GLsizei width, GLsizei height);
void Q_GUI_EXPORT aglShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length);
void Q_GUI_EXPORT aglShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length);
void Q_GUI_EXPORT aglStencilFunc(GLenum func, GLint ref, GLuint mask);
void Q_GUI_EXPORT aglStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
void Q_GUI_EXPORT aglStencilMask(GLuint mask);
void Q_GUI_EXPORT aglStencilMaskSeparate(GLenum face, GLuint mask);
void Q_GUI_EXPORT aglStencilOp(GLenum fail, GLenum zfail, GLenum zpass);
void Q_GUI_EXPORT aglStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass);
void Q_GUI_EXPORT aglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels);
void Q_GUI_EXPORT aglTexParameterf(GLenum target, GLenum pname, GLfloat param);
void Q_GUI_EXPORT aglTexParameterfv(GLenum target, GLenum pname, const GLfloat * params);
void Q_GUI_EXPORT aglTexParameteri(GLenum target, GLenum pname, GLint param);
void Q_GUI_EXPORT aglTexParameteriv(GLenum target, GLenum pname, const GLint * params);
void Q_GUI_EXPORT aglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels);
void Q_GUI_EXPORT aglUniform1f(GLint location, GLfloat v0);
void Q_GUI_EXPORT aglUniform1fv(GLint location, GLsizei count, const GLfloat * value);
void Q_GUI_EXPORT aglUniform1i(GLint location, GLint v0);
void Q_GUI_EXPORT aglUniform1iv(GLint location, GLsizei count, const GLint * value);
void Q_GUI_EXPORT aglUniform2f(GLint location, GLfloat v0, GLfloat v1);
void Q_GUI_EXPORT aglUniform2fv(GLint location, GLsizei count, const GLfloat * value);
void Q_GUI_EXPORT aglUniform2i(GLint location, GLint v0, GLint v1);
void Q_GUI_EXPORT aglUniform2iv(GLint location, GLsizei count, const GLint * value);
void Q_GUI_EXPORT aglUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2);
void Q_GUI_EXPORT aglUniform3fv(GLint location, GLsizei count, const GLfloat * value);
void Q_GUI_EXPORT aglUniform3i(GLint location, GLint v0, GLint v1, GLint v2);
void Q_GUI_EXPORT aglUniform3iv(GLint location, GLsizei count, const GLint * value);
void Q_GUI_EXPORT aglUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3);
void Q_GUI_EXPORT aglUniform4fv(GLint location, GLsizei count, const GLfloat * value);
void Q_GUI_EXPORT aglUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3);
void Q_GUI_EXPORT aglUniform4iv(GLint location, GLsizei count, const GLint * value);
void Q_GUI_EXPORT aglUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void Q_GUI_EXPORT aglUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void Q_GUI_EXPORT aglUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value);
void Q_GUI_EXPORT aglUseProgram(GLuint program);
void Q_GUI_EXPORT aglValidateProgram(GLuint program);
void Q_GUI_EXPORT aglVertexAttrib1f(GLuint index, GLfloat x);
void Q_GUI_EXPORT aglVertexAttrib1fv(GLuint index, const GLfloat * v);
void Q_GUI_EXPORT aglVertexAttrib2f(GLuint index, GLfloat x, GLfloat y);
void Q_GUI_EXPORT aglVertexAttrib2fv(GLuint index, const GLfloat * v);
void Q_GUI_EXPORT aglVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z);
void Q_GUI_EXPORT aglVertexAttrib3fv(GLuint index, const GLfloat * v);
void Q_GUI_EXPORT aglVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
void Q_GUI_EXPORT aglVertexAttrib4fv(GLuint index, const GLfloat * v);
void Q_GUI_EXPORT aglVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer);
void Q_GUI_EXPORT aglViewport(GLint x, GLint y, GLsizei width, GLsizei height);

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
#endif
