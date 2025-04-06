#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void main()
{
    int f1 = open("test.c", O_RDONLY);
    printf("File descriptor: %d\n", f1);
    close(f1);
}