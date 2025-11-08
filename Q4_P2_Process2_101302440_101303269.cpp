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

    shmid = shmget(key, sizeof(int), 0666); // memory already exits already created by parent
    if (shmid < 0)
    {
        printf("Error: failed to get existing shared memory.\n");
        exit(1);
    }

    shared = (int*)shmat(shmid, NULL, 0); // attach the shared memory so the child can read from it
    if (shared == (void*)-1) //if attaching did not work
    {
        printf("Error: failed to attach shared memory.\n"); 
        exit(1);
    }

    while (1) //keeps reading the share memory value until its more than 500
    {
        int current_value = *shared; // read the shared value that parent writes

        if (current_value > 100 && (current_value % 3 == 0)) //starts checking if current value is a multiple of 3 only when its more than a 100
        {
            printf("[P2] %d is a multiple of 3 (read from shared memory)\n", current_value);
        }

        if (current_value > 500) //stop when parents went beyond the shared memory value 500
        {
            printf("Process 2: value passed 500, stopping now.\n");
            break;
        }
        sleep(2); //to slow down
    }

    int value = shmdt(shared); //detach from shared memory
    if (value == -1){
        printf("Error: detachment unssucssuful");
    }

    printf("Process 2: cleaned shared memory, exiting.\n"); //confirms cleanup
    return 0; //child terminates
}
