#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(void)
{
    key_t key = 0x1234; //both programs use the same shared memory
    int shmid; //used to later store the shared memory number
    int *shared; //will later point to the memory both processes share
    pid_t pid;

    shmid = shmget(key, sizeof(int), 0666 | IPC_CREAT); //shared memory must be big enough to store one integer, that we can read/write to it
    if (shmid < 0) { 
        printf("Error: failed to create shared memory segment.\n"); 
        exit(1);  //if shared memory id less than zero its an error
    }

    shared = (int*)shmat(shmid, NULL, 0); //shared is a pointer to the shared memory that we can read/write the shared value
    if (shared == (void*)-1) {
        printf("Error: failed to attach shared memory.\n");
        exit(1); //if attach didnt work, print an error and exit to stop
    }

    *shared = 0; //shared number is currently 0

    pid = fork();
    if (pid < 0) { 
        printf("fork() has failed."); //if creating a child didnt work
        exit(1); }

    if (pid == 0) {
        execl("./Q4_P2_Process2_101302440_101303269", "Q4_P2_Process2_101302440_101303269", NULL);// first string is file path, second string is what the new program will think its own name
        printf("exec() has failed.");//because if exec() worked properly it never comes back
        exit(1);
    } else { //this part runs for the parent only
        printf("Process 1 [PID:%d]: incrementing shared counter\n", getpid());
        while (1) {
            (*shared)++;                // add 1 to the shared value
            int current = *shared;            // save the current shared value to a local variable to print 

            if (current % 3 == 0) { //if current value is a multiple of 3
                printf("[P1] %d is a multiple of 3\n", current);
            }

            if (current > 500) break; // stop condition

            sleep(2); //to slow down
        }

        wait(NULL); //wait for child to do something, will explain what in process2 code

        int value = shmdt(shared); //detach from shared memory
        if (value == -1){
            printf("Error: detachment unssucssuful");
        }

        int removeSharedMemory = shmctl(shmid, IPC_RMID, NULL);  // remove the shared memory
        if (removeSharedMemory == -1){
            printf("Error: Failed to remove shared memory");
        }

        printf("Process 1: cleaned shared memory, exiting.\n"); //confirms cleanup
        return 0; //parent terminates
    }
}