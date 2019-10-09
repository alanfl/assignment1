//
// Created by alanfl and jmagnes362 on 10/8/19.
//


#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//A: malloc() 1 byte and immediately free it - do this 150 times
int malloc_and_free_150(){
	
	return 0;
}

/*
B: malloc() 1 byte, store the pointer in an array - do this 150 times.
Once you've malloc()ed 50 byte chunks, then free() the 50 1 byte pointers one by one.
*/
int malloc_store_free(){
	
	return 0;

}

//C: Randomly choose between a 1 byte malloc() or free()ing a 1 byte pointer
int random_malloc_free_50(){

	return 0;
}

//D: Randomly choose between a randomly-sized malloc() or free()ing a pointer 
int all_random(){

	return 0;
}

//E: Undetermined
int filler_1(){

	return 0;
}

//F: Undetermined
int filler_2(){

	return 0;
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
	int sums [] = {0,0,0,0,0,0};
	int averages [6];
	for(i = 0; i < 100; i++){
		sums[0] += malloc_and_free_150();
		sums[1] += malloc_store_free();
		sums[2] += random_malloc_free_50();
		sums[3] += all_random();
		sums[4] += filler_1();
		sums[5] += filler_2(); 
	}

	for(i = 0; i < 6; i++){
		averages[i] = sums[i] / 100;
		printf("Mean time for workload %d = %d\n", i, averages[i]);
	}

	return 0;

}
