/*
	This program sorts an array of n (given in command line) random numbers in a child thread.  The parent thread waits on the child
	and the sorted array is printed to the screen.
	To run: gcc -pthread q1.c
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> 

//global variable denoting size of array
int size=-1;

//quick sort functions
int partition (int lo, int hi, int arr[])
{
    int pivot=arr[lo];
    lo--; hi++;

    while(lo<hi)
    {
	hi--;lo++;
	while(arr[lo]<pivot)
		lo++;
	while (arr[hi]>pivot)
		hi--;

	if (lo<hi)
	{
		int temp=arr[lo];
		arr[lo]=arr[hi];
		arr[hi]=temp;
	}
    }

    return hi;
}

void quicksort(int arr[], int lo, int hi)
{
    if (lo<hi)
    {
    int dp=partition(lo, hi, arr);
    quicksort(arr, lo, dp);
    quicksort(arr, dp+1, hi);
    }
}

//calling quicksort using child
void* childQuickSort(void *arr)
{
	quicksort(arr,0,size-1);
}

int main (int argc, char* argv[])
{
	
	//for random numbers based on time
	time_t t;
    	srand((unsigned) time(&t));
	
	if (argc==1) //no input from user
	{
		printf("Please run again with a number.\n");
		return -1;
	}

    	while(atoi(argv[1])<=0) //no number or negative number in input
    	{
        	printf("Enter a number more than 0.  ");
        	fflush(stdout);
        	fgets(argv[1], 30, stdin);
    	}
    	size=atoi(argv[1]);

	//making array and generating random numbers
	int* arr=(int*)malloc(size*sizeof(int));
	
	for(int i=0;i<size;i++)
		arr[i]=rand()%10000;
	
	//printing unsorted array
	printf("Array before sorting.\n");	
	for(int i=0;i<size;i++)
        	printf("%d\n",arr[i]);
	
	//creating child thread and doing sort
	pthread_t id;
	int stat;
	stat=pthread_create(&id, NULL, &childQuickSort, (void*)arr);

	//the created thread should have a value of 0 else error
	if (stat)
	{
		printf("Error creating thread\n");
		return -1;		
	}	
	//join thread
	stat=pthread_join(id, NULL);

	//error if join returns value other than 0
	if (stat)
	{
		printf("Error joining thread\n");
		return -1;		
	}		

	//print sorted array
	printf("\nArray after sorting in child.\n");
	for(int i=0;i<size;i++)
        	printf("%d\n",arr[i]);

	free(arr);
	return 0;
}

