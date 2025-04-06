#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main()
{
    char *args[] = {"./prog2", NULL};
    execvp(args[0], args);
    printf("execvp failed\n");
}