#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct thread_args{
	int arg1;
	int arg2;
	int ret;
	char buffer[100];
};

struct prntmsg{
	int val;
};
void* newstruct(void* args){
	struct prntmsg* argptr=args;
	printf("This is thread: %i\n", argptr->val);
	return NULL;
}

void* thread_entry(void * args){
	printf("Thread is doing something\n");
	struct thread_args* argptr = args;

	printf("Value of arg1 is %d\n", (*argptr).arg1);
	printf("Value of arg2 is %d\n", (*argptr).arg2);
	printf("Value of ret is %d\n", (*argptr).ret);
	printf("The message was: '%s'\n", argptr->buffer);
	return NULL;
}

int main(int argc, char* argv[])
{

struct thread_args arguments;
arguments.arg1=50;
arguments.arg2=314;
arguments.ret=200;
snprintf( arguments.buffer, 100, "hello");

pthread_t tid;
pthread_create(&tid,NULL,thread_entry , &arguments);
pthread_join(tid,NULL);

struct prntmsg NStruct;
struct prntmsg NstructArray[6];
pthread_t tids[6];
for(int a=0; a<6; a++)
{
	NstructArray[a].val=a;
	pthread_create(&tids[a],NULL,newstruct,&NstructArray[a]);
}

for(int b=0; b<6; b++)
{
	pthread_join(tids[b], NULL);
}

return 0;
}
