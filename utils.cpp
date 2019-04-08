#include <cstdio>
#include <dirent.h>

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

bool DirectoryExist(char*szPath)
{
    DIR*pDirectory = opendir(szPath);
    if(pDirectory)
    {
        closedir(pDirectory);
        return true;
    }
    return false;
}
