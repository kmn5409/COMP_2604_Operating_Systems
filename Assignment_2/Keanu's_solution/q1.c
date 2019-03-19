#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int size = 0;

void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 


int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than or 
        // equal to pivot 
        if (arr[j] <= pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void *quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

void *before(void *arr){
    printf("\nChild thread sorting\n");
    int arr1[size];
    int *val = (int *) arr;
    for(int i=0;i<size;i++)
        arr1[i] = val[i];
    /*
    printf("\nBefore:\n");
    for(int i=0;i<size;i++)
        printf("%d\n",arr[i]);
    */
    quickSort(arr1,0,size);
    //printf("\nHere\n%d\n",size);
}

//gcc -pthread q1.c 
//need to check over doesn't work with 1
int main(int argc, char* argv[]){
    //https://stackoverflow.com/questions/22003083/passing-array-as-argument-to-a-new-thread-in-c
    if(argc == 1){
        printf("Run with a number\n");
        return 0;
    }

    while(atoi(argv[1])<=0) //no number or negative number in input
    {
        printf("Enter a number more than 0.  ");
        fflush(stdout);
        fgets(argv[1], 30, stdin);
    }
    int n=atoi(argv[1]);

    //n+=1;
    int *arr = (int *)malloc((n-1)*sizeof(int));
    //int size = 1;

    pthread_t thread_id;

    time_t t;
    srand((unsigned) time(&t));

    for(int i=0;i<n;i++){
        arr[i] = rand()%1000;
        size++;
    }


    for(int i=0;i<n;i++)
        printf("%d\n",arr[i]);

    int e;
    e = pthread_create(&thread_id,NULL, &before, (void*)arr);
    e = pthread_join(thread_id,NULL);
    //printf("%d",size);
    //before(arr);
    printf("\nSorted:\n");

    quickSort(arr,0,n-1);
    for(int i=0;i<n;i++)
        printf("%d\n",arr[i]);
    return 0;
}

