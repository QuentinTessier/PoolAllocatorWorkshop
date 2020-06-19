#include "MemoryPool.h"

static uint8_t *Address_from_Index(MemoryPool *self, uint32_t i);
static uint32_t Index_from_Address(MemoryPool *self, uint8_t const *p);