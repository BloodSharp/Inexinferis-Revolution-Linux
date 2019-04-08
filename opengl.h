#ifndef NOPENGL_H
#define NOPENGL_H

#include <GL/gl.h>
#include <GL/glu.h>

//New OpenGL Functions
GLvoid APIENTRY glBindBuffer(GLenum target, GLuint buffer);
GLvoid * APIENTRY glMapBuffer(GLenum target, GLenum access);
GLboolean APIENTRY glUnmapBuffer(GLenum target);
void APIENTRY glGenBuffers(GLsizei n,GLuint * buffers);
void APIENTRY glBufferData(GLenum target,GLsizei size,const GLvoid * data,GLenum usage);

__typeof__(glEnable)*pglEnable;
__typeof__(glDisable)*pglDisable;
__typeof__(glColor4f)*pglColor4f;
__typeof__(glGetFloatv)*pglGetFloatv;
__typeof__(glGetIntegerv)*pglGetIntegerv;
__typeof__(glClearColor)*pglClearColor;
__typeof__(glTexEnvi)*pglTexEnvi;
__typeof__(glBlendFunc)*pglBlendFunc;
__typeof__(glDepthRange)*pglDepthRange;
__typeof__(glDepthFunc)*pglDepthFunc;
__typeof__(glClear)*pglClear;
//tglVertex2f pglVertex2f;
__typeof__(glVertex3f)*pglVertex3f;
__typeof__(glVertex3fv)*pglVertex3fv;
__typeof__(glBegin)*pglBegin;
__typeof__(glEnd)*pglEnd;
__typeof__(glFrustum)*pglFrustum;
__typeof__(glReadBuffer)*pglReadBuffer;
__typeof__(glReadPixels)*pglReadPixels;
__typeof__(glPolygonMode)*pglPolygonMode;
__typeof__(glLineWidth)*pglLineWidth;
__typeof__(glColor3f)*pglColor3f;
__typeof__(glViewport)*pglViewport;
__typeof__(glPopMatrix)*pglPopMatrix;
__typeof__(glGenTextures)*pglGenTextures;
__typeof__(glBindTexture)*pglBindTexture;
__typeof__(glTexImage2D)*pglTexImage2D;
__typeof__(glTexParameteri)*pglTexParameteri;
__typeof__(glTexCoord2f)*pglTexCoord2f;

//New OpenGL Functions
__typeof__(glBindBuffer)*pglBindBuffer;
__typeof__(glMapBuffer)*pglMapBuffer;
__typeof__(glUnmapBuffer)*pglUnmapBuffer;
__typeof__(glGenBuffers)*pglGenBuffers;
__typeof__(glBufferData)*pglBufferData;

void APIENTRY hglBegin(GLenum mode);
void APIENTRY hglClear(GLbitfield mask);
void APIENTRY hglVertex3fv(const GLfloat *v);
void APIENTRY hglEnable(GLenum mode);
void APIENTRY hglDisable(GLenum mode);
void APIENTRY hglFrustum(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar);
void APIENTRY hglBlendFunc(GLenum sfactor,GLenum dfactor);
void APIENTRY hglColor4f(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha);
void APIENTRY hglViewport(GLint x,GLint y,GLsizei width,GLsizei height);
void APIENTRY hglReadPixels(GLint x,GLint	y,GLsizei	width,GLsizei	height,GLenum format,GLenum type,GLvoid *data);

void APIENTRY glCreateTextureBuffer(GLint width,GLint height,GLvoid* data);
void APIENTRY glDrawTexture(GLint x,GLint y,GLint width,GLint height);

extern bool oglSubtractive;
extern bool oglChams;
extern float oglChamsColor[3];

#endif //NOPENGL_H
