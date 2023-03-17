#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
int prime(int number)
{
int i;
if(number==2){
        return 1;
}
else if(number==1)
{
        return 0;
}
if(number%2==0)
        {
                return 0;
                exit(0);
        }
//#pragma omp parallel for
for (i=3;i*i<=number;i+=2){
        if(number%i==0){
                return 0;
                break;
        }
//      else
//      {
//              return 1;
//      }
}
return 1;
}


int main()
{
time_t begin;
int number;
//int marker;
//printf("Enter a number: ");
//scanf("%d", &number);
#pragma omp parallel for
for(int number=1;number<=20000000;number++)
{
if(prime(number)==1)
        {
               // printf("Number is prime: %d\n", number);
               // begin=time(NULL);
               // printf("Time elapsed is %d seconds 1......  \n", (begin));
        }
  //      else{
  //              printf("Number isn't prime: %d\n", number);
                //begin=time(NULL);
               // printf("Time elapsed is %d seconds \n", (begin));
  //      }
       // begin=time(NULL);
       // printf("Time elapsed is %d seconds 2.....  \n", (begin));
}
  begin=time(NULL);
  printf("Time elapsed is %d seconds 2.....  \n", (begin));
}
