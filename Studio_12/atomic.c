/*
#include <stdio.h>
#include <unistd.h>

int main()
{
int* ptr = 0;
printf("%d\n",ptr);
__sync_add_and_fetch(&ptr,10);
printf("%d\n",ptr);
}
*/
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 20000000
int* race=0;
 pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* adder(void* args){
//	pthread_mutex_lock(&m);
        for(int a=0;a<N;a++){
		pthread_mutex_lock(&m);
                __sync_add_and_fetch(&race,1);
		pthread_mutex_unlock(&m);
        }
//	pthread_mutex_unlock(&m);
}
void* subtractor(void* args){
//	pthread_mutex_lock(&m);
        for(int a=0; a<N;a++){
		pthread_mutex_lock(&m);
                __sync_sub_and_fetch(&race,1);
		pthread_mutex_unlock(&m);
        }
//	pthread_mutex_unlock(&m);
}


int main(int argc, char* argv[])
{
	time_t begin;
	printf("starting value is %d\n", race);
//	pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;///
        pthread_t tid, tid2;
        pthread_create(&tid,NULL,adder,&m);
        pthread_create(&tid2,NULL,subtractor,&m);
        void* retval;
        pthread_join(tid,&retval);
        pthread_join(tid2,&retval);
        printf("final value is: %d\n", race);
	begin=time(NULL);
	printf("Time elapsed is %d seconds \n", (begin));
       	return 0;

}

