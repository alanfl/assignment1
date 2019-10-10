//
// Created by alanfl and jmagnes362 on 10/8/19.
//

#include "mymalloc.h"

// This is the header that precedes all managed blocks.
// A negative value denotes that the block is not in use.
// A positive value denotes that the block is in use.
// All size values are in bytes.
short block_size;

// This constant refers to the size of the header, and should be referenced when calculating block jumps
const short header_size = sizeof(block_size);

// This constant refers to the block size, and is abstracted in case the managed block size ever changes
const int heap_size = 4096;

// "Managed" block
// Should be initialized as all 0s, since it's located in the BSS
static char heap[heap_size];

// Usage: Traverses a linked list of block headers and returns a pointer to the first block that is meets the size
// requirement and is also not in use.
void* first_fit(size_t size);

// Usage: Traverses a linked list of block headers and coalesces blocks that are both adjacent to each other, and freed.
// Note: Coalescing will maintain lower addresses, and adjacent higher addresses will be absorbed
void coalesce();

// Splits an free block into two blocks, one with the specified size
// and then appends a free block with the remainder of the space at the end
// Returns the block with the specified size
void* split_block(char* ptr, short size);

// Usage: Primarily for usage of traversing a flattened linked list. Accepts a ptr to the current block and returns
// A ptr to the next adjacent block, or NULL if it exceeds the block's size.
void* get_next_block(const char* ptr);

// todo
void* mymalloc(size_t size) {
    return NULL;
}

// todo
void* myfree(void* ptr) {
    return NULL;
}

void* first_fit(size_t requested_size) {
    // Begin at head of allocated block
    char* ptr = &heap[0];

    // Traverse list
    while(ptr != NULL) {
        // This block is of proper size AND not in use, return this block
        if( abs( *ptr ) >= requested_size && (short) *ptr < 0)
            return ptr + header_size;
        else
            get_next_block(ptr);
    }

    // Could not find a block of appropriate size, return null
    return NULL;
}

void coalesce() {
    // Begin at head of allocated block
    char * ptr = &heap[0];
    char * next_ptr = get_next_block(ptr);

    // Traverse list until end, ptr should remain behind, next peeks into next in case a coalesce is necessary
    while(ptr != NULL && next_ptr != NULL) {
        // This block is free and so is the next, coalesce next into this one
        if((signed short) *ptr < 0 && (signed short) *next_ptr < 0) {
            short ptr_size = (short) abs(*ptr);
            short next_ptr_size = (short) abs(*next_ptr);

            // Also mark this ptr as unused
            *((short*)ptr) = (short) abs(ptr_size + next_ptr_size + header_size) * -1;

            // Move the next block forward in case the next block is able to be coalesced
            next_ptr = get_next_block(ptr);
        }
        // Not able to coalesce, move pointers forward
        else {
            ptr = get_next_block(ptr);
            next_ptr = get_next_block(ptr);
        }
    }
}

void* split_block(char* ptr, short size) {
    short original_size = (short) abs(*ptr);
    *((short*)ptr) = (short) (size * -1);

    // Newly inserted node is free
    char* next = get_next_block(ptr);
    *((short*)next) = (short) (original_size - size - header_size) * -1;

    return ptr;
}

void* get_next_block(const char* ptr) {
    int index = 0;
    short ptr_size = (short) *ptr;

    index = ptr_size + header_size;

    if(index > block_size)
        return NULL;
    else
        return &heap[index];
}
