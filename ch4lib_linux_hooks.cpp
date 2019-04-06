#include <SDL2/SDL2.h>
#include "opengl.h"

#ifdef __cplusplus
#define HOOKED_EXPORT extern "C" __attribute__ ((visibility ("default")))
#else
#define HOOKED_EXPORT __attribute__ ((visibility ("default")))
#endif // __cplusplus

//Hooked
HOOKED_EXPORT void*SDL_GL_GetProcAddress(const char*proc);
HOOKED_EXPORT void SDL_GL_SwapWindow(SDL_Window*window);
HOOKED_EXPORT int SDL_PollEvent(SDL_Event*event);
HOOKED_EXPORT SDL_GLContext SDL_GL_CreateContext(SDL_Window*window);

__typeof__(SDL_GL_GetProcAddress)*pOrig_SDL_GL_GetProcAddress=0;

HOOKED_EXPORT void*SDL_GL_GetProcAddress(const char*proc)
{
    while(!pOrig_SDL_GL_GetProcAddress)
    {
        puts("[B#] SDL_GL_GetProcAddress!");
        pOrig_SDL_GL_GetProcAddress=(__typeof__(SDL_GL_GetProcAddress)*)ssltrace_dlsym("SDL_GL_GetProcAddress");
    }

    // Hooked GL!
    if(!strcmp(proc,"glBegin"))
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
