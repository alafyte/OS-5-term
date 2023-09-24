#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


void cycle(int counter, char* message)
{
    for (int i = 1; i <= counter; ++i)
    {
        printf("PID = %d [%s]: %d\n", getpid(), message, i);
        sleep(2);
    }
}


int main()
{

    pid_t pid;
    switch (pid = fork())
    {
    case -1: perror("Fork() returned -1");
             exit(-1);
    case  0: cycle(50, "OS03_05_1");
             exit(0);
    default: cycle(100, "OS03_05");
             wait(0);
    }
    exit(0);
}