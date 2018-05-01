#include "sort.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <time.h>
int len[7] = {100,500,1000,2000,5000,8000,10000}; //array storing data sizes for testing
void bubblesort(int* arr){ //bubble sort implementation
  int i, j,temp;
  for (i = 0; i < MAX-1; i++){
    //swaps elements if condition is met
      for (j = 0; j < MAX-i-1; j++){
          if (arr[j] > arr[j+1]){
            temp = arr[j];
            arr[j] = arr[j+1];
            arr[j+1] = temp;
          }
      }
  }
}

void insertsort(int* arr,int n){
     int i, key, j;
     for (i = 1; i < n; i++)
     {
         key = arr[i]; //performs shifting on array based on numerical comparison
         j = i-1;
         while (j >= 0 && arr[j] > key)
         {
             arr[j+1] = arr[j];
             j = j-1;
         }
         arr[j+1] = key;
     }

}

void quicksort(int* arr, int begin,int finish){
  int q = begin; int v = finish;
  	int temp;
  	//divides array
  	int pivot = arr[(begin+finish)/2];
  	while(q <= v)
  	{	//checks for values greater than and less than pivot then performs swap
  		while(arr[q] < pivot)
  		{
  			q++;
  		}
  		while(arr[v] > pivot)
  		{
  			v--;
  		}
  		if(q <= v)
  		{
  			temp = arr[q];
  			arr[q] = arr[v];
  			arr[v] = temp;
  			q++;
  			v--;
  		}
  	};
  	//recursion
  	if(begin < v)
  	{
  		quicksort(arr,begin,v);
  	}
  	if(q < finish)
  	{
  		quicksort(arr,q,finish);
  	}
}

void mergesort(int* arr, int low, int high){
	int mid;
	if (low < high)
	{
		mid=(low+high)/2;
		// splits the data into halves.
		mergesort(arr, low, mid);
		mergesort(arr, mid+1, high);

		// merge them to get output.
		merge(arr, low, high, mid);
	}
}

void merge(int* arr,int low,int high,int mid){
	int i, j, k, temp[high-low+1];
	i = low;
	k = 0;
	j = mid + 1;
 
	// merge parts into temporary array
	while (i <= mid && j <= high)
	{
		if (arr[i] < arr[j])
		{
			temp[k] = arr[i];
			k++;
			i++;
		}
		else
		{
			temp[k] = arr[j];
			k++;
			j++;
		}
	}
 
	// Insert values from i to mid into temp.
	while (i <= mid)
	{
		temp[k] = arr[i];
		k++;
		i++;
	}
 
	// nsert values from j to temp[].
	while (j <= high)
	{
		temp[k] = arr[j];
		k++;
		j++;
	}
 
 
	// set temp = to array
	for (i = low; i <= high; i++)
	{
		arr[i] = temp[i-low];
	}
}

void heapsort(int* arr,int n){
	// Build heap
    for (int i = n / 2 - 1; i >= 0; i--)
        heap(arr, n, i);
 
    // extract from heap
    for (int i=n-1; i>=0; i--)
    {
        // move root to end
        swap(&arr[0], &arr[i]);
 
        // call heap on reduced heap
        heap(arr, i, 0);
    }
}

void heap(int* arr,int n,int i){
	int largest = i;  // largest # as root
    int l = 2*i + 1;  
    int r = 2*i + 2;  
 
    // if left larger than root
    if (l < n && arr[l] > arr[largest])
        largest = l;
 
    // if right larger than root
    if (r < n && arr[r] > arr[largest])
        largest = r;
 
    // if largest is not the root
    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
 
        // heap subtree
        heap(arr, n, largest);
    }
}

void swap(int* i,int* j){ //generic swapping algorithm
	int temp;
	temp = *i;
	*i = *j;
	*j = temp;
}
void test(int* vals,int* sortedvals){
	clock_t t;
	double execTime; //variable to store run time
	int temp[MAX]; //temp array to store data to be sorted 
	FILE* fp; //creates file to store run time output
	fp = fopen("time.csv","w");
	if(fp == NULL)
		perror(0);
	fprintf(fp,"Unsorted Input Size, Insert, Quick, Heap, Merge,\n"); //attaches header
	populate(vals,temp); //fills up temp
	for(int x = 0;x<7;x++){ //repeats loop for all data sizes
		fprintf(fp,"%d,",len[x]); //prints the length to the row
		t = clock(); //gets current time
		insertsort(temp,len[x]); //runs the sort
		t = clock() - t; //finds difference in time
		execTime = ((double)t)/CLOCKS_PER_SEC; //calculates execution time based on clocks per sec
		fprintf(fp,"%f,",execTime); //appends execution time
		populate(vals,temp); //repopulates temp with unsorted data
		t = clock(); //reapeats for all other sorting algorithms
		quicksort(temp,0,len[x]);
		t = clock() - t;
		execTime = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp,"%f,",execTime);
		populate(vals,temp);
		t = clock();
		mergesort(temp,0,len[x]);
		t = clock() - t;
		execTime = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp,"%f,",execTime);
		populate(vals,temp);
		t = clock();
		heapsort(temp,len[x]);
		t = clock() - t;
		execTime = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp,"%f,\n",execTime);
		populate(vals,temp);
	}
	fprintf(fp,"Sorted Input Size, Insert, Quick, Heap, Merge,\n"); //appends header
	populate(sortedvals,temp);
	for(int x = 0;x<7;x++){ //repeats same as above but 
		fprintf(fp,"%d,",len[x]);
		t = clock();
		insertsort(temp,len[x]);
		t = clock() - t;
		execTime = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp,"%f,",execTime);
		populate(sortedvals,temp);
		t = clock();
		quicksort(temp,0,len[x]);
		t = clock() - t;
		execTime = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp,"%f,",execTime);
		populate(sortedvals,temp);
		t = clock();
		mergesort(temp,0,len[x]);
		t = clock() - t;
		execTime = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp,"%f,",execTime);
		populate(sortedvals,temp);
		t = clock();
		heapsort(temp,len[x]);
		t = clock() - t;
		execTime = ((double)t)/CLOCKS_PER_SEC;
		fprintf(fp,"%f,\n",execTime);
		populate(sortedvals,temp);
	}	
		fclose(fp);	
}

void populate(int* arr,int* temp){ //assigns passed array to temp
	for(int x = 0;x<MAX;x++){
		temp[x] = arr[x];
	}
}
