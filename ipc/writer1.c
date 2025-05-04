#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

void main()
{
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, 1024, 0666|IPC_CREAT);
    int *data = (int *) shmat(shmid, (void *)0, 0);
    data[0] = 69420;
    shmdt(data);
}