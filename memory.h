#ifndef MEMORY_H_SENTRY
#define MEMORY_H_SENTRY

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define EXAMPLE_DATA_SIZE sizeof(uint16_t)
#define MEMORY_SIZE 1024

void MEMORY_read(uint32_t addr, uint16_t *data, int size);
void MEMORY_write(uint32_t addr, uint16_t *data, int size);

#endif
