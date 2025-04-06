#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>

void main()
{
    DIR *dir = opendir(".");
   struct dirent *dp = readdir(dir);
    while(dp!=NULL)
    {
        printf("%s\n", dp->d_name);
        dp = readdir(dir);
    }
}