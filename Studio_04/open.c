#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#define bufferSize 1200
int main( int argc, char* argv[] )
{
char* filename = argv[1];
char buffer[ bufferSize ];
int fd = open(filename,O_RDONLY);

if(fd==-1)
{
perror("Error opening and reading file: ");
return(-1);
}
while(read(fd,buffer,sizeof(fd)-3)!=0)
{
printf(buffer);
}

close(fd);
return 0;
}

