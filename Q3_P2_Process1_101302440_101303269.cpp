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
        execl("./Q3_P2_Process2_101302440_101303269", "Q3_P2_Process2_101302440_101303269", NULL);// first string is file path, second string is what the new program will think its own name
        printf("exec() has failed.");//because if exec() worked properly it never comes back
        exit(1);
    }
    else //its the parent process and it stays in that program
    {
        printf("Process 1 [PID: %d]: Displaying multiples of 3 (incrementing)\n", getpid());
        printf("Process 1 waiting for Process 2 to finish, please wait.\n"); //because the parent process says wait(NULL)
        wait(NULL);
        printf("Process 2 is finished, Process 1 exiting now.\n"); //child is done, program continues here, shows that parent process's prorgam is back but exiting
        return 0; //p1 (parents) exits because child finished
    }
}
