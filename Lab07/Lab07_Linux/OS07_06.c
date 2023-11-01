#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> 

int main()
{
    struct timespec beg, start, end;
    clock_gettime(CLOCK_REALTIME, &start);
	
    for (int i = 0; ; i++ )
	{
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &beg);
        if (beg.tv_sec == 2)
        {
            printf("second: %ld, i = %d\n", beg.tv_sec, i);
            break;
        }
    }
    clock_gettime(CLOCK_REALTIME, &end);
    printf("real time: seconds: %ld, nanoseconds: %ld\n", end.tv_sec - start.tv_sec, end.tv_nsec);
}