#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <semaphore.h>

int main(void)
{
    key_t shm_key = 0x1234;  // same as parent
    key_t sem_key = 0x5678;  // same semaphore key as parent

    int shmid = shmget(shm_key, sizeof(int), 0666); // get existing shared memory
    if (shmid < 0) { 
        printf("Error: failed to get existing shared memory.\n"); 
        exit(1); 
    }

    int *shared = (int*)shmat(shmid, NULL, 0);      // attach to shared memory
    if (shared == (void*)-1) { 
        printf("Error: failed to attach shared memory.\n"); 
        exit(1); 
    }

    int semid = semget(sem_key, 1, 0666);           // get existing semaphore
    if (semid < 0) { 
        printf("Error: failed to get semaphore.\n"); 
        exit(1); 
    }

    struct sembuf P = {0, -1, 0}; //same as parent
    struct sembuf V = {0,  1, 0}; //same as parent

    printf("Process 2 [PID:%d]: attached to shared memory, using semaphore to read safely\n", getpid());

    while (1) { //stops when shared memory value bigger than 500
        int value; //storing in the value to be read
        int lock = semop(semid, &P, 1);
        if (lock == -1) { //lock semaphore
            printf("Error: semop P failed in child.\n"); //if locking failed
            break; 
        }

        // if semaphore lockedd successfuly, then it continues from her and then this becomes the critical section 
        value = *shared; //read the current value of the shared memory

        int unlock = semop(semid, &V, 1);
        if (unlock == -1) { //after reading, unlock semaphore 
            printf("Error: semop V failed in child.\n"); //if unlocking failed
            break; 
        }


        if (value > 100 && (value % 3 == 0)) {
            printf("[P2] %d is a multiple of 3 (read under lock)\n", value); //starts checking if current value is a multiple of 3 only when its more than a 100
        }

        if (value > 500) { //stops when current value more than 500
            printf("Process 2: value passed 500, stopping.\n");
            break;
        }

        sleep(2); //to slow down
    }

    int detach = shmdt(shared);
    if (detach == -1) { //detach from shared memory ONLY
        printf("Error: detaching shared memory failed failed in child.\n"); //if detaching unsuccessful
    }
    printf("Process 2: exiting.\n");
    return 0;
}
