#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <sched.h>



void thread1()
{
	pid_t pid = getpid();
	int cnice = nice(0);
	printf("Nice: %d\n", cnice);

	for (int i = 0; i < 1000000; ++i)
	{
		if (i == 1)
		{
			cnice = nice(10);
		}
		printf("Nice: %d\n", cnice);
		printf("Child PID: %d\n", pid);
		sleep(1);
	}
}


void thread2()
{
	pid_t pid = getpid();
	int cnice = nice(0);
	for (int i = 0; i < 1000000; i++)
	{
		printf("Main nice: %d\n", cnice);
		printf("Main PID: %d\n", pid);
		sleep(1);
	}
}



int main()
{
	pid_t pid;
	switch (pid = fork())
	{
	case -1:
		perror("Fork() returned -1.");
		exit(-1);
	case 0:
		thread1();
		exit(0);
	default:
		thread2();
		wait(NULL);
	}

	exit(0);
}
