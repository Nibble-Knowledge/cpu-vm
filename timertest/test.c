#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	struct timespec tm;
	struct timespec tm1;
	struct timespec tm2;
	long loopamount = 1;	
	long i = 0;
	
	if(argc >= 2)
	{
		loopamount = atol(argv[1]);
	}
	
	for(i = 0; i < loopamount; i++)
	{
		tm1.tv_sec = 0;
		tm1.tv_nsec = 0;
		tm2.tv_sec = 0;
		tm2.tv_nsec = 0;
		/* clock_settime(CLOCK_REALTIME, &tm); */
		clock_gettime(CLOCK_MONOTONIC, &tm1);
		clock_gettime(CLOCK_MONOTONIC, &tm2);
	
		printf("time for 2 gettime calls: %li\n", (tm2.tv_nsec - tm1.tv_nsec));
	}

	return 0;
}
