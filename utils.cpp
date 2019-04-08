#include <cstdio>
#include <dirent.h>
#include <sys/stat.h>

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

void CreateDirectory(char*szPath)
{
    mkdir(szPath,S_IRWXU //Me
                |S_IRGRP|S_IWGRP //GROUP_MAX
                |S_IROTH|S_IWOTH //Others
                );
}
