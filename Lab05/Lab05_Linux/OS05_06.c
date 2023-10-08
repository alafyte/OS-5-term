#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>


int main()
{
    pid_t pid = getpid();
    pid_t tid = gettid();

    for (int i = 0; i < 1000000; ++i)
    {
        printf("PID:  %d\nTID:  %d\n\n", pid, tid);
        sleep(1);
    }
}