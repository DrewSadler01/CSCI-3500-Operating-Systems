#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

//Creating a simple client: Two steps
//
// 1. Create a socket with socket()
//
// 2. Connect to a remote peer with connect()


int main( int argc, char* argv[] ){

        if ( argc != 3 ){
                printf("Usage: ./client (ip address) (port number)\n");
                return 0;
        }
	char* ipAddr = argv[1];
        int portNum = atoi( argv[2] );

	//Step 1: Create a socket
        int sockFD = socket( AF_INET, SOCK_STREAM, 0 );
        if( sockFD == -1 ){
                perror("Could not create socket");
                return -1;
        }

	//Step 2: Connect to a remote peer
        struct sockaddr_in address;
        //Initializes address structure to zero
        memset( &address, 0, sizeof( struct sockaddr_in ) );
        address.sin_family = AF_INET;
        address.sin_port = htons( portNum );
	address.sin_addr.s_addr = htonl(INADDR_ANY);
	
	//int retVal = inet_aton( ipAddr, &(address.sin_addr) );
	//if( retVal == 0 ){
	//	printf("Error: IP address not valid\n");
	//	return -1;
	//}

	int retVal = connect( sockFD, (struct sockaddr*) &address, sizeof(struct sockaddr_in));
	if( retVal == -1 ){
		perror("Could not connect to server");
		return -1;
	}

	//Now we're at the point where we can read/write to sockFD
	
	//write( sockFD, "Hello from the client.", 22 );
	
	//FILE* sockStream = fdopen( sockFD, "r+" );

	//fprintf( sockStream, "Hello this is a test to the server\n" );

	char msg[1024];
	printf("what is you message: ");
	fgets(msg, 1024, stdin);
	int bytRD =0;
//	for(int a=0;a=99999;a++){
	while(msg[bytRD] != 0){
		bytRD++;
	}
//	}
	while(read(sockFD,msg,bytRD) != 0){
	return 0;
	}
	write(sockFD,msg,bytRD);
	return 0;
}

