#ifndef QAMIGAOPENGLCONTEXT_p_h
#define QAMIGAOPENGLCONTEXT_p_h

#include <QtCore/qhash.h>
#include <qpa/qplatformopenglcontext.h>
#include <qpa/qplatformsurface.h>
#include "qoffscreenwindow_p.h"

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
public:
    QAmigaOpenGLContext(QOpenGLContext *context) : QPlatformOpenGLContext()
    {
        Q_UNUSED(context);

        if(!OGLES2Library) OGLES2Library = IExec->OpenLibrary("ogles2.library", 0);
        if(!IOGLES2) IOGLES2 = (struct OGLES2IFace *) IExec->GetInterface(OGLES2Library, "main", 1, NULL);

        ULONG errCode;
        aglContext = aglCreateContextTags(&errCode,
            OGLES2_CCT_VSYNC, 0,
            TAG_DONE);
    }
    ~QAmigaOpenGLContext()
    {
        aglDestroyContext(aglContext);
        if(IOGLES2) IExec->DropInterface((struct Interface *)IOGLES2);
        if(OGLES2Library) IExec->CloseLibrary(OGLES2Library);
        IOGLES2 = 0;
        OGLES2Library = 0;
    }
    QSurfaceFormat format() const override
    {
        QSurfaceFormat format;
        format.setRedBufferSize(8);
        format.setGreenBufferSize(8);
        format.setBlueBufferSize(8);
        format.setAlphaBufferSize(8);
        return format;
    }
    void swapBuffers(QPlatformSurface *surface) override
    {
        Q_UNUSED(surface);
        if(surface->surface()->surfaceClass() == QSurface::Window) {
            IGraphics->BltBitMapRastPort(
            bitmap,
            0, 0,
            dynamic_cast<QOffscreenWindow *>(surface)->m_intuitionWindow->RPort,
            0, 0,
            surface->surface()->size().width(), surface->surface()->size().height(),
            0xc0);
        }
        aglSwapBuffers();
    }
    bool makeCurrent(QPlatformSurface *surface) override
    {
        struct Screen *workbench = IIntuition->LockPubScreen(0);
        bitmap = IGraphics->AllocBitMapTags(surface->surface()->size().width(),surface->surface()->size().height(),0,
                                BMATags_Friend, workbench->FirstWindow->RPort->BitMap,
                                BMATags_Displayable, TRUE,
                                TAG_DONE);
        IIntuition->UnlockPubScreen(0, workbench);
        aglMakeCurrent(aglContext);
        aglSetBitmap(bitmap);
        return true;
    }
    void doneCurrent() override
    {
        IGraphics->FreeBitMap(bitmap);
    }
    QFunctionPointer getProcAddress(const char *procName) override;
private:
    void *aglContext;
    struct BitMap *bitmap;
};
#endif
