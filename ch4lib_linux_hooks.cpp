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
    while(!pOrig_SDL_GL_GetProcAddress)
    {
        puts("[B#] SDL_GL_GetProcAddress!");
        pOrig_SDL_GL_GetProcAddress=(__typeof__(SDL_GL_GetProcAddress)*)ssltrace_dlsym("SDL_GL_GetProcAddress");
    }

    // Non-hooked GL!
    if(!strcmp(proc,"glGetFloatv"))
    {
        pglGetFloatv=(__typeof__(glGetFloatv)*)=pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglGetFloatv;
    }
    else if(!strcmp(proc,"glGetIntegerv"))
    {
        pglGetIntegerv=(__typeof__(glGetIntegerv)*)=pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglGetIntegerv;
    }
    else if(!strcmp(proc,"glClearColor"))
    {
        pglClearColor=(__typeof__(glClearColor)*)=pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglClearColor;
    }
    else if(!strcmp(proc,"glTexEnvi"))
    {
        pglTexEnvi=(__typeof__(glTexEnvi)*)=pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglTexEnvi;
    }
    else if(!strcmp(proc,"glDepthRange"))
    {
        pglDepthRange=(__typeof__(glDepthRange)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglDepthRange;
    }
    else if(!strcmp(proc,"glDepthFunc"))
    {
        pglDepthFunc=(__typeof__(glDepthFunc)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglDepthFunc;
    }
    else if(!strcmp(proc,"glVertex3f"))
    {
        pglVertex3f=(__typeof__(glVertex3f)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglVertex3f;
    }
    else if(!strcmp(proc,"glEnd"))
    {
        pglEnd=(__typeof__(glEnd)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglEnd;
    }
    else if(!strcmp(proc,"pglReadBuffer"))
    {
        pglReadBuffer=(__typeof__(glReadBuffer)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglReadBuffer;
    }
    else if(!strcmp(proc,"glPolygonMode"))
    {
        pglPolygonMode=(__typeof__(glPolygonMode)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglPolygonMode;
    }
    else if(!strcmp(proc,"glLineWidth"))
    {
        pglLineWidth=(__typeof__(glLineWidth)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglLineWidth;
    }
    else if(!strcmp(proc,"glColor3f"))
    {
        pglColor3f=(__typeof__(glColor3f)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglColor3f;
    }
    else if(!strcmp(proc,"glPopMatrix"))
    {
        pglPopMatrix=(__typeof__(glPopMatrix)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglPopMatrix;
    }
    else if(!strcmp(proc,"glGenTextures"))
    {
        pglGenTextures=(__typeof__(glGenTextures)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglGenTextures;
    }
    else if(!strcmp(proc,"glBindTexture"))
    {
        pglBindTexture=(__typeof__(glBindTexture)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglBindTexture;
    }
    else if(!strcmp(proc,"glTexImage2D"))
    {
        pglTexImage2D=(__typeof__(glTexImage2D)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglTexImage2D;
    }
    else if(!strcmp(proc,"glTexParameteri"))
    {
        pglTexParameteri=(__typeof__(glTexParameteri)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglTexParameteri;
    }
    else if(!strcmp(proc,"glTexCoord2f"))
    {
        pglTexCoord2f=(__typeof__(glTexCoord2f)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglTexCoord2f;
    }

    //New OpenGL Functions !VERIFICAR!
    else if(!strcmp(proc,"glBindBuffer"))
    {
        pglBindBuffer=(__typeof__(glBindBuffer)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglBindBuffer;
    }
    else if(!strcmp(proc,"glMapBuffer"))
    {
        pglMapBuffer=(__typeof__(glMapBuffer)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglMapBuffer;
    }
    else if(!strcmp(proc,"glUnmapBuffer"))
    {
        pglUnmapBuffer=(__typeof__(glUnmapBuffer)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglUnmapBuffer;
    }
    else if(!strcmp(proc,"pglGenBuffers"))
    {
        pglGenBuffers=(__typeof__(glGenBuffers)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglGenBuffers;
    }
    else if(!strcmp(proc,"glBufferData"))
    {
        pglBufferData=(__typeof__(glBufferData)*)pOrig_SDL_GL_GetProcAddress(proc);
        return(void*)pglBufferData;
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
