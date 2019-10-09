//
// Created by alanfl and jmagnes362 on 10/8/19.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//random number generator
int randomNum(int floor, int ceil){

	return 0;
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
	double elapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return elapsed;
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
	double elapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return elapsed;

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
	int type;
	char* ptrs [50];	

	//run until the 50th malloc
	while(mCount < 50){

		//randomly pick between malloc and free, if cannot free then malloc
		//increment counters after each malloc or free
		type = rand() % 2; //even will be malloc, odd free

		//expected free and there is something to free	
		if(type == 1 && (mCount!=fCount)){
			free(ptrs[fCount]);
			fCount++;

		//expected malloc or unable to free
		}else{
			char* test = malloc(1);
			ptrs[mCount] = test;
			mCount++;			
		}
		
		//all 50 mallocs have occurred. free all remaining pointers
		if(mCount == 50){
			while(fCount < 50){
				free(ptrs[fCount]);
				fCount++;
			}
		}
	}
	
	
		
	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double elapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return elapsed;
}

//D: Randomly choose between a randomly-sized malloc() or free()ing a pointer 
double all_random(){
	//find start time	
	struct timeval start, end;
	gettimeofday(&start, NULL);	

	


	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double elapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return elapsed;
}

//E: Undetermined
double filler_1(){
//find start time	
	struct timeval start, end;
	gettimeofday(&start, NULL);	

	


	//find end time, calculate length, return
	gettimeofday(&end, NULL);
	double elapsed = (end.tv_sec - start.tv_sec) + 
              ((end.tv_usec - start.tv_usec));

	return elapsed;
}

//F: Undetermined
double filler_2(){

	return 0.0;
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
	double sums [] = {0.0,0.0,0.0,0.0,0.0,0.0};
	double averages [6];
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
		printf("Mean time for workload %c = %f microseconds\n", ('A'+ i), averages[i]);
	}


	return 0;

}
