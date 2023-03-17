#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>


int main( int argc, char* argv[] )
{
int max_args = 15;
int max_argv_size = max_args + 2; //one for argv[0], one for null terminator
char* cmd;
char* my_argv[max_argv_size];

int compLength=1024;
char message[compLength];
printf("enter in something : ");
int length = sizeof(message)/sizeof(message[0]);
char  *input_string=fgets(message,length,stdin);
printf("%s\n", input_string);

char *token;
token=strtok(input_string," ");
cmd=token;
printf("%s\n",token);
printf("\n");
int i=1;
my_argv[0]=cmd;
while(token!=NULL)
{
//argv[i]///not done
printf("%s\n",token);
token=strtok(NULL, " \n");
my_argv[i]=token;
i++;
}
my_argv[i]=NULL;
execvp( cmd, my_argv );
}

