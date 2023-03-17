#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define N 20000000
int race;
 pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

void* adder(void* args){
//	pthread_mutex_lock(&m);
        for(int a=0;a<N;a++){
//		pthread_mutex_lock(&m);
                race++;
//		pthread_mutex_unlock(&m);
        }
//	pthread_mutex_unlock(&m);
}
void* subtractor(void* args){
//	pthread_mutex_lock(&m);
        for(int a=0; a<N;a++){
//		pthread_mutex_lock(&m);
                race--;
//		pthread_mutex_unlock(&m);
        }
//	pthread_mutex_unlock(&m);
}


int main(int argc, char* argv[])
{
	time_t begin;
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
