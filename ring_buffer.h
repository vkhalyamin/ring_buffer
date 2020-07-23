d#ifndef RING_BUFFER_H_SENTRY
#define RING_BUFFER_H_SENTRY

#include <stdint.h>

enum BUFFER_ErrorStatus {
    BUFFER_SUCCESS,
    BUFFER_ERROR
};

typedef struct RingBuffer {
    uint16_t *buffer;
    int head;
    int tail;
    int size;
    int full;
} RING_BUFFER;

int BUFFER_init(RING_BUFFER *ringBuffer, uint16_t *buffer, int size);
int BUFFER_insert(RING_BUFFER *ringBuffer, uint16_t data);
int BUFFER_getFirst(RING_BUFFER *ringBuffer, uint16_t *data);
int BUFFER_getLast(RING_BUFFER *ringBuffer, uint16_t *data);
int BUFFER_getCurrentHeadIndex(RING_BUFFER *ringBuffer);
int BUFFER_getCurrentTailIndex(RING_BUFFER *ringBuffer);
int BUFFER_getSize(RING_BUFFER *ringBuffer);
int BUFFER_getCount(RING_BUFFER *ringBuffer);
int BUFFER_isFull(RING_BUFFER *ringBuffer);
int BUFFER_isEmpty(RING_BUFFER *ringBuffer);
void BUFFER_flush(RING_BUFFER *ringBuffer);

#endif