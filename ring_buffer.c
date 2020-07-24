#include "ring_buffer.h"

int BUFFER_init(RingBuffer *ringBuffer, uint16_t *buffer, int size) {
    if (!(buffer && size && ringBuffer)) {
        return BUFFER_ERROR;
    }

    ringBuffer->buffer = buffer;
    ringBuffer->size = size;
    BUFFER_flush(ringBuffer);

    return BUFFER_SUCCESS;
}

int BUFFER_insert(RingBuffer *ringBuffer, uint16_t data) {
    if ((!ringBuffer) || (!ringBuffer->buffer)) {
        return BUFFER_ERROR;
    }

    ringBuffer->buffer[ringBuffer->head] = data;
    ringBuffer->head = (ringBuffer->head + 1) % ringBuffer->size;

    if (ringBuffer->full) {
        ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->size;
    }

    ringBuffer->full = (ringBuffer->head == ringBuffer->tail);

    return BUFFER_SUCCESS;
}

int BUFFER_getFirst(RingBuffer *ringBuffer, uint16_t *data) {
    if (BUFFER_isEmpty(ringBuffer)) {
        return BUFFER_ERROR;
    }

    if (ringBuffer->full) {
        ringBuffer->full = 0;
    }

    *data = ringBuffer->buffer[ringBuffer->tail];
    ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->size;

    return BUFFER_SUCCESS;
}

int BUFFER_getLast(RingBuffer *ringBuffer, uint16_t *data) {
    if (BUFFER_isEmpty(ringBuffer)) {
        return BUFFER_ERROR;
    }

    if (ringBuffer->full) {
        ringBuffer->full = 0;
    }

    (ringBuffer->head) ? (ringBuffer->head--) : (ringBuffer->head = ringBuffer->size - 1);
    *data = ringBuffer->buffer[ringBuffer->head];

    return BUFFER_SUCCESS;
}

int BUFFER_getCurrentHeadIndex(RingBuffer *ringBuffer) {
    return ringBuffer->head;
}

int BUFFER_getCurrentTailIndex(RingBuffer *ringBuffer) {
    return ringBuffer->tail;
}

int BUFFER_getSize(RingBuffer *ringBuffer) {
    return ringBuffer->size;
}

int BUFFER_getCount(RingBuffer *ringBuffer) {
    if (ringBuffer->full) {
        return ringBuffer->size;
    }
    else {
        return (ringBuffer->head >= ringBuffer->tail) ? (ringBuffer->head - ringBuffer->tail)
            : (ringBuffer->size + ringBuffer->head - ringBuffer->tail);
    }
}

int BUFFER_isFull(RingBuffer *ringBuffer) {
    return ringBuffer->full;
}

int BUFFER_isEmpty(RingBuffer *ringBuffer) {
    return ((!ringBuffer->full) && (ringBuffer->head == ringBuffer->tail)); 
}

void BUFFER_flush(RingBuffer *ringBuffer) {
    ringBuffer->head = 0;
    ringBuffer->tail = 0;
    ringBuffer->full = 0;
}
