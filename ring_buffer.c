#include "ring_buffer.h"

int BUFFER_init(RING_BUFFER *ringBuffer, uint16_t *buffer, int size)
{
    if (!(buffer && size)) {
        return BUFFER_ERROR;
    }
    ringBuffer->buffer = buffer;
    ringBuffer->size = size;
    BUFFER_flush(ringBuffer);

    return BUFFER_SUCCESS;
}

int BUFFER_insert(RING_BUFFER *ringBuffer, uint16_t data)
{
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

int BUFFER_getFirst(RING_BUFFER *ringBuffer, uint16_t *data)
{
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

int BUFFER_getLast(RING_BUFFER *ringBuffer, uint16_t *data)
{
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

int BUFFER_getCurrentHeadIndex(RING_BUFFER *ringBuffer)
{
    return ringBuffer->head;
}

int BUFFER_getCurrentTailIndex(RING_BUFFER *ringBuffer)
{
    return ringBuffer->tail;
}

int BUFFER_getSize(RING_BUFFER *ringBuffer)
{
    return ringBuffer->size;
}

int BUFFER_getCount(RING_BUFFER *ringBuffer)
{
    if (ringBuffer->full) {
        return ringBuffer->size;
    }
    else {
        return (ringBuffer->head >= ringBuffer->tail) ? (ringBuffer->head - ringBuffer->tail)
            : (ringBuffer->size + ringBuffer->head - ringBuffer->tail);
    }
}

int BUFFER_isFull(RING_BUFFER *ringBuffer)
{
    return ringBuffer->full;
}

int BUFFER_isEmpty(RING_BUFFER *ringBuffer)
{
    return ((!ringBuffer->full) && (ringBuffer->head == ringBuffer->tail)); 
}

void BUFFER_flush(RING_BUFFER *ringBuffer)
{
    ringBuffer->head = 0;
    ringBuffer->tail = 0;
    ringBuffer->full = 0;
}