/* Program 1 */
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
    char *shm;
    /* create shared memory segment */
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0)
    {
        perror("shmget");
        exit(1);
    }
    /* attach shared memory segment */
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *)-1)
    {
        perror("shmat");
        exit(1);
    }
    /* write data to shared memory */
    sprintf(shm, "Hello from program 1!"); /* wait for program 2 to read data */
    sleep(5);                              /* detach shared memory segment */
    if (shmdt(shm) == -1)
    {
        perror("shmdt");
        exit(1);
    } /* destroy shared memory segment */
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl");
        exit(1);
    }
    return 0;
}
