#include <stdio.h>
#include <unistd.h>


int main( int argc, char* argv[] )
{
while(1)
{
	int buffer=1024;
	char message[buffer];
	int length = sizeof(message)/sizeof(message[0]);
	char  *input_string=fgets(message,length,stdin);
	if(input_string==NULL){
		break;
	}
	else{
		printf("Program 2 got: %s\n", input_string);
	}
}

}
