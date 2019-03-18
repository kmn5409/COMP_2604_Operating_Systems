#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int Golomb(int n) 
{  
    if (n == 1) 
        return 1;  
    return 1 + Golomb(n -  Golomb(Golomb(n - 1))); 
} 

void printGolomb(int n)
{
for (int i = 1; i <= n; i++)  
 printf("%d", Golomb(i)); 

}

int main(){
    pid_t id = fork();

    int n;
    scanf("%d" , &n);
    //change input to terminal
    while(n < 1){
        printf("Please enter a number greater than 0:\n");
        scanf("%d", &n);
    }
    //printf("%d" , n);
    if(id == 0){
	    printGolomb(int n);
    }else if(id > 0){
         //wait thing
        //parent
    }else{
	//error
	}
    printf("\n");
return 0;
}
