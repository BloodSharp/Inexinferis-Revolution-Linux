#include <cstdio>

bool FileExists(char*szPath)
{
    bool bReturn=false;
    FILE*pFile=fopen(szPath,"r");
    if(pFile)
    {
        fclose(pFile);
        bReturn=true;
    }
    return bReturn;
}
