#include <stdio.h>
#include "src/MemoryPool.h"

int main()
{
    printf("Pool Allocator Workshop\n");
    MemoryPool *mem = MemoryPool_create(sizeof(float), 300);

    float *ptr = MemoryPool_obtain(mem);
    return 0;
}