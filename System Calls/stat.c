#include <stdio.h>
#include <sys/stat.h>

void main() {
    struct stat fileStat;
    stat("test.c", &fileStat);
    printf("File Size: %ld bytes\n", fileStat.st_size);

}
