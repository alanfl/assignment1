//
// Created by test on 10/5/19.
//

#ifndef _MEMGRIND_H
#define _MEMGRIND_H

// Returns the runtime in milliseconds
int malloc_and_free_150();

// Returns runtime in ms
int malloc_store_free();

int random_malloc_free_50();

int all_random();

// Generates a random number from [floor, ceil)
int random(int floor, int ceil);
#endif //_MEMGRIND_H
