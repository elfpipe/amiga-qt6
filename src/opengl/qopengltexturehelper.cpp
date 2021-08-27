/****************************************************************************
**
** Copyright (C) 2013 Klaralvdalens Datakonsult AB (KDAB).
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

#include "qopengltexturehelper_p.h"

#include <QOpenGLContext>
#include <private/qopenglextensions_p.h>

#ifdef __amigaos4__
extern struct OGLES2IFace *IOGLES2;

void aglActiveTexture(GLenum texture) {
    IOGLES2->glActiveTexture(texture);
}

void aglAttachShader(GLuint program, GLuint shader) {
    IOGLES2->glAttachShader(program, shader);
}

void aglBindAttribLocation(GLuint program, GLuint index, const GLchar * name) {
    IOGLES2->glBindAttribLocation(program, index, name);
}

void aglBindBuffer(GLenum target, GLuint buffer) {
    IOGLES2->glBindBuffer(target, buffer);
}

void aglBindFramebuffer(GLenum target, GLuint framebuffer) {
    IOGLES2->glBindFramebuffer(target, framebuffer);
}

void aglBindRenderbuffer(GLenum target, GLuint renderbuffer) {
    IOGLES2->glBindRenderbuffer(target, renderbuffer);
}

void aglBindTexture(GLenum target, GLuint texture) {
    IOGLES2->glBindTexture(target, texture);
}

void aglBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    IOGLES2->glBlendColor(red, green, blue, alpha);
}

void aglBlendEquation(GLenum mode) {
    IOGLES2->glBlendEquation(mode);
}

void aglBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
    IOGLES2->glBlendEquationSeparate(modeRGB, modeAlpha);
}

void aglBlendFunc(GLenum sfactor, GLenum dfactor) {
    IOGLES2->glBlendFunc(sfactor, dfactor);
}

void aglBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    IOGLES2->glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void aglBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage) {
    IOGLES2->glBufferData(target, size, data, usage);
}

void aglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data) {
    IOGLES2->glBufferSubData(target, offset, size, data);
}

GLenum aglCheckFramebufferStatus(GLenum target) {
    return IOGLES2->glCheckFramebufferStatus(target);
}

void aglClear(GLbitfield mask) {
    IOGLES2->glClear(mask);
}

void aglClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    IOGLES2->glClearColor(red, green, blue, alpha);
}

void aglClearDepthf(GLfloat d) {
    IOGLES2->glClearDepthf(d);
}

void aglClearStencil(GLint s) {
    IOGLES2->glClearStencil(s);
}

void aglColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    IOGLES2->glColorMask(red, green, blue, alpha);
}

void aglCompileShader(GLuint shader) {
    IOGLES2->glCompileShader(shader);
}

void aglCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data) {
    IOGLES2->glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void aglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data) {
    IOGLES2->glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void aglCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    IOGLES2->glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void aglCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    IOGLES2->glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

GLuint aglCreateProgram() {
    return IOGLES2->glCreateProgram();
}

GLuint aglCreateShader(GLenum type) {
    return IOGLES2->glCreateShader(type);
}

void aglCullFace(GLenum mode) {
    IOGLES2->glCullFace(mode);
}

void aglDeleteBuffers(GLsizei n, const GLuint * buffers) {
    IOGLES2->glDeleteBuffers(n, buffers);
}

void aglDeleteFramebuffers(GLsizei n, const GLuint * framebuffers) {
    IOGLES2->glDeleteFramebuffers(n, framebuffers);
}

void aglDeleteProgram(GLuint program) {
    IOGLES2->glDeleteProgram(program);
}

void aglDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) {
    IOGLES2->glDeleteRenderbuffers(n, renderbuffers);
}

void aglDeleteShader(GLuint shader) {
    IOGLES2->glDeleteShader(shader);
}

void aglDeleteTextures(GLsizei n, const GLuint * textures) {
    IOGLES2->glDeleteTextures(n, textures);
}

void aglDepthFunc(GLenum func) {
    IOGLES2->glDepthFunc(func);
}

void aglDepthMask(GLboolean flag) {
    IOGLES2->glDepthMask(flag);
}

void aglDepthRangef(GLfloat n, GLfloat f) {
    IOGLES2->glDepthRangef(n, f);
}

void aglDetachShader(GLuint program, GLuint shader) {
    IOGLES2->glDetachShader(program, shader);
}

void aglDisable(GLenum cap) {
    IOGLES2->glDisable(cap);
}

void aglDisableVertexAttribArray(GLuint index) {
    IOGLES2->glDisableVertexAttribArray(index);
}

void aglDrawArrays(GLenum mode, GLint first, GLsizei count) {
    IOGLES2->glDrawArrays(mode, first, count);
}

void aglDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices) {
    IOGLES2->glDrawElements(mode, count, type, indices);
}

void aglEnable(GLenum cap) {
    IOGLES2->glEnable(cap);
}

void aglEnableVertexAttribArray(GLuint index) {
    IOGLES2->glEnableVertexAttribArray(index);
}

void aglFinish() {
    IOGLES2->glFinish();
}

void aglFlush() {
    IOGLES2->glFlush();
}

void aglFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    IOGLES2->glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void glFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    IOGLES2->glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void aglFrontFace(GLenum mode) {
    IOGLES2->glFrontFace(mode);
}

void aglGenBuffers(GLsizei n, GLuint * buffers) {
    IOGLES2->glGenBuffers(n, buffers);
}

void aglGenerateMipmap(GLenum target) {
    IOGLES2->glGenerateMipmap(target);
}

void aglGenFramebuffers(GLsizei n, GLuint * framebuffers) {
    IOGLES2->glGenFramebuffers(n, framebuffers);
}

void aglGenRenderbuffers(GLsizei n, GLuint * renderbuffers) {
    IOGLES2->glGenRenderbuffers(n, renderbuffers);
}

void aglGenTextures(GLsizei n, GLuint * textures) {
    IOGLES2->glGenTextures(n, textures);
}

void aglGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    IOGLES2->glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}

void aglGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    IOGLES2->glGetActiveUniform(program, index, bufSize, length, size, type, name);
}

void aglGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders) {
    IOGLES2->glGetAttachedShaders(program, maxCount, count, shaders);
}

GLint aglGetAttribLocation(GLuint program, const GLchar * name) {
    return IOGLES2->glGetAttribLocation(program, name);
}

void aglGetBooleanv(GLenum pname, GLboolean * data) {
    IOGLES2->glGetBooleanv(pname, data);
}

void aglGetBufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    IOGLES2->glGetBufferParameteriv(target, pname, params);
}

GLenum aglGetError() {
    return IOGLES2->glGetError();
}

void aglGetFloatv(GLenum pname, GLfloat * data) {
    IOGLES2->glGetFloatv(pname, data);
}

void aglGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) {
    IOGLES2->glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}
void aglGetIntegerv(GLenum pname, GLint * data) {
    IOGLES2->glGetIntegerv(pname, data);
}

void aglGetProgramiv(GLuint program, GLenum pname, GLint * params) {
    IOGLES2->glGetProgramiv(program, pname, params);
}

void aglGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    IOGLES2->glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void aglGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    IOGLES2->glGetRenderbufferParameteriv (target, pname, params);
}

void aglGetShaderiv(GLuint shader, GLenum pname, GLint * params) {
    IOGLES2->glGetShaderiv(shader, pname, params);
}

void aglGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    IOGLES2->glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

void aglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision) {
    IOGLES2->glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void aglGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source) {
    IOGLES2->glGetShaderSource(shader, bufSize, length, source);
}

const GLubyte *aglGetString(GLenum name) {
    return IOGLES2->glGetString(name);
}

void aglGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) {
    IOGLES2->glGetTexParameterfv(target, pname, params);
}

void aglGetTexParameteriv(GLenum target, GLenum pname, GLint * params) {
    IOGLES2->glGetTexParameteriv(target, pname, params);
}

void aglGetUniformfv(GLuint program, GLint location, GLfloat * params) {
    IOGLES2->glGetUniformfv(program, location, params);
}

void aglGetUniformiv(GLuint program, GLint location, GLint * params) {
    IOGLES2->glGetUniformiv(program, location, params);
}

GLint aglGetUniformLocation(GLuint program, const GLchar * name) {
    return IOGLES2->glGetUniformLocation(program, name);
}

void aglGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params) {
    IOGLES2->glGetVertexAttribfv(index, pname, params);
}

void aglGetVertexAttribiv(GLuint index, GLenum pname, GLint * params) {
    IOGLES2->glGetVertexAttribiv(index, pname, params);
}

void aglGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer) {
    IOGLES2->glGetVertexAttribPointerv(index, pname, pointer);
}

void aglHint(GLenum target, GLenum mode) {
    IOGLES2->glHint(target, mode);
}

GLboolean aglIsBuffer(GLuint buffer) {
    return IOGLES2->glIsBuffer (buffer);
}

GLboolean aglIsEnabled(GLenum cap) {
    return IOGLES2->glIsEnabled(cap);
}

GLboolean aglIsFramebuffer(GLuint framebuffer) {
    return IOGLES2->glIsFramebuffer(framebuffer);
}

GLboolean aglIsProgram(GLuint program) {
    return IOGLES2->glIsProgram(program);
}

GLboolean aglIsRenderbuffer(GLuint renderbuffer) {
    return IOGLES2->glIsRenderbuffer(renderbuffer);
}

GLboolean aglIsShader(GLuint shader) {
    return IOGLES2->glIsShader(shader);
}

GLboolean aglIsTexture(GLuint texture) {
    return IOGLES2->glIsTexture(texture);
}

void aglLineWidth(GLfloat width) {
    IOGLES2->glLineWidth(width);
}

void aglLinkProgram(GLuint program) {
    IOGLES2->glLinkProgram(program);
}

void aglPixelStorei(GLenum pname, GLint param) {
    IOGLES2->glPixelStorei(pname, param);
}

void aglPolygonOffset(GLfloat factor, GLfloat units) {
    IOGLES2->glPolygonOffset(factor, units);
}

void aglReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels) {
    IOGLES2->glReadPixels(x, y, width, height, format, type, pixels);
}

void aglReleaseShaderCompiler() {
    IOGLES2->glReleaseShaderCompiler();
}

void aglRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    IOGLES2->glRenderbufferStorage(target, internalformat, width, height);
}

void aglSampleCoverage(GLfloat value, GLboolean invert) {
    IOGLES2->glSampleCoverage(value, invert);
}

void aglScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    IOGLES2->glScissor(x, y, width, height);
}

void aglShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length) {
    IOGLES2->glShaderBinary(count, shaders, binaryformat, binary, length);
}

void aglShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length) {
    IOGLES2->glShaderSource(shader, count, string, length);
}

void aglStencilFunc(GLenum func, GLint ref, GLuint mask) {
    IOGLES2->glStencilFunc(func, ref, mask);
}

void aglStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    IOGLES2->glStencilFuncSeparate(face, func, ref, mask);
}

void aglStencilMask(GLuint mask) {
    IOGLES2->glStencilMask(mask);
}

void aglStencilMaskSeparate(GLenum face, GLuint mask) {
    IOGLES2->glStencilMaskSeparate(face, mask);
}

void aglStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    IOGLES2->glStencilOp(fail, zfail, zpass);
}

void aglStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    IOGLES2->glStencilOpSeparate(face, sfail, dpfail, dppass);
}

void aglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) {
    IOGLES2->glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void aglTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    IOGLES2->glTexParameterf(target, pname, param);
}

void aglTexParameterfv(GLenum target, GLenum pname, const GLfloat * params) {
    IOGLES2->glTexParameterfv(target, pname, params);
}

void aglTexParameteri(GLenum target, GLenum pname, GLint param) {
    IOGLES2->glTexParameteri(target, pname, param);
}

void aglTexParameteriv(GLenum target, GLenum pname, const GLint * params) {
    IOGLES2->glTexParameteriv(target, pname, params);
}

void aglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    IOGLES2->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void aglUniform1f(GLint location, GLfloat v0) {
    IOGLES2->glUniform1f(location, v0);
}

void aglUniform1fv(GLint location, GLsizei count, const GLfloat * value) {
    IOGLES2->glUniform1fv(location, count, value);
}

void aglUniform1i(GLint location, GLint v0) {
    IOGLES2->glUniform1i(location, v0);
}

void aglUniform1iv(GLint location, GLsizei count, const GLint * value) {
    IOGLES2->glUniform1iv(location, count, value);
}

void aglUniform2f(GLint location, GLfloat v0, GLfloat v1) {
    IOGLES2->glUniform2f(location, v0, v1);
}

void aglUniform2fv(GLint location, GLsizei count, const GLfloat * value) {
    IOGLES2->glUniform2fv(location, count, value);
}

void aglUniform2i(GLint location, GLint v0, GLint v1) {
    IOGLES2->glUniform2i(location, v0, v1);
}

void aglUniform2iv(GLint location, GLsizei count, const GLint * value) {
    IOGLES2->glUniform2iv(location, count, value);
}

void aglUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    IOGLES2->glUniform3f(location, v0, v1, v2);
}

void aglUniform3fv(GLint location, GLsizei count, const GLfloat * value) {
    IOGLES2->glUniform3fv(location, count, value);
}

void aglUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    IOGLES2->glUniform3i(location, v0, v1, v2);
}

void aglUniform3iv(GLint location, GLsizei count, const GLint * value) {
    IOGLES2->glUniform3iv(location, count, value);
}

void aglUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    IOGLES2->glUniform4f(location, v0, v1, v2, v3);
}

void aglUniform4fv(GLint location, GLsizei count, const GLfloat * value) {
    IOGLES2->glUniform4fv(location, count, value);
}

void aglUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    IOGLES2->glUniform4i(location, v0, v1, v2, v3);
}

void aglUniform4iv(GLint location, GLsizei count, const GLint * value) {
    IOGLES2->glUniform4iv(location, count, value);
}

void aglUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    IOGLES2->glUniformMatrix2fv(location, count, transpose, value);
}

void aglUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    IOGLES2->glUniformMatrix3fv(location, count, transpose, value);
}

void aglUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    IOGLES2->glUniformMatrix4fv(location, count, transpose, value);
}

void aglUseProgram(GLuint program) {
    IOGLES2->glUseProgram(program);
}

void aglValidateProgram(GLuint program) {
    IOGLES2->glValidateProgram(program);
}

void aglVertexAttrib1f(GLuint index, GLfloat x) {
    IOGLES2->glVertexAttrib1f(index, x);
}

void aglVertexAttrib1fv(GLuint index, const GLfloat * v) {
    IOGLES2->glVertexAttrib1fv(index, v);
}

void aglVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    IOGLES2->glVertexAttrib2f(index, x, y);
}

void aglVertexAttrib2fv(GLuint index, const GLfloat * v) {
    IOGLES2->glVertexAttrib2fv(index, v);
}

void aglVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    IOGLES2->glVertexAttrib3f(index, x, y, z);
}

void aglVertexAttrib3fv(GLuint index, const GLfloat * v) {
    IOGLES2->glVertexAttrib3fv(index, v);
}

void aglVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    IOGLES2->glVertexAttrib4f(index, x, y, z, w);
}

void aglVertexAttrib4fv(GLuint index, const GLfloat * v) {
    IOGLES2->glVertexAttrib4fv(index, v);
}

void aglVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) {
    IOGLES2->glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void aglViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    IOGLES2->glViewport(x, y, width, height);
}
#endif

QT_BEGIN_NAMESPACE

QOpenGLTextureHelper::QOpenGLTextureHelper(QOpenGLContext *context)
{
    functions = context->functions();
    // Resolve EXT_direct_state_access entry points if present.

    // However, disable it on some systems where DSA is known to be unreliable.
    bool allowDSA = true;
    const char *renderer = reinterpret_cast<const char *>(context->functions()->glGetString(GL_RENDERER));
    // QTBUG-40653, QTBUG-44988
    if (renderer && strstr(renderer, "AMD Radeon HD"))
        allowDSA = false;

    if (allowDSA && !context->isOpenGLES()
        && context->hasExtension(QByteArrayLiteral("GL_EXT_direct_state_access"))) {
        TextureParameteriEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLenum , GLint )>(context->getProcAddress("glTextureParameteriEXT"));
        TextureParameterivEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLenum , const GLint *)>(context->getProcAddress("glTextureParameterivEXT"));
        TextureParameterfEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLenum , GLfloat )>(context->getProcAddress("glTextureParameterfEXT"));
        TextureParameterfvEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLenum , const GLfloat *)>(context->getProcAddress("glTextureParameterfvEXT"));
        GenerateTextureMipmapEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum )>(context->getProcAddress("glGenerateTextureMipmapEXT"));
        TextureStorage3DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLsizei , GLenum , GLsizei , GLsizei , GLsizei )>(context->getProcAddress("glTextureStorage3DEXT"));
        TextureStorage2DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLsizei , GLenum , GLsizei , GLsizei )>(context->getProcAddress("glTextureStorage2DEXT"));
        TextureStorage1DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLsizei , GLenum , GLsizei )>(context->getProcAddress("glTextureStorage1DEXT"));
        TextureStorage3DMultisampleEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLsizei , GLenum , GLsizei , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTextureStorage3DMultisampleEXT"));
        TextureStorage2DMultisampleEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLsizei , GLenum , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTextureStorage2DMultisampleEXT"));
        TextureImage3DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLenum , GLsizei , GLsizei , GLsizei , GLint , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTextureImage3DEXT"));
        TextureImage2DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLenum , GLsizei , GLsizei , GLint , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTextureImage2DEXT"));
        TextureImage1DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLenum , GLsizei , GLint , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTextureImage1DEXT"));
        TextureSubImage3DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLint , GLint , GLint , GLsizei , GLsizei , GLsizei , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTextureSubImage3DEXT"));
        TextureSubImage2DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLint , GLint , GLsizei , GLsizei , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTextureSubImage2DEXT"));
        TextureSubImage1DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLint , GLsizei , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTextureSubImage1DEXT"));
        CompressedTextureSubImage1DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLint , GLsizei , GLenum , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTextureSubImage1DEXT"));
        CompressedTextureSubImage2DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLint , GLint , GLsizei , GLsizei , GLenum , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTextureSubImage2DEXT"));
        CompressedTextureSubImage3DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLint , GLint , GLint , GLsizei , GLsizei , GLsizei , GLenum , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTextureSubImage3DEXT"));
        CompressedTextureImage1DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLenum , GLsizei , GLint , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTextureImage1DEXT"));
        CompressedTextureImage2DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLenum , GLsizei , GLsizei , GLint , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTextureImage2DEXT"));
        CompressedTextureImage3DEXT = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLint , GLenum , GLsizei , GLsizei , GLsizei , GLint , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTextureImage3DEXT"));

        // Use the real DSA functions
        TextureParameteri = &QOpenGLTextureHelper::dsa_TextureParameteri;
        TextureParameteriv = &QOpenGLTextureHelper::dsa_TextureParameteriv;
        TextureParameterf = &QOpenGLTextureHelper::dsa_TextureParameterf;
        TextureParameterfv = &QOpenGLTextureHelper::dsa_TextureParameterfv;
        GenerateTextureMipmap = &QOpenGLTextureHelper::dsa_GenerateTextureMipmap;
        TextureStorage3D = &QOpenGLTextureHelper::dsa_TextureStorage3D;
        TextureStorage2D = &QOpenGLTextureHelper::dsa_TextureStorage2D;
        TextureStorage1D = &QOpenGLTextureHelper::dsa_TextureStorage1D;
        TextureStorage3DMultisample = &QOpenGLTextureHelper::dsa_TextureStorage3DMultisample;
        TextureStorage2DMultisample = &QOpenGLTextureHelper::dsa_TextureStorage2DMultisample;
        TextureImage3D = &QOpenGLTextureHelper::dsa_TextureImage3D;
        TextureImage2D = &QOpenGLTextureHelper::dsa_TextureImage2D;
        TextureImage1D = &QOpenGLTextureHelper::dsa_TextureImage1D;
        TextureSubImage3D = &QOpenGLTextureHelper::dsa_TextureSubImage3D;
        TextureSubImage2D = &QOpenGLTextureHelper::dsa_TextureSubImage2D;
        TextureSubImage1D = &QOpenGLTextureHelper::dsa_TextureSubImage1D;
        CompressedTextureSubImage1D = &QOpenGLTextureHelper::dsa_CompressedTextureSubImage1D;
        CompressedTextureSubImage2D = &QOpenGLTextureHelper::dsa_CompressedTextureSubImage2D;
        CompressedTextureSubImage3D = &QOpenGLTextureHelper::dsa_CompressedTextureSubImage3D;
        CompressedTextureImage1D = &QOpenGLTextureHelper::dsa_CompressedTextureImage1D;
        CompressedTextureImage2D = &QOpenGLTextureHelper::dsa_CompressedTextureImage2D;
        CompressedTextureImage3D = &QOpenGLTextureHelper::dsa_CompressedTextureImage3D;
    } else {
        // Use our own DSA emulation
        TextureParameteri = &QOpenGLTextureHelper::qt_TextureParameteri;
        TextureParameteriv = &QOpenGLTextureHelper::qt_TextureParameteriv;
        TextureParameterf = &QOpenGLTextureHelper::qt_TextureParameterf;
        TextureParameterfv = &QOpenGLTextureHelper::qt_TextureParameterfv;
        GenerateTextureMipmap = &QOpenGLTextureHelper::qt_GenerateTextureMipmap;
        TextureStorage3D = &QOpenGLTextureHelper::qt_TextureStorage3D;
        TextureStorage2D = &QOpenGLTextureHelper::qt_TextureStorage2D;
        TextureStorage1D = &QOpenGLTextureHelper::qt_TextureStorage1D;
        TextureStorage3DMultisample = &QOpenGLTextureHelper::qt_TextureStorage3DMultisample;
        TextureStorage2DMultisample = &QOpenGLTextureHelper::qt_TextureStorage2DMultisample;
        TextureImage3D = &QOpenGLTextureHelper::qt_TextureImage3D;
        TextureImage2D = &QOpenGLTextureHelper::qt_TextureImage2D;
        TextureImage1D = &QOpenGLTextureHelper::qt_TextureImage1D;
        TextureSubImage3D = &QOpenGLTextureHelper::qt_TextureSubImage3D;
        TextureSubImage2D = &QOpenGLTextureHelper::qt_TextureSubImage2D;
        TextureSubImage1D = &QOpenGLTextureHelper::qt_TextureSubImage1D;
        CompressedTextureSubImage1D = &QOpenGLTextureHelper::qt_CompressedTextureSubImage1D;
        CompressedTextureSubImage2D = &QOpenGLTextureHelper::qt_CompressedTextureSubImage2D;
        CompressedTextureSubImage3D = &QOpenGLTextureHelper::qt_CompressedTextureSubImage3D;
        CompressedTextureImage1D = &QOpenGLTextureHelper::qt_CompressedTextureImage1D;
        CompressedTextureImage2D = &QOpenGLTextureHelper::qt_CompressedTextureImage2D;
        CompressedTextureImage3D = &QOpenGLTextureHelper::qt_CompressedTextureImage3D;
    }

    // Some DSA functions are part of NV_texture_multisample instead
    if (!context->isOpenGLES()
        && context->hasExtension(QByteArrayLiteral("GL_NV_texture_multisample"))) {
        TextureImage3DMultisampleNV = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLsizei , GLint , GLsizei , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTextureImage3DMultisampleNV"));
        TextureImage2DMultisampleNV = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLsizei , GLint , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTextureImage2DMultisampleNV"));

        TextureImage3DMultisample = &QOpenGLTextureHelper::dsa_TextureImage3DMultisample;
        TextureImage2DMultisample = &QOpenGLTextureHelper::dsa_TextureImage2DMultisample;
    } else {
        TextureImage3DMultisample = &QOpenGLTextureHelper::qt_TextureImage3DMultisample;
        TextureImage2DMultisample = &QOpenGLTextureHelper::qt_TextureImage2DMultisample;
    }

#if QT_CONFIG(opengles2)
    // Here we are targeting OpenGL ES 2.0+ only. This is likely using EGL, where,
    // similarly to WGL, non-extension functions (i.e. any function that is part of the
    // GLES spec) *may* not be queried via eglGetProcAddress.

    // OpenGL 1.0
    TexImage1D = 0;

    // OpenGL 1.1
    TexSubImage1D = 0;

    // OpenGL 1.3
    GetCompressedTexImage = 0;
    CompressedTexSubImage1D = 0;
    CompressedTexSubImage2D = aglCompressedTexSubImage2D;
    CompressedTexImage1D = 0;
    CompressedTexImage2D = aglCompressedTexImage2D;
    ActiveTexture = aglActiveTexture;

    // OpenGL 3.0
    GenerateMipmap = aglGenerateMipmap;

    // OpenGL 3.2
    TexImage3DMultisample = 0;
    TexImage2DMultisample = 0;

    // OpenGL 4.2
    QOpenGLContext *ctx = QOpenGLContext::currentContext();
    if (ctx->format().majorVersion() >= 3) {
        // OpenGL ES 3.0+ has immutable storage for 2D and 3D at least.
        QOpenGLExtraFunctionsPrivate *extra = static_cast<QOpenGLExtensions *>(context->extraFunctions())->d();
        TexStorage3D = extra->f.TexStorage3D;
        TexStorage2D = extra->f.TexStorage2D;
    } else {
        TexStorage3D = 0;
        TexStorage2D = 0;
    }
    TexStorage1D = 0;

    // OpenGL 4.3
    TexStorage3DMultisample = 0;
    TexStorage2DMultisample = 0;
    TexBufferRange = 0;
    TextureView = 0;

    // OpenGL ES 3.1+ has TexStorage2DMultisample
    if (ctx->format().version() >= qMakePair(3, 1)) {
        QOpenGLExtraFunctionsPrivate *extra = static_cast<QOpenGLExtensions *>(context->extraFunctions())->d();
        TexStorage2DMultisample = extra->f.TexStorage2DMultisample;
    }

#endif

    if (context->isOpenGLES() && context->hasExtension(QByteArrayLiteral("GL_OES_texture_3D"))) {
        TexImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum, GLint, GLint, GLsizei, GLsizei, GLsizei, GLint, GLenum, GLenum, const GLvoid*)>(context->getProcAddress("glTexImage3DOES"));
        TexSubImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLenum, const GLvoid*)>(context->getProcAddress("glTexSubImage3DOES"));
        CompressedTexImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum, GLint, GLenum, GLsizei, GLsizei, GLsizei, GLint, GLsizei, const GLvoid*)>(context->getProcAddress("glCompressedTexImage3DOES"));
        CompressedTexSubImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum, GLint, GLint, GLint, GLint, GLsizei, GLsizei, GLsizei, GLenum, GLsizei, const GLvoid*)>(context->getProcAddress("glCompressedTexSubImage3DOES"));
    } else {
        QOpenGLContext *ctx = QOpenGLContext::currentContext();
        if (ctx->isOpenGLES() && ctx->format().majorVersion() >= 3) {
            // OpenGL ES 3.0+ has glTexImage3D.
            QOpenGLExtraFunctionsPrivate *extra = static_cast<QOpenGLExtensions *>(context->extraFunctions())->d();
            TexImage3D = extra->f.TexImage3D;
            TexSubImage3D = extra->f.TexSubImage3D;
            CompressedTexImage3D = extra->f.CompressedTexImage3D;
            CompressedTexSubImage3D = extra->f.CompressedTexSubImage3D;
        } else {
            // OpenGL 1.2
            TexImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLint , GLsizei , GLsizei , GLsizei , GLint , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTexImage3D"));
            TexSubImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLint , GLint , GLint , GLsizei , GLsizei , GLsizei , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTexSubImage3D"));

            // OpenGL 1.3
            CompressedTexImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLenum , GLsizei , GLsizei , GLsizei , GLint , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTexImage3D"));
            CompressedTexSubImage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLint , GLint , GLint , GLsizei , GLsizei , GLsizei , GLenum , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTexSubImage3D"));
        }
    }

#if !QT_CONFIG(opengles2)
    // OpenGL 1.0 and 1.1
    TexImage1D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLint , GLsizei , GLint , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTexImage1D"));
    TexSubImage1D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLint , GLsizei , GLenum , GLenum , const GLvoid *)>(context->getProcAddress("glTexSubImage1D"));\

    // OpenGL 1.3
    GetCompressedTexImage = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLvoid *)>(context->getProcAddress("glGetCompressedTexImage"));
    CompressedTexSubImage1D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLint , GLsizei , GLenum , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTexSubImage1D"));
    CompressedTexSubImage2D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLint , GLint , GLsizei , GLsizei , GLenum , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTexSubImage2D"));
    CompressedTexImage1D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLenum , GLsizei , GLint , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTexImage1D"));
    CompressedTexImage2D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLint , GLenum , GLsizei , GLsizei , GLint , GLsizei , const GLvoid *)>(context->getProcAddress("glCompressedTexImage2D"));
    ActiveTexture = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum )>(context->getProcAddress("glActiveTexture"));

    // OpenGL 3.0
    GenerateMipmap = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum )>(context->getProcAddress("glGenerateMipmap"));

    // OpenGL 3.2
    TexImage3DMultisample = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLsizei , GLint , GLsizei , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTexImage3DMultisample"));
    TexImage2DMultisample = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLsizei , GLint , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTexImage2DMultisample"));

    // OpenGL 4.2
    TexStorage3D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLsizei , GLenum , GLsizei , GLsizei , GLsizei )>(context->getProcAddress("glTexStorage3D"));
    TexStorage2D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLsizei , GLenum , GLsizei , GLsizei )>(context->getProcAddress("glTexStorage2D"));
    TexStorage1D = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLsizei , GLenum , GLsizei )>(context->getProcAddress("glTexStorage1D"));

    // OpenGL 4.3
    TexStorage3DMultisample = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLsizei , GLenum , GLsizei , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTexStorage3DMultisample"));
    TexStorage2DMultisample = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLsizei , GLenum , GLsizei , GLsizei , GLboolean )>(context->getProcAddress("glTexStorage2DMultisample"));
    TexBufferRange = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLenum , GLenum , GLuint , GLintptr , GLsizeiptr )>(context->getProcAddress("glTexBufferRange"));
    TextureView = reinterpret_cast<void (QOPENGLF_APIENTRYP)(GLuint , GLenum , GLuint , GLenum , GLuint , GLuint , GLuint , GLuint )>(context->getProcAddress("glTextureView"));
#endif
}

void QOpenGLTextureHelper::dsa_TextureParameteri(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, GLint param)
{
    Q_UNUSED(bindingTarget);
    TextureParameteriEXT(texture, target, pname, param);
}

void QOpenGLTextureHelper::dsa_TextureParameteriv(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, const GLint *params)
{
    Q_UNUSED(bindingTarget);
    TextureParameterivEXT(texture, target, pname, params);
}

void QOpenGLTextureHelper::dsa_TextureParameterf(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, GLfloat param)
{
    Q_UNUSED(bindingTarget);
    TextureParameterfEXT(texture, target, pname, param);
}

void QOpenGLTextureHelper::dsa_TextureParameterfv(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, const GLfloat *params)
{
    Q_UNUSED(bindingTarget);
    TextureParameterfvEXT(texture, target, pname, params);
}

void QOpenGLTextureHelper::dsa_GenerateTextureMipmap(GLuint texture, GLenum target, GLenum bindingTarget)
{
    Q_UNUSED(bindingTarget);
    GenerateTextureMipmapEXT(texture, target);
}

void QOpenGLTextureHelper::dsa_TextureStorage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth)
{
    Q_UNUSED(bindingTarget);
    TextureStorage3DEXT(texture, target, levels, internalFormat, width, height, depth);
}

void QOpenGLTextureHelper::dsa_TextureStorage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height)
{
    Q_UNUSED(bindingTarget);
    TextureStorage2DEXT(texture, target, levels, internalFormat, width, height);
}

void QOpenGLTextureHelper::dsa_TextureStorage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei levels, GLenum internalFormat, GLsizei width)
{
    Q_UNUSED(bindingTarget);
    TextureStorage1DEXT(texture, target, levels, internalFormat, width);
}

void QOpenGLTextureHelper::dsa_TextureStorage3DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
    Q_UNUSED(bindingTarget);
    TextureStorage3DMultisampleEXT(texture, target, samples, internalFormat, width, height, depth, fixedSampleLocations);
}

void QOpenGLTextureHelper::dsa_TextureStorage2DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
    Q_UNUSED(bindingTarget);
    TextureStorage2DMultisampleEXT(texture, target, samples, internalFormat, width, height, fixedSampleLocations);
}

void QOpenGLTextureHelper::dsa_TextureImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    Q_UNUSED(bindingTarget);
    TextureImage3DEXT(texture, target, level, internalFormat, width, height, depth, border, format, type, pixels);
}

void QOpenGLTextureHelper::dsa_TextureImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    Q_UNUSED(bindingTarget);
    TextureImage2DEXT(texture, target, level, internalFormat, width, height, border, format, type, pixels);
}

void QOpenGLTextureHelper::dsa_TextureImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    Q_UNUSED(bindingTarget);
    TextureImage1DEXT(texture, target, level, internalFormat, width, border, format, type, pixels);
}

void QOpenGLTextureHelper::dsa_TextureSubImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
    Q_UNUSED(bindingTarget);
    TextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void QOpenGLTextureHelper::dsa_TextureSubImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
    Q_UNUSED(bindingTarget);
    TextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void QOpenGLTextureHelper::dsa_TextureSubImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels)
{
    Q_UNUSED(bindingTarget);
    TextureSubImage1DEXT(texture, target, level, xoffset, width, format, type, pixels);
}

void QOpenGLTextureHelper::dsa_TextureImage3DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
    Q_UNUSED(bindingTarget);
    TextureImage3DMultisampleNV(texture, target, samples, internalFormat, width, height, depth, fixedSampleLocations);
}

void QOpenGLTextureHelper::dsa_TextureImage2DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
    Q_UNUSED(bindingTarget);
    TextureImage2DMultisampleNV(texture, target, samples, internalFormat, width, height, fixedSampleLocations);
}

void QOpenGLTextureHelper::dsa_CompressedTextureSubImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *bits)
{
    Q_UNUSED(bindingTarget);
    CompressedTextureSubImage1DEXT(texture, target, level, xoffset, width, format, imageSize, bits);
}

void QOpenGLTextureHelper::dsa_CompressedTextureSubImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *bits)
{
    Q_UNUSED(bindingTarget);
    CompressedTextureSubImage2DEXT(texture, target, level, xoffset, yoffset, width, height, format, imageSize, bits);
}

void QOpenGLTextureHelper::dsa_CompressedTextureSubImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *bits)
{
    Q_UNUSED(bindingTarget);
    CompressedTextureSubImage3DEXT(texture, target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
}

void QOpenGLTextureHelper::dsa_CompressedTextureImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *bits)
{
    Q_UNUSED(bindingTarget);
    CompressedTextureImage1DEXT(texture, target, level, internalFormat, width, border, imageSize, bits);
}

void QOpenGLTextureHelper::dsa_CompressedTextureImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *bits)
{
    Q_UNUSED(bindingTarget);
    CompressedTextureImage2DEXT(texture, target, level, internalFormat, width, height, border, imageSize, bits);
}

void QOpenGLTextureHelper::dsa_CompressedTextureImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *bits)
{
    Q_UNUSED(bindingTarget);
    CompressedTextureImage3DEXT(texture, target, level, internalFormat, width, height, depth, border, imageSize, bits);
}

namespace {

class TextureBinder
{
public:
    TextureBinder(QOpenGLFunctions *functions, GLuint texture, GLenum target, GLenum bindingTarget)
    : m_functions(functions)
    {
        // For cubemaps we can't use the standard DSA emulation as it is illegal to
        // try to bind a texture to one of the cubemap face targets. So we force the
        // target and binding target to the cubemap values in this case.
        switch (target) {
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_X:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_X:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Y:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Y:
        case GL_TEXTURE_CUBE_MAP_NEGATIVE_Z:
        case GL_TEXTURE_CUBE_MAP_POSITIVE_Z:
            bindingTarget = GL_TEXTURE_BINDING_CUBE_MAP;
            m_target = GL_TEXTURE_CUBE_MAP;
            break;

        default:
            m_target = target;
            break;
        }

        m_functions->glGetIntegerv(bindingTarget, &m_oldTexture);
        m_functions->glBindTexture(m_target, texture);
    }

    ~TextureBinder()
    {
        m_functions->glBindTexture(m_target, m_oldTexture);
    }

private:
    QOpenGLFunctions *m_functions;
    GLenum m_target;
    GLint m_oldTexture;
};

} // namespace

void QOpenGLTextureHelper::qt_TextureParameteri(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, GLint param)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    functions->glTexParameteri(target, pname, param);
}

void QOpenGLTextureHelper::qt_TextureParameteriv(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, const GLint *params)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    functions->glTexParameteriv(target, pname, params);
}

void QOpenGLTextureHelper::qt_TextureParameterf(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, GLfloat param)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    functions->glTexParameterf(target, pname, param);
}

void QOpenGLTextureHelper::qt_TextureParameterfv(GLuint texture, GLenum target, GLenum bindingTarget, GLenum pname, const GLfloat *params)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    functions->glTexParameterfv(target, pname, params);
}

void QOpenGLTextureHelper::qt_GenerateTextureMipmap(GLuint texture, GLenum target, GLenum bindingTarget)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    functions->glGenerateMipmap(target);
}

void QOpenGLTextureHelper::qt_TextureStorage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexStorage3D(target, levels, internalFormat, width, height, depth);
}

void QOpenGLTextureHelper::qt_TextureStorage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei levels, GLenum internalFormat, GLsizei width, GLsizei height)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexStorage2D(target, levels, internalFormat, width, height);
}

void QOpenGLTextureHelper::qt_TextureStorage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei levels, GLenum internalFormat, GLsizei width)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexStorage1D(target, levels, internalFormat, width);
}

void QOpenGLTextureHelper::qt_TextureStorage3DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexStorage3DMultisample(target, samples, internalFormat, width, height, depth, fixedSampleLocations);
}

void QOpenGLTextureHelper::qt_TextureStorage2DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLenum internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexStorage2DMultisample(target, samples, internalFormat, width, height, fixedSampleLocations);
}

void QOpenGLTextureHelper::qt_TextureImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexImage3D(target, level, internalFormat, width, height, depth, border, format, type, pixels);
}

void QOpenGLTextureHelper::qt_TextureImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    functions->glTexImage2D(target, level, internalFormat, width, height, border, format, type, pixels);
}

void QOpenGLTextureHelper::qt_TextureImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexImage1D(target, level, internalFormat, width, border, format, type, pixels);
}

void QOpenGLTextureHelper::qt_TextureSubImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, type, pixels);
}

void QOpenGLTextureHelper::qt_TextureSubImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    functions->glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void QOpenGLTextureHelper::qt_TextureSubImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexSubImage1D(target, level, xoffset, width, format, type, pixels);
}

void QOpenGLTextureHelper::qt_TextureImage3DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedSampleLocations)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexImage3DMultisample(target, samples, internalFormat, width, height, depth, fixedSampleLocations);
}

void QOpenGLTextureHelper::qt_TextureImage2DMultisample(GLuint texture, GLenum target, GLenum bindingTarget, GLsizei samples, GLint internalFormat, GLsizei width, GLsizei height, GLboolean fixedSampleLocations)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glTexImage2DMultisample(target, samples, internalFormat, width, height, fixedSampleLocations);
}

void QOpenGLTextureHelper::qt_CompressedTextureSubImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *bits)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glCompressedTexSubImage1D(target, level, xoffset, width, format, imageSize, bits);
}

void QOpenGLTextureHelper::qt_CompressedTextureSubImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *bits)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, bits);
}

void QOpenGLTextureHelper::qt_CompressedTextureSubImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *bits)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glCompressedTexSubImage3D(target, level, xoffset, yoffset, zoffset, width, height, depth, format, imageSize, bits);
}

void QOpenGLTextureHelper::qt_CompressedTextureImage1D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *bits)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glCompressedTexImage1D(target, level, internalFormat, width, border, imageSize, bits);
}

void QOpenGLTextureHelper::qt_CompressedTextureImage2D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *bits)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glCompressedTexImage2D(target, level, internalFormat, width, height, border, imageSize, bits);
}

void QOpenGLTextureHelper::qt_CompressedTextureImage3D(GLuint texture, GLenum target, GLenum bindingTarget, GLint level, GLenum internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *bits)
{
    TextureBinder binder(functions, texture, target, bindingTarget);
    glCompressedTexImage3D(target, level, internalFormat, width, height, depth, border, imageSize, bits);
}

QT_END_NAMESPACE
