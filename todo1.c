#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 12345
#define SHM_SIZE sizeof(int)

int main() {
    int shmid;
    int *balance;

    // Create the shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment
    balance = (int *)shmat(shmid, NULL, 0);
    if (balance == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Initialize balance to $100
    *balance = 100;

    // Simulate a withdrawal
    if (*balance >= 50) {
        printf("Withdrawing $50 from the balance which is $%d...\n", *balance);
        sleep(1); // simulate time delay for reading and updating balance
        *balance -= 50;
        printf("Program 1 new balance: $%d\n", *balance);
    }

    // Detach from the shared memory segment
    if (shmdt(balance) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
