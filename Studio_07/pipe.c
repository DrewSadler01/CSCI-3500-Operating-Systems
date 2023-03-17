#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
int pipefd[2];
pipe(pipefd);
int ret=fork();
if(ret==0)
{
	char* cmd="./output";
	char* myArgv[2];
	myArgv[0]=cmd;
	myArgv[1]=NULL;
	dup2(pipefd[1], STDOUT_FILENO);
	execvp(cmd, myArgv);
	return 0;
}
else if(ret==-1)
{
	perror("Error exec'ing print");
}
close(pipefd[1]);
int ret2=fork();
if(ret2==0)
{
        char* cmd="./input";
        char* myArgv[2];
        myArgv[0]=cmd;
        myArgv[1]=NULL;
        dup2(pipefd[0], STDIN_FILENO);
 	execvp(cmd, myArgv);
	return 0;
}
close(pipefd[1]);
if(ret2==-1)
{
        perror("Error exec'ing print");
}
waitpid(ret2,NULL,0);
}
