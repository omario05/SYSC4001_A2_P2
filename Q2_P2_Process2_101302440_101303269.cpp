/**
 * @file Q2_P2_Process2_101302440_101303269.cpp
 * @author Omar Elhogaraty 101302440
 * @author Ahmad El-Jabi 101303269
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

//this is the program of the child process right now, which got replaced by the original duplicate of the parent's program
int main(void)
{
    long counter=0;
    long cycles=0;
    printf("Process 2 [PID: %d]: Displaying multiples of 3 (decrementing)\n", getpid()); //to declare its process 2 right now (child)
    while (1)
    {
        if (counter%3==0)
        {
            printf("Cycle number: %ld - (%ld) is a multiple of 3\n", cycles, counter); // prints both the cycle number and counter (when counter is a multiple of 3)
        }
        else
        {
            printf("Cycle number: %ld\n", cycles); //prints how many loops happened
        }
        counter--; //because this time counting downwards, to print in the next loop negative numbers that are a multiple of 3
        cycles++;
        sleep(2); //change it to 1 if you feel like its a little too slow
    }
    return 0;
}