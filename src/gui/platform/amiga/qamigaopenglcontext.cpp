#include <proto/ogles2.h>
#include <inline4/ogles2.h>
struct Library *OGLES2Library = 0;
struct OGLES2IFace *IOGLES2 = 0;

void aglActiveTexture(GLenum texture) {
    glActiveTexture(texture);
}

void aglAttachShader(GLuint program, GLuint shader) {
    glAttachShader(program, shader);
}

void aglBindAttribLocation(GLuint program, GLuint index, const GLchar * name) {
    glBindAttribLocation(program, index, name);
}

void aglBindBuffer(GLenum target, GLuint buffer) {
    glBindBuffer(target, buffer);
}

void aglBindFramebuffer(GLenum target, GLuint framebuffer) {
    glBindFramebuffer(target, framebuffer);
}

void aglBindRenderbuffer(GLenum target, GLuint renderbuffer) {
    glBindRenderbuffer(target, renderbuffer);
}

void aglBindTexture(GLenum target, GLuint texture) {
    glBindTexture(target, texture);
}

void aglBlendColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glBlendColor(red, green, blue, alpha);
}

void aglBlendEquation(GLenum mode) {
    glBlendEquation(mode);
}

void aglBlendEquationSeparate(GLenum modeRGB, GLenum modeAlpha) {
    glBlendEquationSeparate(modeRGB, modeAlpha);
}

void aglBlendFunc(GLenum sfactor, GLenum dfactor) {
    glBlendFunc(sfactor, dfactor);
}

void aglBlendFuncSeparate(GLenum sfactorRGB, GLenum dfactorRGB, GLenum sfactorAlpha, GLenum dfactorAlpha) {
    glBlendFuncSeparate(sfactorRGB, dfactorRGB, sfactorAlpha, dfactorAlpha);
}

void aglBufferData(GLenum target, GLsizeiptr size, const void * data, GLenum usage) {
    glBufferData(target, size, data, usage);
}

void aglBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data) {
    glBufferSubData(target, offset, size, data);
}

GLenum aglCheckFramebufferStatus(GLenum target) {
    return glCheckFramebufferStatus(target);
}

void aglClear(GLbitfield mask) {
    glClear(mask);
}

void aglClearColor(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) {
    glClearColor(red, green, blue, alpha);
}

void aglClearDepthf(GLfloat d) {
    glClearDepthf(d);
}

void aglClearStencil(GLint s) {
    glClearStencil(s);
}

void aglColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha) {
    glColorMask(red, green, blue, alpha);
}

void aglCompileShader(GLuint shader) {
    glCompileShader(shader);
}

void aglCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const void * data) {
    glCompressedTexImage2D(target, level, internalformat, width, height, border, imageSize, data);
}

void aglCompressedTexSubImage2D (GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const void * data) {
    glCompressedTexSubImage2D(target, level, xoffset, yoffset, width, height, format, imageSize, data);
}

void aglCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border) {
    glCopyTexImage2D(target, level, internalformat, x, y, width, height, border);
}

void aglCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height) {
    glCopyTexSubImage2D(target, level, xoffset, yoffset, x, y, width, height);
}

GLuint aglCreateProgram() {
    return glCreateProgram();
}

GLuint aglCreateShader(GLenum type) {
    return glCreateShader(type);
}

void aglCullFace(GLenum mode) {
    glCullFace(mode);
}

void aglDeleteBuffers(GLsizei n, const GLuint * buffers) {
    glDeleteBuffers(n, buffers);
}

void aglDeleteFramebuffers(GLsizei n, const GLuint * framebuffers) {
    glDeleteFramebuffers(n, framebuffers);
}

void aglDeleteProgram(GLuint program) {
    glDeleteProgram(program);
}

void aglDeleteRenderbuffers(GLsizei n, const GLuint * renderbuffers) {
    glDeleteRenderbuffers(n, renderbuffers);
}

void aglDeleteShader(GLuint shader) {
    glDeleteShader(shader);
}

void aglDeleteTextures(GLsizei n, const GLuint * textures) {
    glDeleteTextures(n, textures);
}

void aglDepthFunc(GLenum func) {
    glDepthFunc(func);
}

void aglDepthMask(GLboolean flag) {
    glDepthMask(flag);
}

void aglDepthRangef(GLfloat n, GLfloat f) {
    glDepthRangef(n, f);
}

void aglDetachShader(GLuint program, GLuint shader) {
    glDetachShader(program, shader);
}

void aglDisable(GLenum cap) {
    glDisable(cap);
}

void aglDisableVertexAttribArray(GLuint index) {
    glDisableVertexAttribArray(index);
}

void aglDrawArrays(GLenum mode, GLint first, GLsizei count) {
    glDrawArrays(mode, first, count);
}

void aglDrawElements(GLenum mode, GLsizei count, GLenum type, const void * indices) {
    glDrawElements(mode, count, type, indices);
}

void aglEnable(GLenum cap) {
    glEnable(cap);
}

void aglEnableVertexAttribArray(GLuint index) {
    glEnableVertexAttribArray(index);
}

void aglFinish() {
    glFinish();
}

void aglFlush() {
    glFlush();
}

void aglFramebufferRenderbuffer(GLenum target, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer) {
    glFramebufferRenderbuffer(target, attachment, renderbuffertarget, renderbuffer);
}

void aglFramebufferTexture2D(GLenum target, GLenum attachment, GLenum textarget, GLuint texture, GLint level) {
    glFramebufferTexture2D(target, attachment, textarget, texture, level);
}

void aglFrontFace(GLenum mode) {
    glFrontFace(mode);
}

void aglGenBuffers(GLsizei n, GLuint * buffers) {
    glGenBuffers(n, buffers);
}

void aglGenerateMipmap(GLenum target) {
    glGenerateMipmap(target);
}

void aglGenFramebuffers(GLsizei n, GLuint * framebuffers) {
    glGenFramebuffers(n, framebuffers);
}

void aglGenRenderbuffers(GLsizei n, GLuint * renderbuffers) {
    glGenRenderbuffers(n, renderbuffers);
}

void aglGenTextures(GLsizei n, GLuint * textures) {
    glGenTextures(n, textures);
}

void aglGetActiveAttrib(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    glGetActiveAttrib(program, index, bufSize, length, size, type, name);
}

void aglGetActiveUniform(GLuint program, GLuint index, GLsizei bufSize, GLsizei * length, GLint * size, GLenum * type, GLchar * name) {
    glGetActiveUniform(program, index, bufSize, length, size, type, name);
}

void aglGetAttachedShaders(GLuint program, GLsizei maxCount, GLsizei * count, GLuint * shaders) {
    glGetAttachedShaders(program, maxCount, count, shaders);
}

GLint aglGetAttribLocation(GLuint program, const GLchar * name) {
    return glGetAttribLocation(program, name);
}

void aglGetBooleanv(GLenum pname, GLboolean * data) {
    glGetBooleanv(pname, data);
}

void aglGetBufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    glGetBufferParameteriv(target, pname, params);
}

GLenum aglGetError() {
    return glGetError();
}

void aglGetFloatv(GLenum pname, GLfloat * data) {
    glGetFloatv(pname, data);
}

void aglGetFramebufferAttachmentParameteriv(GLenum target, GLenum attachment, GLenum pname, GLint * params) {
    glGetFramebufferAttachmentParameteriv(target, attachment, pname, params);
}
void aglGetIntegerv(GLenum pname, GLint * data) {
    glGetIntegerv(pname, data);
}

void aglGetProgramiv(GLuint program, GLenum pname, GLint * params) {
    glGetProgramiv(program, pname, params);
}

void aglGetProgramInfoLog(GLuint program, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    glGetProgramInfoLog(program, bufSize, length, infoLog);
}

void aglGetRenderbufferParameteriv(GLenum target, GLenum pname, GLint * params) {
    glGetRenderbufferParameteriv (target, pname, params);
}

void aglGetShaderiv(GLuint shader, GLenum pname, GLint * params) {
    glGetShaderiv(shader, pname, params);
}

void aglGetShaderInfoLog(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * infoLog) {
    glGetShaderInfoLog(shader, bufSize, length, infoLog);
}

void aglGetShaderPrecisionFormat(GLenum shadertype, GLenum precisiontype, GLint * range, GLint * precision) {
    glGetShaderPrecisionFormat(shadertype, precisiontype, range, precision);
}

void aglGetShaderSource(GLuint shader, GLsizei bufSize, GLsizei * length, GLchar * source) {
    glGetShaderSource(shader, bufSize, length, source);
}

const GLubyte *aglGetString(GLenum name) {
    return glGetString(name);
}

void aglGetTexParameterfv(GLenum target, GLenum pname, GLfloat * params) {
    glGetTexParameterfv(target, pname, params);
}

void aglGetTexParameteriv(GLenum target, GLenum pname, GLint * params) {
    glGetTexParameteriv(target, pname, params);
}

void aglGetUniformfv(GLuint program, GLint location, GLfloat * params) {
    glGetUniformfv(program, location, params);
}

void aglGetUniformiv(GLuint program, GLint location, GLint * params) {
    glGetUniformiv(program, location, params);
}

GLint aglGetUniformLocation(GLuint program, const GLchar * name) {
    return glGetUniformLocation(program, name);
}

void aglGetVertexAttribfv(GLuint index, GLenum pname, GLfloat * params) {
    glGetVertexAttribfv(index, pname, params);
}

void aglGetVertexAttribiv(GLuint index, GLenum pname, GLint * params) {
    glGetVertexAttribiv(index, pname, params);
}

void aglGetVertexAttribPointerv(GLuint index, GLenum pname, void ** pointer) {
    glGetVertexAttribPointerv(index, pname, pointer);
}

void aglHint(GLenum target, GLenum mode) {
    glHint(target, mode);
}

GLboolean aglIsBuffer(GLuint buffer) {
    return glIsBuffer (buffer);
}

GLboolean aglIsEnabled(GLenum cap) {
    return glIsEnabled(cap);
}

GLboolean aglIsFramebuffer(GLuint framebuffer) {
    return glIsFramebuffer(framebuffer);
}

GLboolean aglIsProgram(GLuint program) {
    return glIsProgram(program);
}

GLboolean aglIsRenderbuffer(GLuint renderbuffer) {
    return glIsRenderbuffer(renderbuffer);
}

GLboolean aglIsShader(GLuint shader) {
    return glIsShader(shader);
}

GLboolean aglIsTexture(GLuint texture) {
    return glIsTexture(texture);
}

void aglLineWidth(GLfloat width) {
    glLineWidth(width);
}

void aglLinkProgram(GLuint program) {
    glLinkProgram(program);
}

void aglPixelStorei(GLenum pname, GLint param) {
    glPixelStorei(pname, param);
}

void aglPolygonOffset(GLfloat factor, GLfloat units) {
    glPolygonOffset(factor, units);
}

void aglReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, void * pixels) {
    glReadPixels(x, y, width, height, format, type, pixels);
}

void aglReleaseShaderCompiler() {
    glReleaseShaderCompiler();
}

void aglRenderbufferStorage(GLenum target, GLenum internalformat, GLsizei width, GLsizei height) {
    glRenderbufferStorage(target, internalformat, width, height);
}

void aglSampleCoverage(GLfloat value, GLboolean invert) {
    glSampleCoverage(value, invert);
}

void aglScissor(GLint x, GLint y, GLsizei width, GLsizei height) {
    glScissor(x, y, width, height);
}

void aglShaderBinary(GLsizei count, const GLuint * shaders, GLenum binaryformat, const void * binary, GLsizei length) {
    glShaderBinary(count, shaders, binaryformat, binary, length);
}

void aglShaderSource(GLuint shader, GLsizei count, const GLchar *const* string, const GLint * length) {
    glShaderSource(shader, count, string, length);
}

void aglStencilFunc(GLenum func, GLint ref, GLuint mask) {
    glStencilFunc(func, ref, mask);
}

void aglStencilFuncSeparate(GLenum face, GLenum func, GLint ref, GLuint mask) {
    glStencilFuncSeparate(face, func, ref, mask);
}

void aglStencilMask(GLuint mask) {
    glStencilMask(mask);
}

void aglStencilMaskSeparate(GLenum face, GLuint mask) {
    glStencilMaskSeparate(face, mask);
}

void aglStencilOp(GLenum fail, GLenum zfail, GLenum zpass) {
    glStencilOp(fail, zfail, zpass);
}

void aglStencilOpSeparate(GLenum face, GLenum sfail, GLenum dpfail, GLenum dppass) {
    glStencilOpSeparate(face, sfail, dpfail, dppass);
}

void aglTexImage2D(GLenum target, GLint level, GLint internalformat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const void * pixels) {
    glTexImage2D(target, level, internalformat, width, height, border, format, type, pixels);
}

void aglTexParameterf(GLenum target, GLenum pname, GLfloat param) {
    glTexParameterf(target, pname, param);
}

void aglTexParameterfv(GLenum target, GLenum pname, const GLfloat * params) {
    glTexParameterfv(target, pname, params);
}

void aglTexParameteri(GLenum target, GLenum pname, GLint param) {
    glTexParameteri(target, pname, param);
}

void aglTexParameteriv(GLenum target, GLenum pname, const GLint * params) {
    glTexParameteriv(target, pname, params);
}

void aglTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const void * pixels) {
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void aglUniform1f(GLint location, GLfloat v0) {
    glUniform1f(location, v0);
}

void aglUniform1fv(GLint location, GLsizei count, const GLfloat * value) {
    glUniform1fv(location, count, value);
}

void aglUniform1i(GLint location, GLint v0) {
    glUniform1i(location, v0);
}

void aglUniform1iv(GLint location, GLsizei count, const GLint * value) {
    glUniform1iv(location, count, value);
}

void aglUniform2f(GLint location, GLfloat v0, GLfloat v1) {
    glUniform2f(location, v0, v1);
}

void aglUniform2fv(GLint location, GLsizei count, const GLfloat * value) {
    glUniform2fv(location, count, value);
}

void aglUniform2i(GLint location, GLint v0, GLint v1) {
    glUniform2i(location, v0, v1);
}

void aglUniform2iv(GLint location, GLsizei count, const GLint * value) {
    glUniform2iv(location, count, value);
}

void aglUniform3f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2) {
    glUniform3f(location, v0, v1, v2);
}

void aglUniform3fv(GLint location, GLsizei count, const GLfloat * value) {
    glUniform3fv(location, count, value);
}

void aglUniform3i(GLint location, GLint v0, GLint v1, GLint v2) {
    glUniform3i(location, v0, v1, v2);
}

void aglUniform3iv(GLint location, GLsizei count, const GLint * value) {
    glUniform3iv(location, count, value);
}

void aglUniform4f(GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) {
    glUniform4f(location, v0, v1, v2, v3);
}

void aglUniform4fv(GLint location, GLsizei count, const GLfloat * value) {
    glUniform4fv(location, count, value);
}

void aglUniform4i(GLint location, GLint v0, GLint v1, GLint v2, GLint v3) {
    glUniform4i(location, v0, v1, v2, v3);
}

void aglUniform4iv(GLint location, GLsizei count, const GLint * value) {
    glUniform4iv(location, count, value);
}

void aglUniformMatrix2fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glUniformMatrix2fv(location, count, transpose, value);
}

void aglUniformMatrix3fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glUniformMatrix3fv(location, count, transpose, value);
}

void aglUniformMatrix4fv(GLint location, GLsizei count, GLboolean transpose, const GLfloat * value) {
    glUniformMatrix4fv(location, count, transpose, value);
}

void aglUseProgram(GLuint program) {
    glUseProgram(program);
}

void aglValidateProgram(GLuint program) {
    glValidateProgram(program);
}

void aglVertexAttrib1f(GLuint index, GLfloat x) {
    glVertexAttrib1f(index, x);
}

void aglVertexAttrib1fv(GLuint index, const GLfloat * v) {
    glVertexAttrib1fv(index, v);
}

void aglVertexAttrib2f(GLuint index, GLfloat x, GLfloat y) {
    glVertexAttrib2f(index, x, y);
}

void aglVertexAttrib2fv(GLuint index, const GLfloat * v) {
    glVertexAttrib2fv(index, v);
}

void aglVertexAttrib3f(GLuint index, GLfloat x, GLfloat y, GLfloat z) {
    glVertexAttrib3f(index, x, y, z);
}

void aglVertexAttrib3fv(GLuint index, const GLfloat * v) {
    glVertexAttrib3fv(index, v);
}

void aglVertexAttrib4f(GLuint index, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
    glVertexAttrib4f(index, x, y, z, w);
}

void aglVertexAttrib4fv(GLuint index, const GLfloat * v) {
    glVertexAttrib4fv(index, v);
}

void aglVertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void * pointer) {
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}

void aglViewport(GLint x, GLint y, GLsizei width, GLsizei height) {
    glViewport(x, y, width, height);
}

#include "qamigaopenglcontext_p.h"

QFunctionPointer QAmigaOpenGLContext::getProcAddress(const char *procName)
{
    QHash<QString, QFunctionPointer> functions;
    functions["glActiveTexture"] = QFunctionPointer(aglActiveTexture);
    functions["glAttachShader"] = QFunctionPointer(aglAttachShader);
    functions["glBindAttribLocation"] = QFunctionPointer(aglBindAttribLocation);
    functions["glBindBuffer"] = QFunctionPointer(aglBindBuffer);
    functions["glBindFramebuffer"] = QFunctionPointer(aglBindFramebuffer);
    functions["glBindRenderbuffer"] = QFunctionPointer(aglBindRenderbuffer);
    functions["glBindTexture"] = QFunctionPointer(aglBindTexture);
    functions["glBlendColor"] = QFunctionPointer(aglBlendColor);
    functions["glBlendEquation"] = QFunctionPointer(aglBlendEquation);
    functions["glBlendEquationSeparate"] = QFunctionPointer(aglBlendEquationSeparate);
    functions["glBlendFunc"] = QFunctionPointer(aglBlendFunc);
    functions["glBlendFuncSeparate"] = QFunctionPointer(aglBlendFuncSeparate);
    functions["glBufferData"] = QFunctionPointer(aglBufferData);
    functions["glBufferSubData"] = QFunctionPointer(aglBufferSubData);
    functions["glCheckFramebufferStatus"] = QFunctionPointer(aglCheckFramebufferStatus);
    functions["glClear"] = QFunctionPointer(aglClear);
    functions["glClearColor"] = QFunctionPointer(aglClearColor);
    functions["glClearDepthf"] = QFunctionPointer(aglClearDepthf);
    functions["glClearStencil"] = QFunctionPointer(aglClearStencil);
    functions["glColorMask"] = QFunctionPointer(aglColorMask);
    functions["glCompileShader"] = QFunctionPointer(aglCompileShader);
    functions["glCompressedTexImage2D"] = QFunctionPointer(aglCompressedTexImage2D);
    functions["glCompressedTexSubImage2D"] = QFunctionPointer(aglCompressedTexSubImage2D);
    functions["glCopyTexImage2D"] = QFunctionPointer(aglCopyTexImage2D);
    functions["glCopyTexSubImage2D"] = QFunctionPointer(aglCopyTexSubImage2D);
    functions["glCreateProgram"] = QFunctionPointer(aglCreateProgram);
    functions["glCreateShader"] = QFunctionPointer(aglCreateShader);
    functions["glCullFace"] = QFunctionPointer(aglCullFace);
    functions["glDeleteBuffers"] = QFunctionPointer(aglDeleteBuffers);
    functions["glDeleteFramebuffers"] = QFunctionPointer(aglDeleteFramebuffers);
    functions["glDeleteProgram"] = QFunctionPointer(aglDeleteProgram);
    functions["glDeleteRenderbuffers"] = QFunctionPointer(aglDeleteRenderbuffers);
    functions["glDeleteShader"] = QFunctionPointer(aglDeleteShader);
    functions["glDeleteTextures"] = QFunctionPointer(aglDeleteTextures);
    functions["glDepthFunc"] = QFunctionPointer(aglDepthFunc);
    functions["glDepthMask"] = QFunctionPointer(aglDepthMask);
    functions["glDepthRangef"] = QFunctionPointer(aglDepthRangef);
    functions["glDetachShader"] = QFunctionPointer(aglDetachShader);
    functions["glDisable"] = QFunctionPointer(aglDisable);
    functions["glDisableVertexAttribArray"] = QFunctionPointer(aglDisableVertexAttribArray);
    functions["glDrawArrays"] = QFunctionPointer(aglDrawArrays);
    functions["glDrawElements"] = QFunctionPointer(aglDrawElements);
    functions["glEnable"] = QFunctionPointer(aglEnable);
    functions["glEnableVertexAttribArray"] = QFunctionPointer(aglEnableVertexAttribArray);
    functions["glFinish"] = QFunctionPointer(aglFinish);
    functions["glFlush"] = QFunctionPointer(aglFlush);
    functions["glFramebufferRenderbuffer"] = QFunctionPointer(aglFramebufferRenderbuffer);
    functions["glFramebufferTexture2D"] = QFunctionPointer(aglFramebufferTexture2D);
    functions["glFrontFace"] = QFunctionPointer(aglFrontFace);
    functions["glGenBuffers"] = QFunctionPointer(aglGenBuffers);
    functions["glGenerateMipmap"] = QFunctionPointer(aglGenerateMipmap);
    functions["glGenFramebuffers"] = QFunctionPointer(aglGenFramebuffers);
    functions["glGenRenderbuffers"] = QFunctionPointer(aglGenRenderbuffers);
    functions["glGenTextures"] = QFunctionPointer(aglGenTextures);
    functions["glGetActiveAttrib"] = QFunctionPointer(aglGetActiveAttrib);
    functions["glGetActiveUniform"] = QFunctionPointer(aglGetActiveUniform);
    functions["glGetAttachedShaders"] = QFunctionPointer(aglGetAttachedShaders);
    functions["glGetAttribLocation"] = QFunctionPointer(aglGetAttribLocation);
    functions["glGetBooleanv"] = QFunctionPointer(aglGetBooleanv);
    functions["glGetBufferParameteriv"] = QFunctionPointer(aglGetBufferParameteriv);
    functions["glGetError"] = QFunctionPointer(aglGetError);
    functions["glGetFloatv"] = QFunctionPointer(aglGetFloatv);
    functions["glGetFramebufferAttachmentParameteriv"] = QFunctionPointer(aglGetFramebufferAttachmentParameteriv);
    functions["glGetIntegerv"] = QFunctionPointer(aglGetIntegerv);
    functions["glGetProgramiv"] = QFunctionPointer(aglGetProgramiv);
    functions["glGetProgramInfoLog"] = QFunctionPointer(aglGetProgramInfoLog);
    functions["glGetRenderbufferParameteriv"] = QFunctionPointer(aglGetRenderbufferParameteriv);
    functions["glGetShaderiv"] = QFunctionPointer(aglGetShaderiv);
    functions["glGetShaderInfoLog"] = QFunctionPointer(aglGetShaderInfoLog);
    functions["glGetShaderPrecisionFormat"] = QFunctionPointer(aglGetShaderPrecisionFormat);
    functions["glGetShaderSource"] = QFunctionPointer(aglGetShaderSource);
    functions["glGetString"] = QFunctionPointer(aglGetString);
    functions["glGetTexParameterfv"] = QFunctionPointer(aglGetTexParameterfv);
    functions["glGetTexParameteriv"] = QFunctionPointer(aglGetTexParameteriv);
    functions["glGetUniformfv"] = QFunctionPointer(aglGetUniformfv);
    functions["glGetUniformiv"] = QFunctionPointer(aglGetUniformiv);
    functions["glGetUniformLocation"] = QFunctionPointer(aglGetUniformLocation);
    functions["glGetVertexAttribfv"] = QFunctionPointer(aglGetVertexAttribfv);
    functions["glGetVertexAttribiv"] = QFunctionPointer(aglGetVertexAttribiv);
    functions["glGetVertexAttribPointerv"] = QFunctionPointer(aglGetVertexAttribPointerv);
    functions["glHint"] = QFunctionPointer(aglHint);
    functions["glIsBuffer"] = QFunctionPointer(aglIsBuffer);
    functions["glIsEnabled"] = QFunctionPointer(aglIsEnabled);
    functions["glIsFramebuffer"] = QFunctionPointer(aglIsFramebuffer);
    functions["glIsProgram"] = QFunctionPointer(aglIsProgram);
    functions["glIsRenderbuffer"] = QFunctionPointer(aglIsRenderbuffer);
    functions["glIsShader"] = QFunctionPointer(aglIsShader);
    functions["glIsTexture"] = QFunctionPointer(aglIsTexture);
    functions["glLineWidth"] = QFunctionPointer(aglLineWidth);
    functions["glLinkProgram"] = QFunctionPointer(aglLinkProgram);
    functions["glPixelStorei"] = QFunctionPointer(aglPixelStorei);
    functions["glPolygonOffset"] = QFunctionPointer(aglPolygonOffset);
    functions["glReadPixels"] = QFunctionPointer(aglReadPixels);
    functions["glReleaseShaderCompiler"] = QFunctionPointer(aglReleaseShaderCompiler);
    functions["glRenderbufferStorage"] = QFunctionPointer(aglRenderbufferStorage);
    functions["glSampleCoverage"] = QFunctionPointer(aglSampleCoverage);
    functions["glScissor"] = QFunctionPointer(aglScissor);
    functions["glShaderBinary"] = QFunctionPointer(aglShaderBinary);
    functions["glShaderSource"] = QFunctionPointer(aglShaderSource);
    functions["glStencilFunc"] = QFunctionPointer(aglStencilFunc);
    functions["glStencilFuncSeparate"] = QFunctionPointer(aglStencilFuncSeparate);
    functions["glStencilMask"] = QFunctionPointer(aglStencilMask);
    functions["glStencilMaskSeparate"] = QFunctionPointer(aglStencilMaskSeparate);
    functions["glStencilOp"] = QFunctionPointer(aglStencilOp);
    functions["glStencilOpSeparate"] = QFunctionPointer(aglStencilOpSeparate);
    functions["glTexImage2D"] = QFunctionPointer(aglTexImage2D);
    functions["glTexParameterf"] = QFunctionPointer(aglTexParameterf);
    functions["glTexParameterfv"] = QFunctionPointer(aglTexParameterfv);
    functions["glTexParameteri"] = QFunctionPointer(aglTexParameteri);
    functions["glTexParameteriv"] = QFunctionPointer(aglTexParameteriv);
    functions["glTexSubImage2D"] = QFunctionPointer(aglTexSubImage2D);
    functions["glUniform1f"] = QFunctionPointer(aglUniform1f);
    functions["glUniform1fv"] = QFunctionPointer(aglUniform1fv);
    functions["glUniform1i"] = QFunctionPointer(aglUniform1i);
    functions["glUniform1iv"] = QFunctionPointer(aglUniform1iv);
    functions["glUniform2f"] = QFunctionPointer(aglUniform2f);
    functions["glUniform2fv"] = QFunctionPointer(aglUniform2fv);
    functions["glUniform2i"] = QFunctionPointer(aglUniform2i);
    functions["glUniform2iv"] = QFunctionPointer(aglUniform2iv);
    functions["glUniform3f"] = QFunctionPointer(aglUniform3f);
    functions["glUniform3fv"] = QFunctionPointer(aglUniform3fv);
    functions["glUniform3i"] = QFunctionPointer(aglUniform3i);
    functions["glUniform3iv"] = QFunctionPointer(aglUniform3iv);
    functions["glUniform4f"] = QFunctionPointer(aglUniform4f);
    functions["glUniform4fv"] = QFunctionPointer(aglUniform4fv);
    functions["glUniform4i"] = QFunctionPointer(aglUniform4i);
    functions["glUniform4iv"] = QFunctionPointer(aglUniform4iv);
    functions["glUniformMatrix2fv"] = QFunctionPointer(aglUniformMatrix2fv);
    functions["glUniformMatrix3fv"] = QFunctionPointer(aglUniformMatrix3fv);
    functions["glUniformMatrix4fv"] = QFunctionPointer(aglUniformMatrix4fv);
    functions["glUseProgram"] = QFunctionPointer(aglUseProgram);
    functions["glValidateProgram"] = QFunctionPointer(aglValidateProgram);
    functions["glVertexAttrib1fv"] = QFunctionPointer(aglVertexAttrib1f);
    functions["glVertexAttrib1fv"] = QFunctionPointer(aglVertexAttrib1fv);
    functions["glVertexAttrib2f"] = QFunctionPointer(aglVertexAttrib2f);
    functions["glVertexAttrib2fv"] = QFunctionPointer(aglVertexAttrib2fv);
    functions["glVertexAttrib3f"] = QFunctionPointer(aglVertexAttrib3f);
    functions["glVertexAttrib3fv"] = QFunctionPointer(aglVertexAttrib3fv);
    functions["glVertexAttrib4f"] = QFunctionPointer(aglVertexAttrib4f);
    functions["glVertexAttrib4fv"] = QFunctionPointer(aglVertexAttrib4fv);
    functions["glVertexAttribPointer"] = QFunctionPointer(aglVertexAttribPointer);
    functions["glViewport"] = QFunctionPointer(aglViewport);
    return functions.value(procName);
}
