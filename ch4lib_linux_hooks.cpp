#include <SDL2/SDL.h>
#include <dlfcn.h>
#include "opengl.h"

#ifdef __cplusplus
#define HOOKED_EXPORT extern "C" __attribute__ ((visibility ("default")))
#else
#define HOOKED_EXPORT __attribute__ ((visibility ("default")))
#endif // __cplusplus

bool bVK_LSHIFT=false;

char szGameMode[15];
const char szLibSDL2[]="./libSDL2.so";
const char szHwSo[]="./hw.so";
const char szClientDll[]="/cl_dlls/client.so";
char szFullClientDllPath[sizeof(szClientDll)+15];

//Hooked
HOOKED_EXPORT void*SDL_GL_GetProcAddress(const char*proc);
HOOKED_EXPORT int SDL_PollEvent(SDL_Event*event);

__typeof__(SDL_GL_GetProcAddress)*pOrig_SDL_GL_GetProcAddress=0;
__typeof__(SDL_PollEvent)*pOrig_SDL_PollEvent=0;

HOOKED_EXPORT void*SDL_GL_GetProcAddress(const char*proc)
{
    static bool bOpenGLPointers=false;

    while(!pOrig_SDL_GL_GetProcAddress)
    {
        puts("[B#] SDL_GL_GetProcAddress!");
        pOrig_SDL_GL_GetProcAddress=(__typeof__(SDL_GL_GetProcAddress)*)dlsym(dlopen(szLibSDL2,RTLD_NOW),"SDL_GL_GetProcAddress");
    }

    if(!bOpenGLPointers && pOrig_SDL_GL_GetProcAddress)
    {
        // Non-hooked GL!
        pglGetFloatv=(__typeof__(glGetFloatv)*)pOrig_SDL_GL_GetProcAddress("glGetFloatv");
        pglGetIntegerv=(__typeof__(glGetIntegerv)*)pOrig_SDL_GL_GetProcAddress("glGetIntegerv");
        pglClearColor=(__typeof__(glClearColor)*)pOrig_SDL_GL_GetProcAddress("glClearColor");
        pglTexEnvi=(__typeof__(glTexEnvi)*)pOrig_SDL_GL_GetProcAddress("glTexEnvi");
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

HOOKED_EXPORT int SDL_PollEvent(SDL_Event*event)
{
    while(!pOrig_SDL_PollEvent)
    {
        puts("[B#] SDL_PollEvent!");
        pOrig_SDL_PollEvent=(__typeof__(SDL_PollEvent)*)dlsym(dlopen(szLibSDL2,RTLD_NOW),"SDL_PollEvent");
    }
    int iReturn=pOrig_SDL_PollEvent(event);
    if(event->type==SDL_KEYDOWN&&event->key.keysym.scancode==SDL_SCANCODE_LSHIFT)
        bVK_LSHIFT=true;
    else if(event->type==SDL_KEYUP&&event->key.keysym.scancode==SDL_SCANCODE_LSHIFT)
        bVK_LSHIFT=false;
    return iReturn;
}

void*LinuxVirtualProtect(void*address,size_t size,int protections)
{
    long pagesize;
    pagesize=sysconf(_SC_PAGESIZE);
    address=(void*)((long)address&~(pagesize-1));
    if(mprotect(address,size,protections)==0)
        return address;
    return 0;
}

void*fake_malloc(size_t size)
{
    void *retadd=mmap(0,size,PROT_READ|PROT_WRITE|PROT_EXEC,MAP_ANON|MAP_PRIVATE,-1,0);
    if(retadd==MAP_FAILED)
        return 0;
    return retadd;
}

void*DetourFunction(unsigned char*orig,unsigned char*hook,int len)
{
    unsigned char*jmp=(unsigned char*)fake_malloc(len+5);
    LinuxVirtualProtect(orig,len,PROT_READ|PROT_WRITE|PROT_EXEC);
    memcpy(jmp,orig,len);
    jmp+=len; // increment to the end of the copied bytes
    jmp[0]=0xE9;
    *(unsigned int*)(jmp+1)=(unsigned int)(orig+len-jmp)-5;
    memset(orig,0x90,len);
    orig[0]=0xE9;
    *(unsigned int*)(orig+1)=(unsigned int)(hook-orig)-5;
    //LinuxVirtualProtect(orig,len,PROT_READ|PROT_EXEC);
    return(jmp-len);
}

void*GetAndHooksEngineThread(void*arg)
{
    cldll_func_t*pExportTable=0;
    cl_enginefunc_t*pEngfuncs=0;
    engine_studio_api_t*pEngineStudio=0;

    //Engine
    while(!(pEngfuncs=(cl_enginefunc_t*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"gEngfuncs")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));//60fps
    while(!(pEngineStudio=(engine_studio_api_t*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"IEngineStudio")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    memcpy(&gEngfuncs,pEngfuncs,sizeof(cl_enginefunc_t));
    memcpy(&gEngStudio,pEngineStudio,sizeof(cl_enginefunc_t));

    //User messages
    puts("[B#] UserMsg trampolines begin!");
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z18__MsgFunc_TeamInfoPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pTeamInfo=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z18__MsgFunc_TeamInfoPKciPv"),
                                                          (unsigned char*)&TeamInfo,5);
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z19__MsgFunc_CurWeaponPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pCurWeapon=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z19__MsgFunc_CurWeaponPKciPv"),
                                                            (unsigned char*)&CurWeapon,9);
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z21__MsgFunc_ScoreAttribPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pScoreAttrib=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z21__MsgFunc_ScoreAttribPKciPv"),
                                                              (unsigned char*)&ScoreAttrib,8);
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z16__MsgFunc_SetFOVPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pSetFOV=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z16__MsgFunc_SetFOVPKciPv"),
                                                        (unsigned char*)&SetFOV,8);
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z16__MsgFunc_HealthPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pHealth=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z16__MsgFunc_HealthPKciPv"),
                                                        (unsigned char*)&Health,7);
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z17__MsgFunc_BatteryPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pBattery=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z17__MsgFunc_BatteryPKciPv"),
                                                          (unsigned char*)&Battery,7);
    //ScoreInfo
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z18__MsgFunc_DeathMsgPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pDeathMsg=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z18__MsgFunc_DeathMsgPKciPv"),
                                                          (unsigned char*)&DeathMsg,7);
    //SayText
    //Damage
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z15__MsgFunc_AmmoXPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pAmmoX=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z15__MsgFunc_AmmoXPKciPv"),
                                                        (unsigned char*)&AmmoX,8);
    while(!(CH4::Pointers::Money=(pfnUserMsgHook)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z15__MsgFunc_MoneyPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pMoney=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z15__MsgFunc_MoneyPKciPv"),
                                                        (unsigned char*)&Money,8);
    while(!(dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z15__MsgFunc_RadarPKciPv")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pRadar=(pfnUserMsgHook)DetourFunction((unsigned char*)dlsym(dlopen(szFullClientDllPath,RTLD_NOW),"_Z15__MsgFunc_RadarPKciPv"),
                                                        (unsigned char*)&Radar,8);
    /*WeaponList
    Fog
    BombDrop
    BombPickup
    HostagePos
    HostageK
    ServerName*/
    puts("[B#] UserMsg trampolines end!");

    //Export Table
    while(!(pExportTable=(cldll_func_t*)dlsym(dlopen(szHwSo,RTLD_NOW),"cl_funcs")))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    memcpy(&gExport,pExportTable,sizeof(cldll_func_t));

    //HUD_Redraw
    while(!(pExportTable->pPostRunCmd))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pExportTable->pPostRunCmd=(HUD_POSTRUNCMD_FUNC)&HUD_PostRunCmd;

    while(!(pExportTable->pCalcRefdef))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pExportTable->pCalcRefdef=(HUD_CALCREF_FUNC)&V_CalcRefdef;

    //HUD_PlayerMoveInit
    while(!(pExportTable->pClientMove))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pExportTable->pClientMove=(HUD_CLIENTMOVE_FUNC)&HUD_PlayerMove;

    while(!(pExportTable->pCL_CreateMove))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pExportTable->pCL_CreateMove=(HUD_CLIENTMOVE_FUNC)&CL_CreateMove;

    while(!(pExportTable->pAddEntity))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pExportTable->pAddEntity=(HUD_ADDENTITY_FUNC)&HUD_AddEntity;

    //HUD_Key_Event
    //HUD_UpdateClientData

    while(!(pExportTable->pHudFrame))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    pExportTable->pHudFrame=(HUD_FRAME_FUNC)&HUD_Frame;

    /*while(!(pExportTable->pHudInitFunc))
        std::this_thread::sleep_for(std::chrono::milliseconds(17));
    CH4::Pointers::HUD_Init=(HUD_INIT_FUNC)pExportTable->pHudInitFunc;*/
    pthread_exit(0);
}

static void Crianosfera_FakeEntry_Constructor_Point(int argc,char*argv[],char*envp[])
{
    strcpy(szGameMode,"valve");
    int i=0;
    for(;i<argc;i++)
    {
        if(!strcmp(argv[i],"-game"))
            if(i<(argc-1))
                strcpy(szGameMode,argv[i+1]),
                printf("[B#] Fake entry point found game: %s\n",argv[i+1]);
    }
    szFullClientDllPath[0]=0;
    strcpy(szFullClientDllPath,"./");
    strcat(szFullClientDllPath,szGameMode);
    strcat(szFullClientDllPath,szClientDll);

    //std::thread EngineThread(GetAndHooksEngineThread);
    //EngineThread.join();
    pthread_t EngineThread;
    pthread_create(&EngineThread,0,&GetAndHooksEngineThread,0);
}

__attribute__((section(".init_array"))) void (* p_blood_main)(int,char*[],char*[]) = &Crianosfera_FakeEntry_Constructor_Point;
