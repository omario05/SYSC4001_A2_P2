#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//this is the program of the child process right now, which got replaced by the original duplicate of the parent's program
int main(void)
int main(void)
{
    long counter=0;
    long cycles=0;
    printf("Process 2 [PID: %d]: Decrementing until counter is less than -500\n", getpid()); //the child process's program keeps counting down till its -500
    while (1) //keep counting forever, until we break by calling exit(0) when (count < -500)
    {
        if (counter%3==0)
        {
            printf("Cycle number: %ld - (%ld) is a multiple of 3\n", cycles, counter); //prints the negative numbers that are divisible by 3
        }
        else
        {
            printf("Cycle number: %ld\n", cycles); //prints which loop we are on now
        }
        counter--; //child process counts down 
        cycles++;
        sleep(1); //change it to 2 if you want to see it carefully, or comment out for instant answer
        if (counter<-500) //so the child process exits if it counted more than 500 times
        {
            printf("Process 2 is now lower than -500. Exiting process now.\n");
            exit(0); //process 2 (child) is done, now exit
        }
    }
    return 0;
}
