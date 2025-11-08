#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <semaphore.h>

union semun {
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};

int main(void)
{
    key_t shm_key = 0x1234;  // same shared memory key as Q4
    key_t sem_key = 0x5678;  // semaphore key 

    int shmid; //used to later store the shared memory number
    int *shared; // pointer to the shared integer value
    int semid;  

    pid_t pid;

    shmid = shmget(shm_key, sizeof(int), 0666 | IPC_CREAT); //shared memory must be big enough to store one integer, that we can read/write to it
    if (shmid < 0) { 
        printf("Error: failed to create shared memory.\n"); 
        exit(1); //if shared memory id less than zero its an error
    }

    shared = (int*)shmat(shmid, NULL, 0);  //shared is a pointer to the shared memory that we can read/write the shared value
    if (shared == (void*)-1) { 
        printf("Error: failed to attach shared memory.\n"); 
        exit(1); //if attach didnt work, print an error and exit to stop
    }

    *shared = 0; //shared number is currently 0

    semid = semget(sem_key, 1, 0666 | IPC_CREAT); //make a semaphore set with 1 semaphore (used as a mutex)
    if (semid < 0) { 
        printf("Error: failed to create semaphore.\n"); 
        exit(1); //if semaphore wasnt created successfully
    }

    union semun arg;
    arg.val = 1; //unlocked
    int set = semctl(semid, 0, SETVAL, arg);
    if (set == -1) {
        printf("Error: failed to set semaphore value.\n"); 
        exit(1); //if failed to set semaphore value
    }

    struct sembuf P = {0, -1, 0};  // lock
    struct sembuf V = {0,  1, 0};  // free key, unlock

    
    pid = fork();
    if (pid < 0) {
        printf("Error: fork() failed.\n");
        exit(1); //if creating a child didnt work
    }

    if (pid == 0) {
        // child becomes Process 2 (reader)
        execl("./Q5_P2_Process2_101302440_101303269", "Q5_P2_Process2_101302440_101303269", NULL); // first string is file path, second string is what the new program will think its own name
        printf("Error: exec() failed in child.\n"); //because if exec() worked properly it never comes back
        exit(1);
    }

    printf("Process 1 [PID:%d]: protected increment using semaphore\n", getpid());
    while (1) { //this part runs for the parent only
        if (semop(semid, &P, 1) == -1) { //try locking the shared memory
            printf("Error: semop P failed.\n"); 
            break; //if lock failed
        } 

        //lock successful, then this is the critical section
        (*shared)++;
        int current = *shared;

        if (semop(semid, &V, 1) == -1) { //try to unlock v
            printf("Error: semop V failed.\n"); 
            break; //if unlocking failed
        }

        // lock freed
        if (current % 3 == 0) {
            printf("[P1] %d is a multiple of 3\n", current);
        }

        if (current > 500) break;

        sleep(2); // slow down 
    }

    wait(NULL); //wait for child to finish

    int value = shmdt(shared); //detach from shared memory
    if (value == -1){
        printf("Error: detachment unssucssuful");
    }

    int removeSharedMemory = shmctl(shmid, IPC_RMID, NULL);  // remove the shared memory
    if (removeSharedMemory == -1){
        printf("Error: Failed to remove shared memory");
    }

    int remove_semaphore = semctl(semid, 0, IPC_RMID); //remove semaphore
    if (remove_semaphore == -1){
        printf("Error: removing semaphore failed.\n");
    }
    printf("Process 1: cleaned shared memory and removed semaphore, exiting.\n"); //confirms cleanup
    return 0; //parent terminates
}
