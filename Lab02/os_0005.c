#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	for (int i = 0; i < 1000; i++) 
	{
		printf("%d-%d\n", getpid(), i);
	}
	return 0;
}