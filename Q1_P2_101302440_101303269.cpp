/**
 * @file Q1_P2_101302440_101303269.cpp
 * @author Omar Elhogaraty 101302440
 * @author Ahmad El-Jabi 101303269
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    pid_t pid;
    long counter=0;
    pid=fork();
    if (pid<0) 
    {
        perror("fork() has failed.");
        exit(1);
    }
    if (pid==0) 
    {
        printf("Process 2 started. PID = %d\n", getpid());
        while (1) 
        {
            printf("[Process 2 PID: %d] counter = %ld\n", getpid(), counter);
            counter++;
            sleep(2); //change it to 1 if you feel like its a little too slow
        }
    } 
    else 
    {
        printf("Process 1 started. PID = %d\n", getpid());
        while (1) 
        {
            printf("[Process 1 PID: %d] counter = %ld\n", getpid(), counter);
            counter++;
            sleep(2); //change it to 1 if you feel like its a little too slow
        }
    }
    return 0;
}
