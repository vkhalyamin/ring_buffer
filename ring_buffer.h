#ifndef RING_BUFFER_H_SENTRY
#define RING_BUFFER_H_SENTRY

#include <stdint.h>
#include <stdbool.h>

#include "memory.h"

enum BUFFER_ErrorStatus {
    BUFFER_SUCCESS,
    BUFFER_ERROR
};

typedef struct RingBuffer {
    uint32_t addr;
    int head;
    int tail;
    int size;
    bool full;
} RingBuffer;

int BUFFER_init(RingBuffer *ringBuffer, uint32_t addr, int size);
int BUFFER_insert(RingBuffer *ringBuffer, uint16_t data);
int BUFFER_getFirst(RingBuffer *ringBuffer, uint16_t *data);
int BUFFER_getLast(RingBuffer *ringBuffer, uint16_t *data);
int BUFFER_getAllFromHead(RingBuffer *ringBuffer, uint16_t *buffer, int size);
int BUFFER_getAllFromTail(RingBuffer *ringBuffer, uint16_t *buffer, int size);
int BUFFER_getCurrentHeadIndex(RingBuffer *ringBuffer);
int BUFFER_getCurrentTailIndex(RingBuffer *ringBuffer);
int BUFFER_getSize(RingBuffer *ringBuffer);
int BUFFER_getCount(RingBuffer *ringBuffer);
int BUFFER_isFull(RingBuffer *ringBuffer);
int BUFFER_isEmpty(RingBuffer *ringBuffer);
void BUFFER_flush(RingBuffer *ringBuffer);

#endif
