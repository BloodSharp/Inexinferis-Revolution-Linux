#ifndef _ANTISCREENSHOT_
#define _ANTISCREENSHOT_

#include "utils.h"
#include "jpeg/jpge.h"

//OpenGL Defs
#ifndef GL_RGB
#define GL_RGB      0x1907
#endif

#ifndef GL_RGBA
#define GL_RGBA     0x1908
#endif

#ifndef GL_BGR
#define GL_BGR      0x80E0
#endif

#ifndef GL_BGRA
#define GL_BGRA     0x80E1
#endif

#ifndef GL_PIXEL_PACK_BUFFER
#define GL_PIXEL_PACK_BUFFER              0x88EB
#endif

#ifndef GL_PIXEL_PACK_BUFFER_BINDING
#define GL_PIXEL_PACK_BUFFER_BINDING      0x88ED
#endif

#ifndef GL_READ_ONLY
#define GL_READ_ONLY 0x88B8
#endif

#ifndef GL_WRITE_ONLY
#define GL_WRITE_ONLY 0x88B9
#endif

#ifndef GL_STREAM_READ
#define GL_STREAM_READ 0x88E1
#endif

#pragma pack(push,1)

typedef struct PACKED _SSMSG{
  unsigned long uBuffSize;
  BITMAPINFO bmi;
  unsigned char  pBuffer[];
}SSMSG,*PSSMSG;

#pragma pack(pop)

class cScreenShots{
  public:
    cScreenShots(){
      hFile=hssth=hssee=0;
      pBuff32=0;
      pFlippedBuffer=0;
      bSkipDeath=false;
      bScreenTook=false;
      uiTakesCount=0;
    };
    ~cScreenShots();
    bool InitScreenShot(unsigned long dwWidth,unsigned long dwHeight);
    void TakeScreenShot();
    void TakeScreenShot2();
    void CopyScreenShot(unsigned int width,unsigned int height,unsigned int format,unsigned char* data);
    bool bSkipDeath,bScreenTook;
    unsigned int uiTakesCount;
  private:
    void SaveBitmap(PSSMSG pBuff,bool bIncludeBmp=false);
    bool SaveJPG(PSSMSG pBuff,char* filename,int quality);
    HANDLE hFile,hssth,hssee;
    unsigned long ssthid,bufSize;
    unsigned int sWidth,sHeight;
    PSSMSG pBuff32;
    unsigned char* pFlippedBuffer;
    //HWND hWnd;
  static unsigned long WINAPI ScreenShotsTH(LPvoid);
};

extern cScreenShots gScreenShots;

#endif //_ANTISCREENSHOT_
