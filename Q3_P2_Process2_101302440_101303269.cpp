#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    long counter=0;
    long cycles=0;
    printf("Process 2 [PID: %d]: Decrementing until counter is less than -500\n", getpid());
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
        sleep(1); //change it to 2 if you want to see it carefully, or comment out for instant answer
        if (counter<-500)
        {
            printf("Process 2 is now lower than -500. Exiting process now.\n");
            exit(0);
        }
    }
    return 0;
}
