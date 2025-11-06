/**
 * @file Q2_P2_Process2_101302440_101303269.cpp
 * @author Omar Elhogaraty 101302440
 * @author Ahmad El-Jabi 101303269
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
    long counter=0;
    long cycles=0;
    printf("Process 2 [PID: %d]: Displaying multiples of 3 (decrementing)\n", getpid());
    while (1)
    {
        if (counter%3==0)
        {
            printf("Cycle number: %ld - (%ld) is a multiple of 3\n", cycles, counter);
        }
        else
        {
            printf("Cycle number: %ld\n", cycles);
        }
        counter--;
        cycles++;
        sleep(2); //change it to 1 if you feel like its a little too slow
    }
    return 0;
}