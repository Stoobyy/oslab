#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void main()
{
    pid_t pid = fork();
    if(pid<0){
        printf("Error");
    }
    else if(pid == 0)
    {
        printf("Child\n");
        printf("Child Process is running for 5 seconds\n");
        sleep(5);

    }
    else{
        wait();
        printf("Parent\n");
    }
}