/****************************************************************************
**
** Copyright (C) 2013 Klaralvdalens Datakonsult AB (KDAB)
** Contact: https://www.qt.io/licensing/
**
** This file is part of the QtOpenGL module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 3 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL3 included in the
** packaging of this file. Please review the following information to
** ensure the GNU Lesser General Public License version 3 requirements
** will be met: https://www.gnu.org/licenses/lgpl-3.0.html.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 2.0 or (at your option) the GNU General
** Public license version 3 or any later version approved by the KDE Free
** Qt Foundation. The licenses are as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL2 and LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-2.0.html and
** https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QOPENGLVERSIONFUNCTIONS_ES2_H
#define QOPENGLVERSIONFUNCTIONS_ES2_H

#include <QtOpenGL/qtopenglglobal.h>

#if QT_CONFIG(opengles2) || defined(Q_QDOC)

#include <QtOpenGL/QOpenGLVersionProfile>
#include <QtOpenGL/QOpenGLVersionFunctions>
#include <QtGui/qopenglcontext.h>

#ifdef __amigaos4__
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
#endif

QT_BEGIN_NAMESPACE

class QOpenGLFunctions_ES2Private;

class Q_OPENGL_EXPORT QOpenGLFunctions_ES2 : public QAbstractOpenGLFunctions
{
public:
    QOpenGLFunctions_ES2();
    ~QOpenGLFunctions_ES2();

    bool initializeOpenGLFunctions() override;

    // OpenGL ES2 core functions
    void glActiveTexture(GLenum texture);
    void glAttachShader(GLuint program, GLuint shader);
    void glBindAttribLocation(GLuint program, GLuint index, const GLchar* name);
    void glBindBuffer(GLenum target, GLuint buffer);
    void glBindFramebuffer(GLenum target, GLuint framebuffer);
    void glBindRenderbuffer(GLenum target, GLuint renderbuffer);
    void glBindTexture(GLenum target, GLuint texture);
    void glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    void glBlendEquation(GLenum mode);
    void glBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha);
    void glBlendFunc(GLenum sfactor, GLenum dfactor);
    void glBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
    void glBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage);
    void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data);
    GLenum glCheckFramebufferStatus(GLenum target);
    void glClear(GLbitfield mask);
    void glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha);
    void glClearDepthf(GLclampf depth);
    void glClearStencil(GLint s);
    void glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha);
    void glCompileShader(GLuint shader);
    void glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data);
    void glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data);
    void glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border);
    void glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height);
    GLuint glCreateProgram(void);
    GLuint glCreateShader(GLenum type);
    void glCullFace(GLenum mode);
    void glDeleteBuffers(GLsizei n, const GLuint* buffers);
    void glDeleteFramebuffers(GLsizei n, const GLuint* framebuffers);
    void glDeleteProgram(GLuint program);
    void glDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers);
    void glDeleteShader(GLuint shader);
    void glDeleteTextures(GLsizei n, const GLuint* textures);
    void glDepthFunc(GLenum func);
    void glDepthMask(GLboolean flag);
    void glDepthRangef(GLclampf zNear, GLclampf zFar);
    void glDetachShader(GLuint program, GLuint shader);
    void glDisable(GLenum cap);
    void glDisableVertexAttribArray(GLuint index);
    void glDrawArrays(GLenum mode, GLint first, GLsizei count);
    void glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices);
    void glEnable(GLenum cap);
    void glEnableVertexAttribArray(GLuint index);
    void glFinish(void);
    void glFlush(void);
    void glFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer);
    void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level);
    void glFrontFace(GLenum mode);
    void glGenBuffers(GLsizei n, GLuint* buffers);
    void glGenerateMipmap(GLenum target);
    void glGenFramebuffers(GLsizei n, GLuint* framebuffers);
    void glGenRenderbuffers(GLsizei n, GLuint* renderbuffers);
    void glGenTextures(GLsizei n, GLuint* textures);
    void glGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    void glGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name);
    void glGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders);
    int glGetAttribLocation(GLuint program, const GLchar* name);
    void glGetBooleanv(GLenum pname, GLboolean* params);
    void glGetBufferParameteriv(GLenum target, GLenum pname, GLint* params);
    GLenum glGetError(void);
    void glGetFloatv(GLenum pname, GLfloat* params);
    void glGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params);
    void glGetIntegerv(GLenum pname, GLint* params);
    void glGetProgramiv(GLuint program, GLenum pname, GLint* params);
    void glGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    void glGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params);
    void glGetShaderiv(GLuint shader, GLenum pname, GLint* params);
    void glGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog);
    void glGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision);
    void glGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source);
    const GLubyte* glGetString(GLenum name);
    void glGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params);
    void glGetTexParameteriv(GLenum target, GLenum pname, GLint* params);
    void glGetUniformfv(GLuint program, GLint location, GLfloat* params);
    void glGetUniformiv(GLuint program, GLint location, GLint* params);
    int glGetUniformLocation(GLuint program, const GLchar* name);
    void glGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params);
    void glGetVertexAttribiv(GLuint index, GLenum pname, GLint* params);
    void glGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer);
    void glHint(GLenum target, GLenum mode);
    GLboolean glIsBuffer(GLuint buffer);
    GLboolean glIsEnabled(GLenum cap);
    GLboolean glIsFramebuffer(GLuint framebuffer);
    GLboolean glIsProgram(GLuint program);
    GLboolean glIsRenderbuffer(GLuint renderbuffer);
    GLboolean glIsShader(GLuint shader);
    GLboolean glIsTexture(GLuint texture);
    void glLineWidth(GLfloat width);
    void glLinkProgram(GLuint program);
    void glPixelStorei(GLenum pname, GLint param);
    void glPolygonOffset(GLfloat factor, GLfloat units);
    void glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels);
    void glReleaseShaderCompiler(void);
    void glRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height);
    void glSampleCoverage(GLclampf value, GLboolean invert);
    void glScissor(GLint x, GLint y, GLsizei width, GLsizei height);
    void glShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length);
    void glShaderSource(GLuint shader, GLsizei count, const GLchar* *string, const GLint* length);
    void glStencilFunc(GLenum func, GLint ref, GLuint mask);
    void glStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask);
    void glStencilMask(GLuint mask);
    void glStencilMaskSeparate(GLenum face, GLuint mask);
    void glStencilOp(GLenum fail, GLenum zfail, GLenum zpass);
    void glStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass);
    void glTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels);
    void glTexParameterf(GLenum target, GLenum pname, GLfloat param);
    void glTexParameterfv(GLenum target, GLenum pname, const GLfloat* params);
    void glTexParameteri(GLenum target, GLenum pname, GLint param);
    void glTexParameteriv(GLenum target, GLenum pname, const GLint* params);
    void glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels);
    void glUniform1f(GLint location, GLfloat x);
    void glUniform1fv(GLint location, GLsizei count, const GLfloat* v);
    void glUniform1i(GLint location, GLint x);
    void glUniform1iv(GLint location, GLsizei count, const GLint* v);
    void glUniform2f(GLint location, GLfloat x, GLfloat y);
    void glUniform2fv(GLint location, GLsizei count, const GLfloat* v);
    void glUniform2i(GLint location, GLint x, GLint y);
    void glUniform2iv(GLint location, GLsizei count, const GLint* v);
    void glUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z);
    void glUniform3fv(GLint location, GLsizei count, const GLfloat* v);
    void glUniform3i(GLint location, GLint x, GLint y, GLint z);
    void glUniform3iv(GLint location, GLsizei count, const GLint* v);
    void glUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void glUniform4fv(GLint location, GLsizei count, const GLfloat* v);
    void glUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w);
    void glUniform4iv(GLint location, GLsizei count, const GLint* v);
    void glUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void glUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void glUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value);
    void glUseProgram(GLuint program);
    void glValidateProgram(GLuint program);
    void glVertexAttrib1f(GLuint indx, GLfloat x);
    void glVertexAttrib1fv(GLuint indx, const GLfloat* values);
    void glVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y);
    void glVertexAttrib2fv(GLuint indx, const GLfloat* values);
    void glVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z);
    void glVertexAttrib3fv(GLuint indx, const GLfloat* values);
    void glVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    void glVertexAttrib4fv(GLuint indx, const GLfloat* values);
    void glVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr);
    void glViewport(GLint x, GLint y, GLsizei width, GLsizei height);

private:
    friend class QOpenGLContext;

    static bool isContextCompatible(QOpenGLContext *context);
    static QOpenGLVersionProfile versionProfile();

    // For future expansion - not used
    QOpenGLFunctions_ES2Private* d_es2;
};

// OpenGL ES2 core functions
inline void QOpenGLFunctions_ES2aglActiveTexture(GLenum texture)
{
    aglActiveTexture(texture);
}

inline void QOpenGLFunctions_ES2aglAttachShader(GLuint program, GLuint shader)
{
    aglAttachShader(program, shader);
}

inline void QOpenGLFunctions_ES2aglBindAttribLocation(GLuint program, GLuint index, const GLchar* name)
{
    aglBindAttribLocation(program, index, name);
}

inline void QOpenGLFunctions_ES2aglBindBuffer(GLenum target, GLuint buffer)
{
    aglBindBuffer(target, buffer);
}

inline void QOpenGLFunctions_ES2aglBindFramebuffer(GLenum target, GLuint framebuffer)
{
    aglBindFramebuffer(target, framebuffer);
}

inline void QOpenGLFunctions_ES2aglBindRenderbuffer(GLenum target, GLuint renderbuffer)
{
    aglBindRenderbuffer(target, renderbuffer);
}

inline void QOpenGLFunctions_ES2aglBindTexture(GLenum target, GLuint texture)
{
    aglBindTexture(target, texture);
}

inline void QOpenGLFunctions_ES2aglBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    aglBlendColor(red, green, blue, alpha);
}

inline void QOpenGLFunctions_ES2aglBlendEquation(GLenum mode)
{
    aglBlendEquation(mode);
}

inline void QOpenGLFunctions_ES2aglBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha)
{
    aglBlendEquationSeparate(modeRGB, modeAlpha);
}

inline void QOpenGLFunctions_ES2aglBlendFunc(GLenum sfactor, GLenum dfactor)
{
    aglBlendFunc(sfactor, dfactor);
}

inline void QOpenGLFunctions_ES2aglBlendFuncSeparate(GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha)
{
    aglBlendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
}

inline void QOpenGLFunctions_ES2aglBufferData(GLenum target, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
    aglBufferData(target, size, data, usage);
}

inline void QOpenGLFunctions_ES2aglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const GLvoid* data)
{
    aglBufferSubData(target, offset, size, data);
}

inline GLenum QOpenGLFunctions_ES2aglCheckFramebufferStatus(GLenum target)
{
    return aglCheckFramebufferStatus(target);
}

inline void QOpenGLFunctions_ES2aglClear(GLbitfield mask)
{
    aglClear(mask);
}

inline void QOpenGLFunctions_ES2aglClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    aglClearColor(red, green, blue, alpha);
}

inline void QOpenGLFunctions_ES2aglClearDepthf(GLclampf depth)
{
    aglClearDepthf(depth);
}

inline void QOpenGLFunctions_ES2aglClearStencil(GLint s)
{
    aglClearStencil(s);
}

inline void QOpenGLFunctions_ES2aglColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    aglColorMask(red, green, blue, alpha);
}

inline void QOpenGLFunctions_ES2aglCompileShader(GLuint shader)
{
    aglCompileShader(shader);
}

inline void QOpenGLFunctions_ES2aglCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid* data)
{
    aglCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

inline void QOpenGLFunctions_ES2aglCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid* data)
{
    aglCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

inline void QOpenGLFunctions_ES2aglCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    aglCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

inline void QOpenGLFunctions_ES2aglCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    aglCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

inline GLuint QOpenGLFunctions_ES2aglCreateProgram(void)
{
    return aglCreateProgram();
}

inline GLuint QOpenGLFunctions_ES2aglCreateShader(GLenum type)
{
    return aglCreateShader(type);
}

inline void QOpenGLFunctions_ES2aglCullFace(GLenum mode)
{
    aglCullFace(mode);
}

inline void QOpenGLFunctions_ES2aglDeleteBuffers(GLsizei n, const GLuint* buffers)
{
    aglDeleteBuffers(n, buffers);
}

inline void QOpenGLFunctions_ES2aglDeleteFramebuffers(GLsizei n, const GLuint* framebuffers)
{
    aglDeleteFramebuffers(n, framebuffers);
}

inline void QOpenGLFunctions_ES2aglDeleteProgram(GLuint program)
{
    aglDeleteProgram(program);
}

inline void QOpenGLFunctions_ES2aglDeleteRenderbuffers(GLsizei n, const GLuint* renderbuffers)
{
    aglDeleteRenderbuffers(n, renderbuffers);
}

inline void QOpenGLFunctions_ES2aglDeleteShader(GLuint shader)
{
    aglDeleteShader(shader);
}

inline void QOpenGLFunctions_ES2aglDeleteTextures(GLsizei n, const GLuint* textures)
{
    aglDeleteTextures(n, textures);
}

inline void QOpenGLFunctions_ES2aglDepthFunc(GLenum func)
{
    aglDepthFunc(func);
}

inline void QOpenGLFunctions_ES2aglDepthMask(GLboolean flag)
{
    aglDepthMask(flag);
}

inline void QOpenGLFunctions_ES2aglDepthRangef(GLclampf zNear, GLclampf zFar)
{
    aglDepthRangef(zNear, zFar);
}

inline void QOpenGLFunctions_ES2aglDetachShader(GLuint program, GLuint shader)
{
    aglDetachShader(program, shader);
}

inline void QOpenGLFunctions_ES2aglDisable(GLenum cap)
{
    aglDisable(cap);
}

inline void QOpenGLFunctions_ES2aglDisableVertexAttribArray(GLuint index)
{
    aglDisableVertexAttribArray(index);
}

inline void QOpenGLFunctions_ES2aglDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    aglDrawArrays(mode, first, count);
}

inline void QOpenGLFunctions_ES2aglDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid* indices)
{
    aglDrawElements(mode, count, type, indices);
}

inline void QOpenGLFunctions_ES2aglEnable(GLenum cap)
{
    aglEnable(cap);
}

inline void QOpenGLFunctions_ES2aglEnableVertexAttribArray(GLuint index)
{
    aglEnableVertexAttribArray(index);
}

inline void QOpenGLFunctions_ES2aglFinish(void)
{
    aglFinish();
}

inline void QOpenGLFunctions_ES2aglFlush(void)
{
    aglFlush();
}

inline void QOpenGLFunctions_ES2aglFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer)
{
    aglFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

inline void QOpenGLFunctions_ES2aglFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level)
{
    aglFramebufferTexture2D(target, attachment, textarget, texture, level);
}

inline void QOpenGLFunctions_ES2aglFrontFace(GLenum mode)
{
    aglFrontFace(mode);
}

inline void QOpenGLFunctions_ES2aglGenBuffers(GLsizei n, GLuint* buffers)
{
    aglGenBuffers(n, buffers);
}

inline void QOpenGLFunctions_ES2aglGenerateMipmap(GLenum target)
{
    aglGenerateMipmap(target);
}

inline void QOpenGLFunctions_ES2aglGenFramebuffers(GLsizei n, GLuint* framebuffers)
{
    aglGenFramebuffers(n, framebuffers);
}

inline void QOpenGLFunctions_ES2aglGenRenderbuffers(GLsizei n, GLuint* renderbuffers)
{
    aglGenRenderbuffers(n, renderbuffers);
}

inline void QOpenGLFunctions_ES2aglGenTextures(GLsizei n, GLuint* textures)
{
    aglGenTextures(n, textures);
}

inline void QOpenGLFunctions_ES2aglGetActiveAttrib(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
    aglGetActiveAttrib(program, index, bufsize, length, size, type, name);
}

inline void QOpenGLFunctions_ES2aglGetActiveUniform(GLuint program, GLuint index, GLsizei bufsize, GLsizei* length, GLint* size, GLenum* type, GLchar* name)
{
    aglGetActiveUniform(program, index, bufsize, length, size, type, name);
}

inline void QOpenGLFunctions_ES2aglGetAttachedShaders(GLuint program, GLsizei maxcount, GLsizei* count, GLuint* shaders)
{
    aglGetAttachedShaders(program, maxcount, count, shaders);
}

inline int QOpenGLFunctions_ES2aglGetAttribLocation(GLuint program, const GLchar* name)
{
    return aglGetAttribLocation(program, name);
}

inline void QOpenGLFunctions_ES2aglGetBooleanv(GLenum pname, GLboolean* params)
{
    aglGetBooleanv(pname, params);
}

inline void QOpenGLFunctions_ES2aglGetBufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
    aglGetBufferParameteriv(target, pname, params);
}

inline GLenum QOpenGLFunctions_ES2aglGetError(void)
{
    return aglGetError();
}

inline void QOpenGLFunctions_ES2aglGetFloatv(GLenum pname, GLfloat* params)
{
    aglGetFloatv(pname, params);
}

inline void QOpenGLFunctions_ES2aglGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint* params)
{
    aglGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetIntegerv(GLenum pname, GLint* params)
{
    aglGetIntegerv(pname, params);
}

inline void QOpenGLFunctions_ES2aglGetProgramiv(GLuint program, GLenum pname, GLint* params)
{
    aglGetProgramiv(program, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetProgramInfoLog(GLuint program, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
    aglGetProgramInfoLog(program, bufsize, length, infolog);
}

inline void QOpenGLFunctions_ES2aglGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint* params)
{
    aglGetRenderbufferParameteriv(target, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetShaderiv(GLuint shader, GLenum pname, GLint* params)
{
    aglGetShaderiv(shader, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetShaderInfoLog(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* infolog)
{
    aglGetShaderInfoLog(shader, bufsize, length, infolog);
}

inline void QOpenGLFunctions_ES2aglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint* range, GLint* precision)
{
    aglGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

inline void QOpenGLFunctions_ES2aglGetShaderSource(GLuint shader, GLsizei bufsize, GLsizei* length, GLchar* source)
{
    aglGetShaderSource(shader, bufsize, length, source);
}

inline const GLubyte* QOpenGLFunctions_ES2aglGetString(GLenum name)
{
    return aglGetString(name);
}

inline void QOpenGLFunctions_ES2aglGetTexParameterfv(GLenum target, GLenum pname, GLfloat* params)
{
    aglGetTexParameterfv(target, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetTexParameteriv(GLenum target, GLenum pname, GLint* params)
{
    aglGetTexParameteriv(target, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetUniformfv(GLuint program, GLint location, GLfloat* params)
{
    aglGetUniformfv(program, location, params);
}

inline void QOpenGLFunctions_ES2aglGetUniformiv(GLuint program, GLint location, GLint* params)
{
    aglGetUniformiv(program, location, params);
}

inline int QOpenGLFunctions_ES2aglGetUniformLocation(GLuint program, const GLchar* name)
{
    return aglGetUniformLocation(program, name);
}

inline void QOpenGLFunctions_ES2aglGetVertexAttribfv(GLuint index, GLenum pname, GLfloat* params)
{
    aglGetVertexAttribfv(index, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetVertexAttribiv(GLuint index, GLenum pname, GLint* params)
{
    aglGetVertexAttribiv(index, pname, params);
}

inline void QOpenGLFunctions_ES2aglGetVertexAttribPointerv(GLuint index, GLenum pname, GLvoid** pointer)
{
    aglGetVertexAttribPointerv(index, pname, pointer);
}

inline void QOpenGLFunctions_ES2aglHint(GLenum target, GLenum mode)
{
    aglHint(target, mode);
}

inline GLboolean QOpenGLFunctions_ES2aglIsBuffer(GLuint buffer)
{
    return aglIsBuffer(buffer);
}

inline GLboolean QOpenGLFunctions_ES2aglIsEnabled(GLenum cap)
{
    return aglIsEnabled(cap);
}

inline GLboolean QOpenGLFunctions_ES2aglIsFramebuffer(GLuint framebuffer)
{
    return aglIsFramebuffer(framebuffer);
}

inline GLboolean QOpenGLFunctions_ES2aglIsProgram(GLuint program)
{
    return aglIsProgram(program);
}

inline GLboolean QOpenGLFunctions_ES2aglIsRenderbuffer(GLuint renderbuffer)
{
    return aglIsRenderbuffer(renderbuffer);
}

inline GLboolean QOpenGLFunctions_ES2aglIsShader(GLuint shader)
{
    return aglIsShader(shader);
}

inline GLboolean QOpenGLFunctions_ES2aglIsTexture(GLuint texture)
{
    return aglIsTexture(texture);
}

inline void QOpenGLFunctions_ES2aglLineWidth(GLfloat width)
{
    aglLineWidth(width);
}

inline void QOpenGLFunctions_ES2aglLinkProgram(GLuint program)
{
    aglLinkProgram(program);
}

inline void QOpenGLFunctions_ES2aglPixelStorei(GLenum pname, GLint param)
{
    aglPixelStorei(pname, param);
}

inline void QOpenGLFunctions_ES2aglPolygonOffset(GLfloat factor, GLfloat units)
{
    aglPolygonOffset(factor, units);
}

inline void QOpenGLFunctions_ES2aglReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid* pixels)
{
    aglReadPixels(x, y, width, height, format, type, pixels);
}

inline void QOpenGLFunctions_ES2aglReleaseShaderCompiler(void)
{
    aglReleaseShaderCompiler();
}

inline void QOpenGLFunctions_ES2aglRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height)
{
    aglRenderbufferStorage(target, internalformat, width, height);
}

inline void QOpenGLFunctions_ES2aglSampleCoverage(GLclampf value, GLboolean invert)
{
    aglSampleCoverage(value, invert);
}

inline void QOpenGLFunctions_ES2aglScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    aglScissor(x, y, width, height);
}

inline void QOpenGLFunctions_ES2aglShaderBinary(GLsizei n, const GLuint* shaders, GLenum binaryformat, const GLvoid* binary, GLsizei length)
{
    aglShaderBinary(n, shaders, binaryformat, binary, length);
}

inline void QOpenGLFunctions_ES2aglShaderSource(GLuint shader, GLsizei count, const GLchar* *string, const GLint* length)
{
    aglShaderSource(shader, count, string, length);
}

inline void QOpenGLFunctions_ES2aglStencilFunc(GLenum func, GLint ref, GLuint mask)
{
    aglStencilFunc(func, ref, mask);
}

inline void QOpenGLFunctions_ES2aglStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask)
{
    aglStencilFuncSeparate(face, func, ref, mask);
}

inline void QOpenGLFunctions_ES2aglStencilMask(GLuint mask)
{
    aglStencilMask(mask);
}

inline void QOpenGLFunctions_ES2aglStencilMaskSeparate(GLenum face, GLuint mask)
{
    aglStencilMaskSeparate(face, mask);
}

inline void QOpenGLFunctions_ES2aglStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
    aglStencilOp(fail, zfail, zpass);
}

inline void QOpenGLFunctions_ES2aglStencilOpSeparate(GLenum face, GLenum fail, GLenum zfail, GLenum zpass)
{
    aglStencilOpSeparate(face, fail, zfail, zpass);
}

inline void QOpenGLFunctions_ES2aglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid* pixels)
{
    aglTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

inline void QOpenGLFunctions_ES2aglTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
    aglTexParameterf(target, pname, param);
}

inline void QOpenGLFunctions_ES2aglTexParameterfv(GLenum target, GLenum pname, const GLfloat* params)
{
    aglTexParameterfv(target, pname, params);
}

inline void QOpenGLFunctions_ES2aglTexParameteri(GLenum target, GLenum pname, GLint param)
{
    aglTexParameteri(target, pname, param);
}

inline void QOpenGLFunctions_ES2aglTexParameteriv(GLenum target, GLenum pname, const GLint* params)
{
    aglTexParameteriv(target, pname, params);
}

inline void QOpenGLFunctions_ES2aglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid* pixels)
{
    aglTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

inline void QOpenGLFunctions_ES2aglUniform1f(GLint location, GLfloat x)
{
    aglUniform1f(location, x);
}

inline void QOpenGLFunctions_ES2aglUniform1fv(GLint location, GLsizei count, const GLfloat* v)
{
    aglUniform1fv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniform1i(GLint location, GLint x)
{
    aglUniform1i(location, x);
}

inline void QOpenGLFunctions_ES2aglUniform1iv(GLint location, GLsizei count, const GLint* v)
{
    aglUniform1iv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniform2f(GLint location, GLfloat x, GLfloat y)
{
    aglUniform2f(location, x, y);
}

inline void QOpenGLFunctions_ES2aglUniform2fv(GLint location, GLsizei count, const GLfloat* v)
{
    aglUniform2fv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniform2i(GLint location, GLint x, GLint y)
{
    aglUniform2i(location, x, y);
}

inline void QOpenGLFunctions_ES2aglUniform2iv(GLint location, GLsizei count, const GLint* v)
{
    aglUniform2iv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniform3f(GLint location, GLfloat x, GLfloat y, GLfloat z)
{
    aglUniform3f(location, x, y, z);
}

inline void QOpenGLFunctions_ES2aglUniform3fv(GLint location, GLsizei count, const GLfloat* v)
{
    aglUniform3fv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniform3i(GLint location, GLint x, GLint y, GLint z)
{
    aglUniform3i(location, x, y, z);
}

inline void QOpenGLFunctions_ES2aglUniform3iv(GLint location, GLsizei count, const GLint* v)
{
    aglUniform3iv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniform4f(GLint location, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    aglUniform4f(location, x, y, z, w);
}

inline void QOpenGLFunctions_ES2aglUniform4fv(GLint location, GLsizei count, const GLfloat* v)
{
    aglUniform4fv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniform4i(GLint location, GLint x, GLint y, GLint z, GLint w)
{
    aglUniform4i(location, x, y, z, w);
}

inline void QOpenGLFunctions_ES2aglUniform4iv(GLint location, GLsizei count, const GLint* v)
{
    aglUniform4iv(location, count, v);
}

inline void QOpenGLFunctions_ES2aglUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    aglUniformMatrix2fv(location, count, transpose, value);
}

inline void QOpenGLFunctions_ES2aglUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    aglUniformMatrix3fv(location, count, transpose, value);
}

inline void QOpenGLFunctions_ES2aglUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    aglUniformMatrix4fv(location, count, transpose, value);
}

inline void QOpenGLFunctions_ES2aglUseProgram(GLuint program)
{
    aglUseProgram(program);
}

inline void QOpenGLFunctions_ES2aglValidateProgram(GLuint program)
{
    aglValidateProgram(program);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib1f(GLuint indx, GLfloat x)
{
    aglVertexAttrib1f(indx, x);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib1fv(GLuint indx, const GLfloat* values)
{
    aglVertexAttrib1fv(indx, values);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib2f(GLuint indx, GLfloat x, GLfloat y)
{
    aglVertexAttrib2f(indx, x, y);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib2fv(GLuint indx, const GLfloat* values)
{
    aglVertexAttrib2fv(indx, values);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib3f(GLuint indx, GLfloat x, GLfloat y, GLfloat z)
{
    aglVertexAttrib3f(indx, x, y, z);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib3fv(GLuint indx, const GLfloat* values)
{
    aglVertexAttrib3fv(indx, values);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib4f(GLuint indx, GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    aglVertexAttrib4f(indx, x, y, z, w);
}

inline void QOpenGLFunctions_ES2aglVertexAttrib4fv(GLuint indx, const GLfloat* values)
{
    aglVertexAttrib4fv(indx, values);
}

inline void QOpenGLFunctions_ES2aglVertexAttribPointer(GLuint indx, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* ptr)
{
    aglVertexAttribPointer(indx, size, type, normalized, stride, ptr);
}

inline void QOpenGLFunctions_ES2aglViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    aglViewport(x, y, width, height);
}

QT_END_NAMESPACE

#endif // QT_CONFIG(opengles2)

#endif
