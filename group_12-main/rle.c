#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

//GRADING NOTE: Compression output is mostly OK, but has trailing zeros which
// are not quite expected. For example, test case 1 with run length of 4 gives:
// 00000000: 0141 4141 4102 4242 4242 0343 4343 4304  .AAAA.BBBB.CCCC.
// 00000010: 4141 4141 0000 0001                      AAAA....
//Where the last four bytes 0000 0001 should not bee there.

// Decompression seems to be OK though.

// Test case 3 - a sequence of more than 255 repeated characters, fails for
// run length of 1. Your code gives 44A, where the output should be the
// binary equivalent of 255A45A.

//Score: 95/100

int main( int argc, char* argv[] ){

// Reading the command line arguments
	char* filename = argv[1];
        char* outputfile = argv[2];
        int compLength = atoi(argv[3]);
        int mode = atoi(argv[4]);




	if (argc > 5) {
       		perror("You have entered too many arguments");
       		exit(-1);
   	}
   	if (argc < 5) {
       		perror("You have entered too few arguments");
       		exit(-1);
   	}
   	if (atoi(argv[3]) < 1) {
       		perror("Compression length cannot be less than 1");
       		exit(-1);
   	}
   	if (atoi(argv[4]) != 0 && atoi(argv[4]) != 1) {
       		perror("Mode must be 0 or 1");
       		exit(-1);
   	}


//code for compression	
	if(mode == 0){
        	int FileInput = open(filename, O_RDONLY);
        	int FileOutput = open(outputfile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR| S_IWUSR);
        	char charPrev[compLength];
        	char charCur[compLength];
        	char int_str[5];
        	char count = 1;

        	if (FileInput == -1) {
            	perror("The input file cannot be opened");
            	exit(-1);
        	}

		if (FileOutput == -1) {
       			perror("Output file cannot be opened");
       			exit(-1);
   		}

        	int iterationCount = 0;
        	char counter_char[1];
        	strcpy(charPrev, charCur);
  	while (1) {
       		int readByte = read(FileInput, charCur, compLength);
        	  if (readByte == 0) {
        	   write(FileOutput, "\0", compLength);
                	  break;
   		    }

       		int results = strcmp(charPrev, charCur);
       		if (results == 0) {
           		count++;
       		}
       		else if(iterationCount > 0){
           		write(FileOutput, &count, sizeof(count));
           		write(FileOutput, charPrev, compLength);
           		count = 1;
           		iterationCount = 1;
       		}
       		else
          		iterationCount++;
  		strcpy(charPrev,charCur);
   }

}
//code for decomrpession
	else{
		char buffer[1024];
		int FileInput = open(filename, O_RDONLY);
        	int FileOutput = open(outputfile, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR| S_IWUSR);
		if (FileInput == -1) {
            	perror("The input file cannot be opened");
            	exit(-1);
        	}

        	if (FileOutput == -1) {
                	perror("Output file cannot be opened");
                	exit(-1);
        	}

		int returnVal = read(FileInput, buffer, 1);
        	int counter = buffer[0];
        	returnVal = read(FileInput, buffer, compLength);

                	while(1)
                	{
                        	if(returnVal == 0)
                        	{
                                	break;
                        	}

                        	for(int i=0; i<counter; i++)
                        	{	
                                	if(returnVal<compLength)
                                	{
                                        	write(FileOutput, buffer, 1);
                                	}

                                	else
                                	{
                                        	write(FileOutput, buffer, compLength);
                                	}
                        	}

                       	 	returnVal = read(FileInput, buffer, 1);
                        	counter = buffer[0];
                        	returnVal = read(FileInput, buffer, compLength);
                	}

	}
return 0;
}


