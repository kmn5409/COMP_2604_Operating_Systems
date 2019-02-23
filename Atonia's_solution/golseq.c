#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int golumb(int n) //gets the nth value of the Golumb Sequence
{
   if (n==1)
return 1;
   return 1+ golumb( n-golumb(golumb(n-1)) );
}


void printGolumb(int n) //prints Golumb Sequence up to n
{
  printf("\nGenerating Golomb Sequence...\n");
    for(int i=1;i<=n;i++)
printf("%d ",golumb(i));
}

int main(void)
{
  pid_t id;
  //getting user input
  char x[30];
  printf("Enter a number that is more than 0.  ");
  fflush(stdout);
  fgets(x, 30, stdin);
 
  while(atoi(x)==0)
 {
  printf("Enter a number more than 0.  ");
  fflush(stdout);
  fgets(x, 30, stdin);
 }

  int num=atoi(x); 
  id=fork();
  int status;

  if(id==0) //print in child
printGolumb(num);
  else if(id>1)  //wait on child
  {
id=wait(&status);
printf("\nFinished."); //end of sequence
  }
  else printf("Fork failed.");  //fork failed

  return 0;
}