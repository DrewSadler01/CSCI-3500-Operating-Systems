#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

//Creating a simple server: Four main things:
//
//1. Create a socket with socket()
//
//2. Bind an address to the socket() (assign a port number)
//
//3. Set socket to listening mode with listen()
//   (This activates the socket, and others can try to connect.)
//
//4. Accept incoming connections with accept()


int main( int argc, char* argv[] ){

	if ( argc != 2 ){
		printf("Usage: ./server (port number)\n");
		return 0;
	}
	int portNum = atoi( argv[1] );

	//Step 1: Create a socket
	int sockFD = socket( AF_INET, SOCK_STREAM, 0 );
	if( sockFD == -1 ){
		perror("Could not create socket");
		return -1;
	}

	//Step 2: Bind port number to socket
	struct sockaddr_in address;
	//Initializes address structure to zero
	memset( &address, 0, sizeof( struct sockaddr_in ) );
	address.sin_family = AF_INET;
	address.sin_port = htons( portNum );
	address.sin_addr.s_addr = htonl(INADDR_ANY);

	int retVal = bind( sockFD,
			   (struct sockaddr*) &address,
			   sizeof(struct sockaddr_in));
	if( retVal == -1 ){
		perror("Could not bind socket");
		return -1;
	}

	//Step 3: Set the port to listening mode
	int listenFD = listen( sockFD, 1 );
	if( listenFD == -1 ){
		perror("Could not listen to socket");
		return -1;
	}

	//Step 4: Accept incoming client connections
	int clientFD = accept( sockFD, NULL, 0 );
	if( clientFD == -1 ){
		perror("Could not accept connection");
		return -1;
	}

	//Now we're at the point where we can read or write
	//from/to the clientFD

	char buffer[ 1024 ];
	//memset( buffer, 0, 1024 );
	//for( int i = 0; i < 256; i++ ){
	//	buffer[i] = i;
	//}
	
        int bytesRead = read( clientFD, buffer, 1024 );
        buffer[bytesRead] = '\0';
        /////////////////////////// edit
        char kill[] =  "quit";
	char cmd[] = "ls";
        int result = strncmp(buffer, kill, 4);
        ///////////////////////////
        //printf("I got '%s' from the client.\n", buffer );

        //FILE* sockStream = fdopen( clientFD, "r+");

        //fgets( buffer, 1024, sockStream );

        //printf("What I got '%s'  afterwards.\n", buffer );
       while(result !=0)
        {
                printf("Print: %s", buffer);
                clientFD = accept(sockFD, NULL,0);
                bytesRead = read(clientFD,buffer,1024);
                FILE *file;
    		file = fopen(buffer, "a");
   		if (file == NULL) {
			perror("Error");
    		} else {
     			 fclose(file);
    			 shutdown(sockFD, SHUT_RDWR);
		}

		buffer[bytesRead] = '\0';
                result= strncmp(buffer,kill,4);
       		result= strncmp(buffer,cmd, 4);
		FILE *f= popen( cmd, "r");
		fgets( cmd, *buffer, f);
		pclose(f);
       	}
       	printf("prints %s%n ",buffer);
       	printf("quit %s", kill);
	return  0;
}


