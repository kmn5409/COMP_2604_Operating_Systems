#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int Golomb(int n){
    if(n == 1)
        return 1;
    return (1 + Golomb(n - Golomb(Golomb(n - 1))) );
}

void PrintGolomb(int n){
    for(int i=1; i<=n; i++){
        printf("%d ",Golomb(i));
    }
    //printf("%d ",Golomb(n));
    //printf("\n");

}

int main(int argc, char* argv[]){
    if(argc > 1){
        if(*argv[1] == '-' || *argv[1] == '0')
            printf("Must be positive\n");
        else if(*argv[1] > '9' || *argv[1] < '0')
            printf("Not a number\n");
        else{
            int num = atoi(argv[1]);
            int status;
            pid_t pid;
            printf("Number: %d\n",num);
            printf("Answer: ");
            fflush(stdout);
            pid = fork();
            if(pid > 0){
                pid = wait(&status);
                //PrintGolomb(num);
            }
            else{
                PrintGolomb(num);
            }
            //printf("")
        }
    }
    else    
        printf("Nothing was input\n");
    return 0;
}
