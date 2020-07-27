#include "memory.h"

/// instead flash memory with 32-bit address
static uint16_t MEMORY[MEMORY_SIZE];

void MEMORY_read(uint32_t addr, uint16_t *data, int size) {
    *data = MEMORY[addr];
    return;
}

void MEMORY_write(uint32_t addr, uint16_t *data, int size) {
    MEMORY[addr] = *data;
    return;
}
