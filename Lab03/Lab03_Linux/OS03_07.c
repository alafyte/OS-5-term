#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main()
{
	char* const argv[] = { "ps", "-ef", 0 };
	
	execv("./OS03_05_1", argv);
	
	for (int i = 1; i <= 100; ++i)
	{
		printf("PID = %d [OS03_07]: %d\n", getpid(), i);
		sleep(1);
	}
	exit(0);
}