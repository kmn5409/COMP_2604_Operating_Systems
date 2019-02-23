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

int main(int argc, char* argv[])
{
  pid_t id;
 
  while(atoi(argv[1])<=0)
 {
  printf("Enter a number more than 0.  ");
  fflush(stdout);
  fgets(argv[1], 30, stdin);
 }

  int num=atoi(argv[1]); 
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
