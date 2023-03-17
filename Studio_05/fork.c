#include<stdio.h>
#include<unistd.h>
#include <sys/types.h> 
#include <sys/wait.h> 

int main(void)
{
//fork();
char* child_argv[] = {"ls", "-l", NULL};
char* child_prog = child_argv[0];
int pidmsg=getpid();
int parent_PID;
int child_PID;
if(fork()==0)
{
printf("Child is: ");
sleep(3);
child_PID=pidmsg;
execvp( child_prog, child_argv );
printf("pid:%d\n ", child_PID);
}
else
{
printf("Parent is: ");
parent_PID=pidmsg+2;
waitpid( child_PID, NULL, 0 );
printf("pid:%d\n ", parent_PID);
}

return 0;
}
