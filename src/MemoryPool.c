#include "MemoryPool.h"

MemoryPool *MemoryPool_create(size_t block_size, size_t block_count)
{
    MemoryPool *n = malloc(sizeof(MemoryPool));

    if (n == 0)
        return 0;
    n->nBlocks = block_count;
    n->sizeBlocks = (block_size < 4) ? 4 : block_size;
    n->memStart = malloc(block_size * block_count);
    if (n->memStart == 0) {
        free(n);
        return 0;
    }
    n->nBlockInit = 0;
    n->nFreeBlocks = n->nBlocks;
    n->memNext = n->memStart;
    return n;
}

void MemoryPool_destroy(MemoryPool *self)
{
    free(self->memStart);
    free(self);
    self = 0;
}

static uint8_t *Address_from_Index(MemoryPool *self, uint32_t i)
{
    return self->memStart + (i * self->sizeBlocks);
}

static uint32_t Index_from_Address(MemoryPool *self, uint8_t const *p)
{
    return ((uint32_t)(p - self->memStart) / self->sizeBlocks);
}

void MemoryPool_reset(MemoryPool *self)
{
    self->nFreeBlocks = self->nBlocks;
    self->memNext = self->memStart;
    self->nBlockInit = 0;
}

void *MemoryPool_obtain(MemoryPool *self)
{
    if (self->nBlockInit < self->nBlocks) {
        uint32_t *p = (uint32_t *)Address_from_Index(self, self->nBlockInit);
        *p = self->nBlockInit + 1;
        self->nBlockInit += 1;
    }
    void *ret = 0;
    if (self->nFreeBlocks > 0) {
        ret = (void *)self->memNext;
        self->nFreeBlocks -= 1;
        if (self->nFreeBlocks != 0) {
            self->memNext = Address_from_Index(self, *((uint32_t *)self->memNext));
        } else {
            self->memNext = 0;
        }
    }
    return 0;
}

void MemoryPool_release(MemoryPool *self, void *ptr)
{
    if (ptr != 0) {
        (*(uint32_t *)ptr) = Index_from_Address(self, self->memNext);
        self->memNext = ptr;
    } else {
        *((uint32_t *)ptr) = self->nBlocks;
        self->memNext = ptr;
    }
    self->nFreeBlocks += 1;
}