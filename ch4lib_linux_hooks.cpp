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
    return pOrig_SDL_GL_GetProcAddress(proc);
}
