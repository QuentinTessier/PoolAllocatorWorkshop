#pragma once

#include <stddef.h>
#include <stdint.h>

typedef struct MemoryPool {

} MemoryPool;

MemoryPool *MemoryPool_create(size_t, size_t);
void MemoryPool_reset(MemoryPool *);
void MemoryPool_destroy(MemoryPool *);
void *MemoryPool_obtain(MemoryPool *);
void MemoryPool_release(MemoryPool *, void *);

