// Drew Sadler
// Date: 1/28/2022
// Program:Hello World!

// Include file goes here
#include<unistd.h>
int main( int argc, char* argv[] ){

//Make a call to fprintf() here
char buffer[] = "Hello, world!\n";
write(STDOUT_FILENO,buffer,15);

return 0;
}

