//
// Created by alanfl and jmagnes362 on 10/3/19.
//

#pragma once

// Overrides system-based memory management calls
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

// Defines the heap block
static char* heap[4096];

// Usage: This function serves as the primary signature to replace the system-based malloc
// Accepts a block size and returns an address pointing to the start of the newly allocated block
void* mymalloc(size_t size, __FILE__, __LINE__);

// Usage: Accepts a pointer to the start of some allocated portion in the block and marks that portion as
// no longer in use. Should then run coalesce to combine blocks with all adjacent unused neighbors.
void* myfree(void* ptr, __FILE__, __LINE__);
