#include <stdio.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include "sort.h"
void randNum(int*,int*);
char printMen();
void printArr(int*);

int main (void){
  char resp; //var for storing user response
  int vals[MAX]; //arrays for holding generated data
  int sortedvals[MAX];
  srand(time(NULL)); //seeds random number generator
  randNum(vals,sortedvals); //generates the random numbers for array
  while(1){ //prints the menu for the initial sort then performs the sort based on selection
	std::cout<<"Please select the method of initial sorting:\n"<<std::endl;
	std::cout<<"-----------------"<<std::endl;
	std::cout<<"1)Insertion Sort"<<std::endl;
	std::cout<<"2)Quick Sort"<<std::endl;
	std::cout<<"3)Merge Sort"<<std::endl;
	std::cout<<"4)Heap Sort"<<std::endl;
	std::cout<<"5)Quit"<<std::endl;
	std::cout<<"-----------------"<<std::endl;
	resp = getchar();
	getchar();
	if(resp == '2'){
		quicksort(sortedvals,0,MAX);
		break;
	}
	else if(resp == '1'){
		insertsort(sortedvals,MAX);
		break;
	}
	else if(resp == '3'){
		mergesort(sortedvals,0,MAX);
		break;
	}
	else if(resp == '4'){
		heapsort(sortedvals,MAX);
		break;
	}
	else if(resp == '5')
		exit(0);
	else{
		std::cout<<"Please enter valid option"<<std::endl;
		continue;
	}
}
  //bubblesort(sortedvals);
  while(1){ //secondary menu that allows user to print or run a time test
    resp = printMen();
    getchar();
    if(resp == '3')
      printArr(sortedvals);
    else if(resp == '2')
      printArr(vals);
    else if(resp == '4')
      exit(0);
    else if(resp == '1')
      test(vals,sortedvals);
    else
      std::cout<<"Please enter valid option"<<std::endl;
    }

}

char printMen(){ //function for handling user input and menu printing
  std::cout<<"Sort Menu"<<std::endl;
  std::cout<<"-----------------"<<std::endl;
  std::cout<<"1)Run Time Test"<<std::endl;
  std::cout<<"2)View Generated Array"<<std::endl;
  std::cout<<"3)View Generated Sorted Array"<<std::endl;
  std::cout<<"4)Quit"<<std::endl;
  std::cout<<"-----------------"<<std::endl;
  return getchar();
}

void randNum(int* vals,int* sortedvals){ //generates random numbers
  bool repeat;
  int n;
  for(int x=0;x<MAX;x++){ //generates random numbers then checks to see if they are already in the array
    do{					//if a number is already in the array regenerate
      n=rand()%MAXVAL;
      repeat = true;
      for(int i = 0;i<x;i++){
        if(n == vals[i]){
          repeat = false;
          break;
        }
      }
    }while(!repeat);
    vals[x] = n;
    sortedvals[x] = n;
  }
  return;
}

void printArr(int* vals){ //function for printing the completed array in rows of 10
  for(int x = 0;x<MAX;x++){
    if(x % 10 == 0 && x != 0){
      std::cout<<"\n";
    }
      std::cout<<vals[x]<<" ";
    }
    std::cout<<std::endl;
}
