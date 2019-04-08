#include <SDL2/SDL2.h>
#include "opengl.h"

#ifdef __cplusplus
#define HOOKED_EXPORT extern "C" __attribute__ ((visibility ("default")))
#else
#define HOOKED_EXPORT __attribute__ ((visibility ("default")))
#endif // __cplusplus

//Hooked
HOOKED_EXPORT void*SDL_GL_GetProcAddress(const char*proc);

__typeof__(SDL_GL_GetProcAddress)*pOrig_SDL_GL_GetProcAddress=0;

HOOKED_EXPORT void*SDL_GL_GetProcAddress(const char*proc)
{
    static bool bOpenGLPointers=false;

    while(!pOrig_SDL_GL_GetProcAddress)
    {
        puts("[B#] SDL_GL_GetProcAddress!");
        pOrig_SDL_GL_GetProcAddress=(__typeof__(SDL_GL_GetProcAddress)*)dlsym(dlopen("./libSDL2.so",RTLD_NOW),"SDL_GL_GetProcAddress");
    }

    if(!bOpenGLPointers && pOrig_SDL_GL_GetProcAddress)
    {
        // Non-hooked GL!
        pglGetFloatv=(__typeof__(glGetFloatv)*)=pOrig_SDL_GL_GetProcAddress("glGetFloatv");
        pglGetIntegerv=(__typeof__(glGetIntegerv)*)=pOrig_SDL_GL_GetProcAddress("glGetIntegerv");
        pglClearColor=(__typeof__(glClearColor)*)=pOrig_SDL_GL_GetProcAddress("glClearColor");
        pglTexEnvi=(__typeof__(glTexEnvi)*)=pOrig_SDL_GL_GetProcAddress("glTexEnvi");
        pglDepthRange=(__typeof__(glDepthRange)*)pOrig_SDL_GL_GetProcAddress("glDepthRange");
        pglDepthFunc=(__typeof__(glDepthFunc)*)pOrig_SDL_GL_GetProcAddress("glDepthFunc");
        pglVertex3f=(__typeof__(glVertex3f)*)pOrig_SDL_GL_GetProcAddress("glVertex3f");
        pglEnd=(__typeof__(glEnd)*)pOrig_SDL_GL_GetProcAddress("glEnd");
        pglReadBuffer=(__typeof__(glReadBuffer)*)pOrig_SDL_GL_GetProcAddress("glReadBuffer");
        pglPolygonMode=(__typeof__(glPolygonMode)*)pOrig_SDL_GL_GetProcAddress("glPolygonMode");
        pglLineWidth=(__typeof__(glLineWidth)*)pOrig_SDL_GL_GetProcAddress("glLineWidth");
        pglColor3f=(__typeof__(glColor3f)*)pOrig_SDL_GL_GetProcAddress("glColor3f");
        pglPopMatrix=(__typeof__(glPopMatrix)*)pOrig_SDL_GL_GetProcAddress("glPopMatrix");
        pglGenTextures=(__typeof__(glGenTextures)*)pOrig_SDL_GL_GetProcAddress("glGenTextures");
        pglBindTexture=(__typeof__(glBindTexture)*)pOrig_SDL_GL_GetProcAddress("glBindTexture");
        pglTexImage2D=(__typeof__(glTexImage2D)*)pOrig_SDL_GL_GetProcAddress("glTexImage2D");
        pglTexParameteri=(__typeof__(glTexParameteri)*)pOrig_SDL_GL_GetProcAddress("glTexParameteri");
        pglTexCoord2f=(__typeof__(glTexCoord2f)*)pOrig_SDL_GL_GetProcAddress("glTexCoord2f");

        //New OpenGL Functions
        pglBindBuffer=(__typeof__(glBindBuffer)*)pOrig_SDL_GL_GetProcAddress("glBindBuffer");
        pglMapBuffer=(__typeof__(glMapBuffer)*)pOrig_SDL_GL_GetProcAddress("glMapBuffer");
        pglUnmapBuffer=(__typeof__(glUnmapBuffer)*)pOrig_SDL_GL_GetProcAddress("glUnmapBuffer");
        pglGenBuffers=(__typeof__(glGenBuffers)*)pOrig_SDL_GL_GetProcAddress("glGenBuffers");
        pglBufferData=(__typeof__(glBufferData)*)pOrig_SDL_GL_GetProcAddress("glBufferData");

        bOpenGLPointers=true;
    }

    // Hooked GL!
    else if(!strcmp(proc,"glBegin"))
    {
        pglBegin=(__typeof__(glBegin)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglBegin;
    }
    else if(!strcmp(proc,"glClear"))
    {
        pglClear=(__typeof__(glClear)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglClear;
    }
    else if(!strcmp(proc,"glVertex3fv"))
    {
        pglVertex3fv=(__typeof__(glVertex3fv)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglVertex3fv;
    }
    else if(!strcmp(proc,"glEnable"))
    {
        pglEnable=(__typeof__(glEnable)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglEnable;
    }
    else if(!strcmp(proc,"glDisable"))
    {
        pglDisable=(__typeof__(glDisable)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglDisable;
    }
    else if(!strcmp(proc,"glFrustum"))
    {
        pglFrustum=(__typeof__(glFrustum)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglFrustum;
    }
    else if(!strcmp(proc,"glBlendFunc"))
    {
        pglBlendFunc=(__typeof__(glBlendFunc)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglBlendFunc;
    }
    else if(!strcmp(proc,"glColor4f"))
    {
        pglColor4f=(__typeof__(glColor4f)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglColor4f;
    }
    else if(!strcmp(proc,"glViewport"))
    {
        pglViewport=(__typeof__(glViewport)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglViewport;
    }
    else if(!strcmp(proc,"glReadPixels"))
    {
        pglReadPixels=(__typeof__(glReadPixels)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)&hglReadPixels;
    }

    return pOrig_SDL_GL_GetProcAddress(proc);
}
