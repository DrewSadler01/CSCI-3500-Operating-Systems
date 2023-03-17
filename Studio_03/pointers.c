// Drew Sadler
// Date: 1/31/2022
// Program: Pointers

// Include file goes here

#include<stdio.h>
#include<string.h>
#include <stdlib.h>
void printReverse( char* string )
{
int b=0;
while(string[b]!='\0')
{
b++;
}
for(int a=b;a>=0; a--)
 {
 printf("%c\n",*(string + a));
 }
}
char* reverseString( char* input )
{
//1. First count how many characters are in the input string
int a=0;
int c=0;
while(input[c]!='\0')
{
c++;
}
int number_of_chars_in_input=c;
//This creates enough space to store the reversed string, plus one more byte
//for the null terminator
char* output = (char*)malloc( number_of_chars_in_input+1 );
//2. Copy the input string to the output string in reverse order. There are
//multiple ways to do this- consider using a counter, or consider using two
//pointers. 
for(int b=number_of_chars_in_input-1;b>=0;b--)
{
output[a++]=input[b];
}
//REMEMBER THAT YOUR OUTPUT STRING MUST END WITH A NULL TERMINATOR. This is not
//provided for you automatically- you must put it there!
output[a]='\0';
return output; 
}

int main( int argc, char* argv[] ){

char *secondString = "Another string!";
char *messagePtr = "HELLOWORLD!";
printf("%s\n", messagePtr);
for(int a=0;a<=(sizeof(messagePtr)+1);a++)
{
printf("%c\n", messagePtr[a]);
}
printf("%c\n", *messagePtr);
printf("%c\n",*(messagePtr + 1));
printf("%c\n",*(messagePtr + 2));

printf("\n");
for(int a=0;a<=(sizeof(messagePtr)+1);a++)
{
printf("%c\n",*(messagePtr + a));
}
printf("\n");

int counter=0;
while(messagePtr[counter]!='\0')
{
printf("%c\n",(messagePtr[counter]));
counter++;
}
printf("\n");

//printReverse(messagePtr);
printReverse(secondString);

char* reversedMessage = reverseString( messagePtr );
printf("Reversed string: %s\n", reversedMessage);
return 0;
}
