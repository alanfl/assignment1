//
// Created by alanfl and jmagnes362 on 10/8/19.
//

#include "mymall.h"
#include <stdio.h>


// This is the header that precedes all managed blocks.
// A negative value denotes that the block is not in use.
// A positive value denotes that the block is in use.
// All size values are in bytes.
short size;

// This constant refers to the size of the header, and should be referenced when calculating block jumps
const size_t header_size = sizeof(size);

// "Managed" block
// Should be initialized as all 0s, since it's located in the BSS
static char* heap[4096];

// Usage: Traverses a linked list of block headers and returns a pointer to the first block that is meets the size
// requirement and is also not in use.
void* first_fit(size_t size);

// Usage: Traverses a linked list of block headers and coalesces blocks that are both adjacent to each other, and freed.
// Note: Coalescing will maintain lower addresses, and adjacent higher addresses will be absorbed
void coalesce();

// Splits an open block into an allocated block, and then appends a free block with the remainder
// of the space at the end
void* split_block(void* block)

// Usage: Primarily for usage of traversing a flattened linked list. Accepts a ptr to the current block and returns
// A ptr to the next adjacent block, or NULL if it exceeds the block's size.
void* get_next_block(void* ptr);

// Usage: This function serves as the primary signature to replace the system-based malloc
// Accepts a block size and returns an address pointing to the start of the newly allocated block
void* mymalloc(size_t size, __FILE__, __LINE__);

// Usage: Accepts a pointer to the start of some allocated portion in the block and marks that portion as
// no longer in use. Should then run coalesce to combine blocks with all adjacent unused neighbors.
void* myfree(void* ptr, __FILE__, __LINE__);

