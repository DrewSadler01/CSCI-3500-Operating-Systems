#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

int Program1( int argc, char* argv[] ){

//Make a call to fprintf() here
fprintf(stdout,"Hello, world!\n");

return 0;
}

Int Program2(int argc, char* argv[] ))
{
        char words[100];
        //Infinite loop
        while(true){
        
                fgets(words, 100, stdin);
                if(input[0] == '\n' && input[1] == '\0'){
                    break;
                }
                printf("You typed: %s\n",input);
        }
        return 0;
}

