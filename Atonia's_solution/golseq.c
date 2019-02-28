
/*
The user will first enter a value into the command line. If it is not a positive number for example in these cases of entering a
negative number, 0 or a string, it will ask the user to re-enter a number. The positive value will then be converted to an
int and a fork will be generated. A conditonal statement will then occur whereby the process id is checked, if it is equal to 0
the printGolumb function is called. This function then iterates through a loop that uses the Golomb function  (which is recursive in nature)
that generates the nth Golomb number passed as a value. If the pid is more than 0 the parent process the process waits for the child process to finish,
then prints "Finished". If the pid is negative the program prints "Fork Failed" and the program then finishes.
*/

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int Golomb(int n) //gets the nth value of the Golumb Sequence
{
    if (n==1)
        return 1;
    return 1+ Golomb( n-Golomb(Golomb(n-1)) );
}


void printGolomb(int n) //prints Golumb Sequence up to n
{
    printf("\nGenerating Golomb Sequence...\n");
    for(int i=1;i<=n;i++)
        printf("%d ",Golomb(i));
}

int main(int argc, char* argv[])
{
    pid_t id;

    while(atoi(argv[1])<=0) //no number or negative number in input
    {
        printf("Enter a number more than 0.  ");
        fflush(stdout);
        fgets(argv[1], 30, stdin);
    }

    int num=atoi(argv[1]);
    id=fork();
    int status;

    if(id==0) //print in child
        printGolomb(num);
    
    else if(id>0)  //wait on child
    {
        id=wait(&status);
        printf("\nFinished."); //end of sequence
    }
    
    else printf("Fork failed.");  //fork failed

    return 0;
}
