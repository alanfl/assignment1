//
// Created by alanfl and jmagnes362 on 10/8/19.
//

#include "mymall.h"
#include <stdio.h>

// "Managed" block
// Should be initialized as all 0s, since it's located in the BSS
static char* heap[4096];

void* mymalloc(size_t size, __FILE__, __LINE__) {

    // The block is not

}