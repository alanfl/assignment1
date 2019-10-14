//
// Created by alanfl and jmagnes362 on 10/8/19.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mymalloc.h"

//finds a random freeable ptr and returns its index
int random_free_index(int freed[], int mCount, int fCount){
	int count = -1; //increment upon freeable ptr
	int index = -1;
	//random number, mCount = max index, fCount = #freed to prevent duplicates
	int target = rand() % (mCount - fCount);
	while(index < mCount){
		if(count == target){
			return index;
		}else if(freed[index+1] == 0){ //if next is freeable, increment
			count++;
		}	
		index++;	
	}
}

//return values of A-F will be the elapsed time in microseconds.
//Add /1000 to elapsed calculation if milliseconds wanted

//A: malloc() 1 byte and immediately free it - do this 150 times
double malloc_and_free_150(){
	//find start time
	struct timeval start, end;
	gettimeofday(&start, NULL);
	
	//malloc and free 150 times	
	int i = 0;
	for(i = 0; i < 150; i++){
		char* test = malloc(1);
		free(test);
	}

	//find end time and return
	gettimeofday(&end, NULL);
	double timeElapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return timeElapsed;
}



//B: malloc() 1 byte, store the pointer in an array - do this 150 times.
//Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers
//one by one.

double malloc_store_free(){	
	//find start time	
	struct timeval start, end;
	gettimeofday(&start, NULL);

	char* ptrs [50];
	int i,j;
	//run 150 times
	for(i = 0; i < 3; i++){
		//malloc 50 bytes
		for(j = 0; j < 50; j++){
			char* test = malloc(1);
			ptrs[j] = test;
		}
		//free 50 pointers
		for(j = 0; j < 50; j++){
			free(ptrs[j]);
		}
	}
	
	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double timeElapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return timeElapsed;

}

//C: Randomly choose between a 1 byte malloc() or freeing a 1 byte pointer
//malloc 50 times, if reach 50 mallocs free all, keep track of freed pointers

double random_malloc_free_50(){
	//find start time	
	struct timeval start, end;
	gettimeofday(&start, NULL);	

	//keep track of counts and type
	int mCount = 0;
	int fCount = 0;
	int i = 0;
	int type;
	char* ptrs [50];
	int freed [50];
	//initialize all indexes to -1 to show not malloced or freed
	for(i = 0; i < 50; i++){
		freed[i] = -1;
	}

	//run until the 50th malloc
	while(mCount < 50){

		//randomly pick between malloc and free, if cannot free then malloc
		//increment counters after each malloc or free
		type = rand() % 2; //even will be malloc, odd free


		//new method, random frees
		//expected free and there is something to free	
		if(type == 1 && (mCount!=fCount)){
			i = random_free_index(freed, mCount, fCount);
			free(ptrs[i]);
			freed[i] = 1;
			fCount++;

		//expected malloc or unable to free
		}else{
			char* test = malloc(1);
			ptrs[mCount] = test;
			freed[mCount] = 0;
			mCount++;			
		}
		
		//all 50 mallocs have occurred. free all remaining pointers
		if(mCount == 50){
			while(fCount < 50){
				i = random_free_index(freed, mCount, fCount);
				free(ptrs[i]);
				freed[i] = 1;
				fCount++;
			}
		}	
	}
	
	
		
	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double timeElapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return timeElapsed;
}

//D: Randomly choose between a randomly-sized malloc() or free()ing a pointer 
//Keep track of each malloc so that all mallocs do not exceed your total memory 
//capacity, malloc() 50 times, and free() all pointers.
//Choose a random allocation size between 1 and 64 bytes
//Worst possible scenario is 50 mallocs of max size which = 3300 bytes. This
//cannot exceed the 4096 bytes available

double all_random(){
	//find start time	
	struct timeval start, end;
	gettimeofday(&start, NULL);	

	//keep track of counts and type
	int mCount = 0;
	int fCount = 0;
	int type, size;
	char* ptrs [50];
	int i = 0;	
	int freed [50];
	//initialize all indexes to -1 to show not malloced or freed
	for(i = 0; i < 50; i++){
		freed[i] = -1;
	}


	//run until the 50th malloc
	while(mCount < 50){

		//randomly pick between malloc and free, if cannot free then malloc
		//increment counters after each malloc or free
		type = rand() % 2; //even will be malloc, odd free

		//expected free and there is something to free	
		if(type == 1 && (mCount!=fCount)){
			i = random_free_index(freed, mCount, fCount);
			free(ptrs[i]);
			freed[i] = 1;
			fCount++;

		//expected malloc or unable to free
		}else{
			//random number 1-64 to malloc
			size = rand() % 64 + 1;
			char* test = malloc(size);
			ptrs[mCount] = test;
			freed[mCount] = 0;
			mCount++;			
		}
		
		//all 50 mallocs have occurred. free all remaining pointers
		if(mCount == 50){
			while(fCount < 50){
				i = random_free_index(freed, mCount, fCount);
				free(ptrs[i]);
				freed[i] = 1;
				fCount++;
			}
		}
	}
	


	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double timeElapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return timeElapsed;
}

//E: Testing to make sure that the free() function correctly stitches memory 
//together. Malloc 64 bytes 50 times = (+2 for metadata) 66 x 50 = 3300 bytes, 796 
//remaining. Free first 25 = 1650. Test to make sure this was correctly freed 
//using a larger size malloc. 128 byte mallocs x 10 = 1300 bytes < 1650 but >796. 
//Only correctly mallocs if the frees had stitched together all of the previous 
//64 byte spaces. Will get errors if the frees did not restore the available 
//memory from the first 25 mallocs to 1650 bytes
//free remaining

double filler_1(){
	//find start time	
	struct timeval start, end;
	gettimeofday(&start, NULL);	

	//implement workload
	char* ptrs [50];
	int i;
	int count = 0;
	
	//malloc 64 bytes 50 times, free 25 times
	for(i = 0; i < 50; i++){
		char* test = malloc(64);
		ptrs[i] = test;
	}	
	for(i = 0; i < 25; i++){
		free(ptrs[i]);
	}	
		
	//malloc 128 bytes 10 times
	for(i = 0; i < 10; i++){
		char* test = malloc(128);
		ptrs[i] = test;
	}	

	//free all pointers
	for(i = 0; i < 50; i++){
		if(i == 10){
			i = 24;
			continue;
		}
		free(ptrs[i]);
	}	

	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double timeElapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return timeElapsed;
}

//F: Randomly sized mallocs until we are no longer able to malloc without 
//going over 4096 bytes. Do maximum malloc size. Free all. Uses almost  
double filler_2(){
	//find start time
	struct timeval start, end;
	gettimeofday(&start, NULL);	

	
	//implement workload
	char* ptrs [5000]; //tons of space because no defined number of mallocs
	int i = 0;
	int size;
	int done = 0;
	int count = 0;
	int total = 0;
	//run until we cannot malloc anymore
	while(total < 4094){
		if(total >= 4092){ //not enough space for block division
			break;
		}
		size = rand() % 64 + 1; //random size 1-64
		if((size + total) > 4094){ //4096 - 2 for first metadata
			size = 4094 - total;
			done = 1;
		}
		char* test = malloc(size);
		ptrs[i] = test;
		total += size + 2;
		count++;
		i++;
	}

	//takes between 100-130 mallocs to fill up all the space
	//printf("There were %d mallocs\n", count);

	//free all
	for(i = 0; i < count; i++){
		free(ptrs[i]);
	}


	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double timeElapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return timeElapsed;
}



int main (int argc, char* argv[]){
	
	/*
	Your memgrind.c should run all the workloads, one after the other, 100 		times. It should record the run time for each workload and store it. 		When all 100 iterations of all the workloads have been run,
	memgrind.c should calculate the mean time for each workload to execute 		and output them in sequence. You might find the 
	gettimeofday(struct timeval * tv, struct timezone * tz) function in the 	time.h library useful. 
	*/



	//loop that runs all workloads back to back 100 times and calculates 
	//mean runtime
	int i = 0;
	//sum was occassionaly overflowing on long runtimes
	long long sums [] = {0.0,0.0,0.0,0.0,0.0,0.0}; 
	double averages [] = {0.0,0.0,0.0,0.0,0.0,0.0};
	for(i = 0; i < 100; i++){
		sums[0] += malloc_and_free_150();
		sums[1] += malloc_store_free();
		sums[2] += random_malloc_free_50();
		sums[3] += all_random();
		sums[4] += filler_1();
		sums[5] += filler_2(); 
	}


	for(i = 0; i < 6; i++){
		//printf("Sum %d = %f\n", i, sums[i]);
		averages[i] = sums[i] / 100.0;
		printf("Mean time for workload %c = %lf microseconds\n", ('A'+ i), averages[i]);
	}


	return 0;

}
