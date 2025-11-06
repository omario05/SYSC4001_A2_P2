#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
    if (pid==0)
    {
        execl("./Q3_P2_Process2_101302440_101303269", "Q3_P2_Process2_101302440_101303269", NULL);
        printf("exec() has failed.");
        exit(1);
    }
    else
    {
        printf("Process 1 [PID: %d]: Displaying multiples of 3 (incrementing)\n", getpid());
        printf("Process 1 waiting for Process 2 to finish, please wait.\n");
        wait(NULL);
        printf("Process 2 is finished, Process 1 exiting now.\n");
        return 0;
    }
}
