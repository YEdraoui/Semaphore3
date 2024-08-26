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

    // Attach to the existing shared memory segment
    shmid = shmget(SHM_KEY, SHM_SIZE, 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }

    balance = (int *)shmat(shmid, NULL, 0);
    if (balance == (int *) -1) {
        perror("shmat");
        exit(1);
    }

    // Simulate another withdrawal
    if (*balance >= 50) {
        printf("Withdrawing $50 from the balance which is $%d...\n", *balance);
        sleep(1); // simulate time delay for reading and updating balance
        *balance -= 50;
        printf("Program 2 new balance: $%d\n", *balance);
    }

    // Detach from the shared memory segment
    if (shmdt(balance) == -1) {
        perror("shmdt");
        exit(1);
    }

    return 0;
}
