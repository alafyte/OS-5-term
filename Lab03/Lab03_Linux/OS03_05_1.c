#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	for (int i = 1; i <= 50; ++i)
	{
		printf("PID = %d [OS03_05_1]: %d\n", getpid(), i);
		sleep(1);
	}
	exit(0);
}