#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#define N 20000000
int race;

void* adder(void* args){
	for(int a=0;a<N;a++){
		race++;
	}
}
void* subtractor(void* args){
	for(int a=0; a<N;a++){
		race--;
	}
}


int main(int argc, char* argv[])
{
	time_t begin;
        //begin = time(NULL);
	pthread_t tid, tid2;
	pthread_create(&tid,NULL,adder,NULL);
	pthread_create(&tid2,NULL,subtractor,NULL);
	void* retval;
	pthread_join(tid,&retval);
	pthread_join(tid2,&retval);
	printf("final value is: %d\n", race);
	//time_t end = time(NULL);
	begin = time(NULL);
	printf("Time elapsed is %d seconds \n", (begin));
	return 0;

}
