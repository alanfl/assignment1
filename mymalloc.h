//
// Created by alanfl and jmagnes on 10/3/19.
//

#ifndef _MYMALLOC_H
#define _MYMALLOC_H

// Overrides system-based memory management calls
#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

// The "definition" of the metadata that is stored in the block
// Note: This actual struct is not stored in the block, but rather this
// declaration only serves as an abstraction what is required by the program
// TODO find out way to "flatten" this
typedef struct Node {
    Node* next;
    size_t size;
} Node;

// Usage: This function serves as the primary signature to replace the system-based malloc
// Accepts a block size and returns an address pointing to the start of the newly allocated block
void* mymalloc(size_t size, __FILE__, __LINE__);

// Usage: Accepts a pointer to the start of some allocated portion in the block and marks that portion as
// no longer in use. Should then run coalesce to combine blocks with all adjacent unused neighbors.
void* myfree(void* ptr, __FILE__, __LINE__);

// Usage: Traverses a linked list of block headers and returns a pointer to the first block that is greater than or equal
// to the input size
void* first_fit(size_t size);

// Usage: Traverses a linked list of block headers and coalesces blocks that are both adjacent to each other, and freed.
// Note: Coalescing will maintain lower addresses, and adjacent higher addresses will be absorbed
void coalesce();

void* get_previous_block(void* ptr);

void* get_next_block(void* ptr);

size_t round_size(size_t size);

// Defines the heap block
static char* heap[4096];

// Splits an open block into an allocated block, and then appends a free block with the remainder
// of the space at the end
void* split_block(void* block)

#endif //_MYMALLOC_H
