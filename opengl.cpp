#include "screenshots.h"
#include "autoroute.h"
#include "players.h"
#include "opengl.h"
#include "aimbot.h"
#include "client.h"
#include "utils.h"
#include "cvar.h"

__typeof__(glEnable)*pglEnable=NULL;
__typeof__(glDisable)*pglDisable=NULL;
__typeof__(glColor4f)*pglColor4f=NULL;
__typeof__(glGetFloatv)*pglGetFloatv=NULL;
__typeof__(glGetIntegerv)*pglGetIntegerv=NULL;
__typeof__(glClearColor)*pglClearColor=NULL;
__typeof__(glTexEnvi)*pglTexEnvi=NULL;
__typeof__(glBlendFunc)*pglBlendFunc=NULL;
__typeof__(glDepthRange)*pglDepthRange=NULL;
__typeof__(glDepthFunc)*pglDepthFunc=NULL;
__typeof__(glClear)*pglClear=NULL;
//tglVertex2f pglVertex2f=NULL;
__typeof__(glVertex3f)*pglVertex3f=NULL;
__typeof__(glVertex3fv)*pglVertex3fv=NULL;
__typeof__(glBegin)*pglBegin=NULL;
__typeof__(glEnd)*pglEnd=NULL;
__typeof__(glFrustum)*pglFrustum=NULL;
__typeof__(glReadBuffer)*pglReadBuffer=NULL;
__typeof__(glReadPixels)*pglReadPixels=NULL;
__typeof__(glPolygonMode)*pglPolygonMode=NULL;
__typeof__(glLineWidth)*pglLineWidth=NULL;
__typeof__(glColor3f)*pglColor3f=NULL;
__typeof__(glViewport)*pglViewport=NULL;
__typeof__(glPopMatrix)*pglPopMatrix=NULL;
__typeof__(glGenTextures)*pglGenTextures=NULL;
__typeof__(glBindTexture)*pglBindTexture=NULL;
__typeof__(glTexImage2D)*pglTexImage2D=NULL;
__typeof__(glTexParameteri)*pglTexParameteri=NULL;
__typeof__(glTexCoord2f)*pglTexCoord2f=NULL;

//New OpenGL Functions
//__typeof__(pwglGetProcAddress=NULL;
__typeof__(glBindBuffer)*pglBindBuffer=NULL;
__typeof__(glMapBuffer)*pglMapBuffer=NULL;
__typeof__(glUnmapBuffer)*pglUnmapBuffer=NULL;
__typeof__(glGenBuffers)*pglGenBuffers=NULL;
__typeof__(glBufferData)*pglBufferData=NULL;


HMODULE hOpengl32=NULL;

bool bSkyTex=false,bSmoke=false,bTex=false,oglSubtractive=false,oglChams=false;//,bFlash=false;
float oglChamsColor[3];

GLuint textureID=0;

PBYTE dwFSBase=0,dwFSBase2=0;tSetCltProcTable pSetCltProcTable=NULL;
VOID WINAPI DoTIBHook(PBYTE dwFSBase,PBYTE dwFSBase2);

BOOL WINAPI CheckFuncs(){
  static BOOL bCheckOK=FALSE;
  if(!bCheckOK)
    bCheckOK=(pglEnable&&pglDisable&&pglColor4f&&pglGetFloatv&&pglGetIntegerv&&pglClearColor&&pglTexEnvi&&pglBlendFunc&&pglDepthRange&&pglDepthFunc&&pglClear&&
      pglVertex3f&&pglVertex3fv&&pglBegin&&pglEnd&&pglFrustum&&pglReadBuffer&&pglReadPixels&&pglPolygonMode&&pglLineWidth&&pglColor3f);
  return bCheckOK;
}

void APIENTRY hglBegin(GLenum mode){
  GLfloat curcolor[4];
  if(cvar.active&&!cvar.takingss&&(!cvar.antiss||!gMe.IsFreeSpectator())&&CheckFuncs()){
    if(cvar.wallhack==2){
      if(mode==GL_POLYGON){
        pglDisable(GL_DEPTH_TEST);
        pglEnable(GL_BLEND);
        pglBlendFunc(GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA_SATURATE);
        pglGetFloatv(GL_CURRENT_COLOR,curcolor);
        pglColor4f(curcolor[0],curcolor[1],curcolor[2],0.667f);
      }else
        if(mode==GL_TRIANGLES||mode==GL_TRIANGLE_STRIP||mode==GL_TRIANGLE_FAN){
          pglEnable(GL_DEPTH_TEST);
          pglDisable(GL_BLEND);
        }
    }
    if(mode!=GL_TRIANGLES&&mode!=GL_TRIANGLE_STRIP&&mode!=GL_TRIANGLE_FAN&&mode!=GL_QUADS){
      if(cvar.nightmode&&!gMe.zoom)
        pglTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_BLEND);
      if(cvar.whitewalls&&!gMe.zoom)
        pglTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
      if(cvar.fullbright&&bTex&&!gMe.zoom)
        pglDisable(GL_TEXTURE_2D);
    }else{
      if(cvar.nigger)
        pglTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_BLEND);
      if(cvar.lambert&&!cvar.glowshells&&mode==GL_TRIANGLE_STRIP)
        pglTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
    }
    switch((int)cvar.wireframe){
      case 1:
        if(mode==GL_POLYGON){
          pglPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          pglLineWidth(1.0f);
          pglColor3f(1.0f,1.0f,1.0f);
        }else
          pglPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      break;
      case 2:
        if(mode==GL_POLYGON){
          pglPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          pglLineWidth(2.0f);
          pglColor3f(1.0f,1.0f,1.0f);
        }else
          pglPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
			case 3:
        if(mode==GL_POLYGON){
          pglPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          pglLineWidth(4.0f);
          pglColor3f(1.0f,1.0f,1.0f);
        }else
          pglPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      break;
      default:break;
    }
    switch((int)cvar.wiremodels){
      case 1:
    		if(mode==GL_TRIANGLE_STRIP||mode==GL_TRIANGLE_FAN){
          pglPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          pglLineWidth(1.0f);
        }else if(mode!=GL_POLYGON)
          pglPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      break;
      case 2:
        if(mode==GL_TRIANGLE_STRIP||mode==GL_TRIANGLE_FAN){
          pglPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          pglLineWidth(3.0f);
        }else if(mode!=GL_POLYGON)
          pglPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      break;
			case 3:
        if(mode==GL_TRIANGLE_STRIP||mode==GL_TRIANGLE_FAN){
          pglPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
          pglLineWidth(5.0f);
        }else if(mode!=GL_POLYGON)
          pglPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      break;
      default:break;
    }
    if(mode==GL_QUADS){
      pglGetFloatv(GL_CURRENT_COLOR,curcolor);
      //fix laserbeam with no sky
      bSkyTex=!((curcolor[0]>0.0&&curcolor[1]==0.0&&curcolor[2]==0.0)||
                (curcolor[0]==0.0&&curcolor[1]>0.0&&curcolor[2]==0.0)||
                (curcolor[0]==0.0&&curcolor[1]==0.0&&curcolor[2]>0.0));
      //fix no smoke engine!
      bSmoke=(curcolor[0]==curcolor[1]&&curcolor[0]==curcolor[2]&&curcolor[0]!=0.0&&curcolor[0]!=1.0);
      //bFlash=(curcolor[0]>=1.0&&curcolor[1]>=1.0&&curcolor[2]>=1.0&&curcolor[3]>0.2);
    }else{
      bSkyTex=false;
      bSmoke=false;
    }
  }
  pglBegin(mode);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

void APIENTRY hglClear(GLbitfield mask){
  //don't clear cam view!
  if(cvar.active&&!cvar.takingss&&(!cvar.antiss||!gMe.IsFreeSpectator())&&
    (cvar.nosky||cvar.wallhack==2||cvar.wireframe)&&!drawingCam){
		if(mask&GL_DEPTH_BUFFER_BIT){
		  if(cvar.wireframe){
        if(pglClearColor)
          pglClearColor(0.1f,0.1f,0.1f,0.1f);
      }else{
        if(pglClearColor)
          pglClearColor(0.0f,0.0f,0.0f,0.0f);
      }
      mask|=GL_COLOR_BUFFER_BIT;
		}
	}
	pglClear(mask);
	//Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

void APIENTRY hglVertex3fv(const GLfloat *v){
  if(cvar.active&&!cvar.takingss&&(!cvar.antiss||!gMe.IsFreeSpectator())&&
     ((cvar.nosmoke&&bSmoke)||(bSkyTex&&(cvar.nosky||cvar.wallhack==2))))
    return;
  pglVertex3fv(v);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

/*void WINAPI hglVertex2f(GLfloat x,GLfloat y){
  if(cvar.active&&!cvar.takingss&&cvar.noflash&&bFlash&&x==0.0&&y==0.0)
    pglColor4f(1.0f,1.0f,1.0f,0.1f);
  pglVertex2f(x,y);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}*/

void APIENTRY hglEnable(GLenum mode){
  if(mode==GL_TEXTURE_2D)bTex=true;
  pglEnable(mode);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

void APIENTRY hglDisable(GLenum mode){
  if(mode==GL_TEXTURE_2D)bTex=false;
  pglDisable(mode);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

//Cam zoom
void APIENTRY hglFrustum(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble zNear,GLdouble zFar){
	if(cvar.active&&!cvar.takingss&&(!cvar.antiss||!gMe.IsFreeSpectator())&&
    drawingCam==1&&cvar.spycam==1){
		top=zNear*tan((50-cvar.camzoom*5)*M_PI/360);
		bottom=-top;
		left=bottom*4/3;
		right=top*4/3;
	}
  pglFrustum(left,right,bottom,top,zNear,zFar);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

//1.5 tint func!
void APIENTRY hglBlendFunc(GLenum sfactor,GLenum dfactor){
  if(cvar.active&&!cvar.takingss&&(!cvar.antiss||!gMe.IsFreeSpectator())&&
    cvar.hudhealth&&dfactor==GL_ONE&&gMe.iHealth){
    GLfloat iRed = 1.0f;
    GLfloat iGreen = 1.0f;
    GLfloat iBlue = 1.0f;
    if(gMe.iHealth >= 60){
      iRed = 0.0f;
      iGreen = 1.0f;
      iBlue = 0.0f;
    }else if((gMe.iHealth >= 20) && (gMe.iHealth <= 59)){
      iRed = 1.0f;
      iGreen = 1.0f;
      iBlue = 0.2f;
    }else if(gMe.iHealth <= 19){
      iRed = 1.0f;
      iGreen = 0.0f;
      iBlue = 0.0f;
    }
    pglColor3f(iRed,iGreen,iBlue);
  }
	if(oglSubtractive)
    pglBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	else
    pglBlendFunc(sfactor,dfactor);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

void APIENTRY hglColor4f(GLfloat red,GLfloat green,GLfloat blue,GLfloat alpha){
  if(cvar.active&&!cvar.takingss&&(!cvar.antiss||!gMe.IsFreeSpectator())&&oglChams){
    red=oglChamsColor[0];
    green=oglChamsColor[1];
    blue=oglChamsColor[2];
    alpha=1.0;
  }
  pglColor4f(red,green,blue,alpha);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

//SmallView
void APIENTRY hglViewport(GLint x,GLint y,GLsizei width,GLsizei height){
	bool bSmall=(cvar.active&&!cvar.takingss&&cvar.smallview&&gMe.alive&&
    cvar.speedmode&&gMe.inspeed&&gAutoRoute.runninginroute&&!drawingCam);
	pglViewport(
		(bSmall?(width-200)/2:x),
		(bSmall?(height-150)/2:y),
		(bSmall?200:width),
		(bSmall?150:height)
	);
	//Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

//UCP/SXE Screenshot
void APIENTRY hglReadPixels(GLint x,GLint	y,GLsizei	width,GLsizei	height,GLenum format,GLenum type,GLvoid *data){
  if(cvar.active&&cvar.antiss)
    gScreenShots.CopyScreenShot(width,height,format,(PBYTE)data);
  else
    pglReadPixels(x,y,width,height,format,type,data);
  //Update TIB Hook
  DoTIBHook(dwFSBase,dwFSBase2);
}

void APIENTRY glCreateTextureBuffer(GLint width,GLint height,GLvoid* data){
  static BOOL bInit=FALSE;
  if(!bInit){
    pglGenTextures(1,&textureID);
    bInit=TRUE;
  }
  if(pglBindTexture)
    pglBindTexture(GL_TEXTURE_2D,textureID);
  if(pglTexImage2D)
    pglTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_BGRA,GL_UNSIGNED_BYTE,data);
  if(pglTexParameteri){
    pglTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    pglTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
  }
}

void APIENTRY glDrawTexture(GLint x,GLint y,GLint width,GLint height){
  if(pglEnable)
    pglEnable(GL_TEXTURE_2D);
  if(pglBindTexture)
    pglBindTexture(GL_TEXTURE_2D,textureID);
  if(pglColor4f)
    pglColor4f(1.0f,1.0f,1.0f,0.1f);
  if(pglBegin)
    pglBegin(GL_QUADS);
  if(pglTexCoord2f&&pglVertex3f){
    pglTexCoord2f(1.0f,1.0f);
    pglVertex3f(x+width,y+height,1.0f);
    pglTexCoord2f(0.0f,1.0f);
    pglVertex3f(x,y+height,1.0f);
    pglTexCoord2f(0.0f,0.0f);
    pglVertex3f(x,y,1.0f);
    pglTexCoord2f(1.0f,0.0f);
    pglVertex3f(x+width,y,1.0f);
  }
  if(pglEnd)
    pglEnd();
  if(pglDisable)
    pglDisable(GL_TEXTURE_2D);
}

BOOL WINAPI HookOpenGl(){
  CONTEXT Context;LDT_ENTRY SelEntry;
  Context.ContextFlags=CONTEXT_FULL|CONTEXT_DEBUG_REGISTERS;
  DWORD pdwTlsOffset=0,pdwSetCltProcTable=0,pdwTlsIndex=0,dwTlsOffset=0,dwTlsIndex=0;BOOL bThisCall=FALSE;

  if((hOpengl32=GetModuleHandle("opengl32.dll"))==NULL){
    return FALSE;
  }

  if(!GetOffsets(hOpengl32,&pdwTlsOffset,&pdwSetCltProcTable,&pdwTlsIndex,&bThisCall))
    return FALSE;

  DWORD dwThreadId,dwProcessId;
  HWND hdHalfLife=FindWindow(NULL,"Counter-Strike");
  if(hdHalfLife){
    dwThreadId=GetWindowThreadProcessId(hdHalfLife,&dwProcessId);
  }

  HANDLE hThread=OpenThread(THREAD_GET_CONTEXT|THREAD_SUSPEND_RESUME|THREAD_QUERY_INFORMATION,FALSE,dwThreadId);
  if(!hThread){
    return FALSE;
  }

  if(!GetThreadContext(hThread,&Context)){
    CloseHandle(hThread);
    return FALSE;
  }

  GetThreadSelectorEntry(hThread,Context.SegFs,&SelEntry);
  dwFSBase=(PBYTE)((SelEntry.HighWord.Bits.BaseHi<<24)|
    (SelEntry.HighWord.Bits.BaseMid<<16)|SelEntry.BaseLow);
  if(!dwFSBase||IsBadReadPtr((PVOID)dwFSBase,4)){
    return FALSE;
  }

  dwTlsOffset=((DWORD)hOpengl32)+pdwTlsOffset;
  if(IsBadReadPtr((PVOID)dwTlsOffset,4)){
    return FALSE;
  }

  if(pdwTlsIndex){
    dwTlsIndex=((DWORD)hOpengl32)+pdwTlsIndex;
    if(IsBadReadPtr((PVOID)dwTlsIndex,4)){
      return FALSE;
    }
  }

  do{//multiple redirect...
    Sleep(100);
    if(dwTlsIndex&&(*(PDWORD)dwTlsIndex)>TLS_MINIMUM_AVAILABLE)
      dwFSBase2=(PBYTE)GetValueFromTeb((PTEB)dwFSBase,*((PDWORD)dwTlsIndex));
    else
      dwFSBase2=(PBYTE)(*(PDWORD)((DWORD)dwFSBase+(*(PDWORD)dwTlsOffset)));
  }while(dwFSBase2==NULL);

  //do Hook
  SuspendThread(hThread);
  DoTIBHook(dwFSBase,dwFSBase2);

  ResumeThread(hThread);
  CloseHandle(hThread);

  return TRUE;
}
