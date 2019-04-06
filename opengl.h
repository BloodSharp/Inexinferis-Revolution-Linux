#ifndef NOPENGL_H
#define NOPENGL_H

#include <GL/gl.h>
#include <GL/glu.h>

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

/New OpenGL Functions
//__typeof__(pwglGetProcAddress;
__typeof__(glBindBuffer)*pglBindBuffer;
__typeof__(glMapBuffer)*pglMapBuffer;
__typeof__(glUnmapBuffer)*pglUnmapBuffer;
__typeof__(glGenBuffers)*pglGenBuffers;
__typeof__(glBufferData)*pglBufferData;

typedef int (WINAPI *tSetCltProcTable)(PDWORD pDst1,PDWORD pDst2,DWORD iSize);

BOOL WINAPI HookOpenGl();
void WINAPI glCreateTextureBuffer(GLint width,GLint height,GLvoid* data);
void WINAPI glDrawTexture(GLint x,GLint y,GLint width,GLint height);

extern tglDepthRange pglDepthRange;
extern tglDepthFunc pglDepthFunc;
extern tglTexEnvi pglTexEnvi;
extern tglEnable pglEnable;
extern tglDisable pglDisable;
extern tglColor4f pglColor4f;
extern tglGetFloatv pglGetFloatv;
extern tglGetIntegerv pglGetIntegerv;
extern tglClearColor pglClearColor;
extern tglBlendFunc pglBlendFunc;
extern tglClear pglClear;
//extern tglVertex2f pglVertex2f;
extern tglVertex3f pglVertex3f;
extern tglVertex3fv pglVertex3fv;
extern tglBegin pglBegin;
extern tglEnd pglEnd;
extern tglFrustum pglFrustum;
extern tglReadBuffer pglReadBuffer;
extern tglReadPixels pglReadPixels;
extern tglPolygonMode pglPolygonMode;
extern tglLineWidth pglLineWidth;
extern tglColor3f pglColor3f;
extern tglViewport pglViewport;
extern tglGenTextures pglGenTextures;
extern tglBindTexture pglBindTexture;
extern tglTexImage2D pglTexImage2D;
extern tglTexParameteri pglTexParameteri;
extern tglTexCoord2f pglTexCoord2f;

//New OpenGL Functions
extern twglGetProcAddress pwglGetProcAddress;
extern tglBindBuffer pglBindBuffer;
extern tglMapBuffer pglMapBuffer;
extern tglUnmapBuffer pglUnmapBuffer;
extern tglGenBuffers pglGenBuffers;
extern tglBufferData pglBufferData;

extern bool oglSubtractive;
extern bool oglChams;
extern float oglChamsColor[3];

#endif //NOPENGL_H
