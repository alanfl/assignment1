//
// Created by alanfl and jmagnes362 on 10/8/19.
//

#include <stdio.h>
#include <stdlib.h>

// This is the header that precedes all managed blocks.
// A positive value denotes that the block is not in use.
// A negative value denotes that the block is in use.
// All size values are in bytes.
typedef struct header_t {
    short size;
} header_t;

// Defines the heap block
static char heap[4096];

// This constant refers to the size of the header, and should be referenced when calculating block jumps
const short header_size = (short) sizeof(header_t);

// This constant refers to the block size, and is abstracted in case the managed block size ever changes
const short heap_size = (short) 4096;

// Usage: Traverses a linked list of block headers and returns a pointer to the first block that is meets the size
// requirement and is also not in use.
void* first_fit(short size);

// Usage: Traverses a linked list of block headers and coalesces blocks that are both adjacent to each other, and freed.
// Note: Coalescing will maintain lower addresses, and adjacent higher addresses will be absorbed
void coalesce();

// Splits an free block into two blocks, one with the specified size
// and then appends a free block with the remainder of the space at the end
// Returns the block with the specified size
void* split_block(header_t * header, short size);

// Usage: Primarily for usage of traversing a flattened linked list. Accepts a ptr to the current block and returns
// A ptr to the next adjacent block, or NULL if it exceeds the block's size.
void* get_next_block(const header_t * header);

// Usage: Dumps all information in the heap
void dump_heap();

char *init_heap();

void* mymalloc(size_t size, char* file_name, int line_num) {

    // Validate size
    if(size < 1 || size > (heap_size - header_size)) {
        printf("Error in %s at line %d: Invalid size error: Requested size was invalid.", file_name, line_num);
        return NULL;
    }

    // Start at the head
    header_t *curr_header = (header_t *)init_heap();

    // Find first block that is large enough to meet request
    curr_header = first_fit((short) size);

    // Check if first fit was able to find a block at all
    if(!curr_header) {
        printf("Error in %s at line %d: Out of space error: Heap is out of space.", file_name, line_num);
        return NULL;
    }

    // Block is larger, split into specified size and remainder
    if(curr_header->size > size) {
        curr_header = split_block(curr_header, size);
    }

    // Mark newly allocated block as in use
    curr_header->size *= -1;

    return ((void *)curr_header) + header_size;
}

void myfree(void* ptr, char* file_name, int line_num) {
    // Start at head
    header_t *curr_header = (header_t *) init_heap();

    // Iterate list
    while(curr_header != NULL) {

        // If ptr matches any address in the list that has been allocated, then mark it as free only if it is in use
        if( ((void *)curr_header + header_size) == ptr ) {
            if(curr_header->size < 0) {
                curr_header->size *= -1;
                coalesce();
                return;
            } else {
                printf("Error in %s at line %d: Redundant free error: Block is not allocated.", file_name, line_num);
                return;
            }
        }

        curr_header = get_next_block(curr_header);
    }

    // If not returned, then the provided ptr was invalid
    printf("Error in %s at line %d: Invalid pointer error: Provided pointer was either not allocated or not a pointer.", file_name, line_num);
}

void* first_fit(short requested_size) {
    // Begin at head of allocated block
    header_t * curr_header = (header_t *)heap;

    // Traverse list
    while(curr_header != NULL) {
        // This block is of adequate size AND not in use, return this header
        if( curr_header->size > 0 && (curr_header->size) >= requested_size )
            return curr_header;
        else
            curr_header = get_next_block(curr_header);
    }

    // Could not find a block of appropriate size, return null
    return NULL;
}

void coalesce() {
    // Begin at head of allocated block
    // Also track the next block over for coalescing purposes
    header_t *curr_header = (header_t *)heap;
    header_t *next_header = get_next_block(curr_header);

    // Traverse list until end, next_header should remain ahead in case a coalesce is necessary
    while(curr_header != NULL && next_header != NULL) {
        // This block is free and so is the next, coalesce next into this one
        if( curr_header->size >= 0 && next_header->size >= 0) {
            // Also mark this ptr as unused
            curr_header->size = (short) (curr_header->size + next_header->size + header_size);

            // Move the next block forward in case the next block is able to be coalesced
            next_header = get_next_block(curr_header);
        }
        // Not able to coalesce, move pointers forward
        else {
            curr_header = get_next_block(curr_header);
            next_header = get_next_block(curr_header);
        }
    }
}

void* split_block(header_t * header, short size) {
    header_t *next = header;

    // Check if able to insert a new header into the remainder, if so, split this block
    if( (header->size - size) > header_size) {
        header->size = header->size - size - header_size;

        next = get_next_block(header);

        // Check that we didn't go out of bounds for some reason
        next->size = size;
    }

    return next;
}

void* get_next_block(const header_t * header) {
    short size = (short)abs(header->size);
    header_t *next_header = (header_t *) ((void*)header + size + header_size);

    // next_header is out of bounds
    if((char *)next_header >= (heap + heap_size))
        return NULL;
    else
        return next_header;
}

void dump_heap() {
    header_t *header = (header_t *)init_heap();
    printf("Dumping heap: ");
    while(header != NULL) {
        printf("%hi, ", header->size);
        header = get_next_block(header);
    }

    printf("\n");
}

char* init_heap() {
    // Start at the head
    header_t *curr_header = (header_t *) heap;

    // Check if this is the first allocation
    if(curr_header->size == 0) {
        // Insert initial node
        curr_header->size = heap_size - header_size;
    }

    return heap;
}