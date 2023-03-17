// Drew Sadler
// Date: 2/1/2022
// Program:Studio
//
//while(read(STDIN_FILENO, buffer, sizeof(buffer))!
// Include file goes here
#include<unistd.h>
#include <stdio.h>
#define bufferSize 900
int main( int argc, char* argv[] )
{
//Make a call to fprintf() here
char buffer[ bufferSize ];
char pattern[ bufferSize ];

int runLength = 3;

//Read in the first pattern
int bytesRead = read(STDIN_FILENO,pattern,runLength);
char counter = 1;

while( 1 )
{
        int bytesRead = read(STDIN_FILENO,buffer,runLength);
        if( bytesRead == 0 )
	{	
		break;
	}
        //Here we can permute the output
        if(pattern==buffer)
	{       
		//Pattern is equal to buffer in the first runLength bytes ){
                counter++;
        }
	else
	{
                write(STDOUT_FILENO,&counter, 1);
                write(STDOUT_FILENO,buffer, bytesRead);
        }
}

//}
return 0;
}

