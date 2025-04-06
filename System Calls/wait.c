#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Error occurred
        fprintf(stderr, "Fork failed\n");
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process: PID = %d\n", getpid());
        sleep(2); // Child does some work
        printf("Child process exiting\n");
        exit(0);
    } else {
        // Parent process
        printf("Parent process: PID = %d\n", getpid());
        printf("Parent waiting for child (PID = %d) to terminate...\n", pid);
        
        // Parent waits for child to terminate
        wait(NULL);
        
        
        printf("Parent process exiting\n");
    }

    return 0;
}