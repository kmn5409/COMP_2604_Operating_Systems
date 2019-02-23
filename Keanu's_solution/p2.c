#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char** argv[]){
    int child = fork();
    int x = 100;

    if(child == 0){//child
        x-=10;
        printf("child1: %d\n",x);
    }
    else{//parent
        child = fork();
        x-=20;
        printf("child2 & parent: %d\n",x);
        if(child){
            x-=10;
            printf("parent: %d\n",x);
        }
    }
    return 0;
}