#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sched.h>


int main()
{
	pid_t pid = getpid();
	printf("OS08_07 PID = %d\n", pid);

	void* memr = malloc(1024 * 1024 * 256);
	printf("memr(1024 * 1024) = %p\n", memr);

	sleep(40);
	exit(0);
}