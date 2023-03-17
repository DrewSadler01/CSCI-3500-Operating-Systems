//This program sleeps forever in an infinite loop
//September 10th, 2016
//David Ferry

#include <unistd.h> //For sleep() and getpid()
#include <stdio.h> //For printf()

int main ( int argc, char* argv[] ){

	const int length_of_sleep = 1;
	int i = 0;

	printf("Sleeper's PID is: %d\n", getpid() );

	while( 1 ){
		printf("Slept for %d iterations!\n", i);
		i++;
		sleep( length_of_sleep );
	}

	printf("This statement should never execute.\n");

	return 0;
}

