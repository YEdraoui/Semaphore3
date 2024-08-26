/* Program 2 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_KEY 12345
#define SHM_SIZE 1024
int main()
{
    int shmid;
    int key = SHM_KEY;
    char *shm; /* get shared memory segment */
    shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    } /* attach shared memory segment */
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }                                   /* read data from shared memory */
    printf("Received data: %s\n", shm); /* detach shared memory segment */
    if (shmdt(shm) == -1)
    {
        perror("shmdt");
        exit(1);
    }
    return 0;
}
