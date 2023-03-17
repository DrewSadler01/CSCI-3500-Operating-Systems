#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <omp.h>

int main()
{
time_t begin;
int number;
omp_set_num_threads(5);
#pragma omp parallel for schedule( dynamic, 3)
for(int number=1;number<=25;number++)
{
	//omp_set_num_threads(5);
	if ( number <= 4 ) sleep(1);
	printf("Thread number:  %d\n", omp_get_thread_num());
	//printf("Thread number:  %d\n", omp_get_max_threads());
}
 begin=time(NULL);
 printf("Time elapsed is %d seconds.....  \n", (begin));
}

