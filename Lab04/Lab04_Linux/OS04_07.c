#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>



void* ChildThread_T1(void* arg)
{
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
	for (int i = 1; i <= 75; ++i)
	{
		printf("%d. PID = %d, Thread1 ID = %d\n", i, pid, tid);
		sleep(1);
	}
	pthread_exit("Child thread");
}



int main()
{
	pid_t pid = getpid();
	pid_t tid = syscall(SYS_gettid);
	pthread_t a_thread;
	void* thread_result;
	int res = pthread_create(&a_thread, NULL, ChildThread_T1, NULL);

	for (int i = 1; i <= 100; ++i)
	{
		printf("%d. PID = %d, Thread main ID = %d\n", i, pid, tid);
		sleep(1);
	}

	int status = pthread_join(a_thread, (void**)&thread_result);
	exit(0);
}

//ps -eLf