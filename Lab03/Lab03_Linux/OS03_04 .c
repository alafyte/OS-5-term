#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	for (int i = 1; i < 1000; i++)
	{
		sleep(1);
		printf("%d-%d \n", getpid(), i);
	}
	exit(0);
}