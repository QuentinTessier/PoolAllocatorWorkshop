#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct MemoryPool {
    uint32_t nBlocks;
    uint32_t sizeBlocks;
    uint32_t nFreeBlocks;
    uint32_t nBlockInit;
    uint8_t *memStart;
    uint8_t *memNext;
} MemoryPool;

MemoryPool *MemoryPool_create(size_t, size_t);
void MemoryPool_reset(MemoryPool *);
void MemoryPool_destroy(MemoryPool *);
void *MemoryPool_obtain(MemoryPool *);
void MemoryPool_release(MemoryPool *, void *);

