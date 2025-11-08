/**
 * @file Q2_P2_Process1_101302440_101303269.cpp
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
    long cycles=0;
    pid=fork();
    if (pid<0)
    {
        printf("fork() has failed.");
        exit(1);
    }
    if (pid==0) //then thats the child process
    {
        execl("./Q2_P2_Process2_101302440_101303269", "Q2_P2_Process2_101302440_101303269", NULL);// first string is file path, second string is what the new program will think its own name
        printf("exec() has failed."); //because if exec() worked properly it never comes back
        exit(1);
    }
    else
    {
        printf("Process 1 [PID: %d]: Displaying multiples of 3 (incrementing)\n", getpid());
        while (1) //counts up forever
        {
            if (counter%3==0)
            {
                printf("Cycle number: %ld - %ld is a multiple of 3\n", cycles, counter); //if the current number is a multiple of 3, print this number
            }
            else
            {
                printf("Cycle number: %ld\n", cycles); //prints how many loops happened 
            }
            counter++; //because parent process counting upwards
            cycles++;
            sleep(2); //change it to 1 if you feel like its a little too slow
        }
    }
    return 0;
}