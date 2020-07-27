#include "ring_buffer.h"

int BUFFER_init(RingBuffer *ringBuffer, uint32_t addr, int size) {
    if ((!ringBuffer) || (!size)) {
        return BUFFER_ERROR;
    }

    ringBuffer->addr = addr;
    ringBuffer->size = size;
    BUFFER_flush(ringBuffer);

    return BUFFER_SUCCESS;
}

int BUFFER_insert(RingBuffer *ringBuffer, uint16_t data) {
    if (!ringBuffer) {
        return BUFFER_ERROR;
    }

    MEMORY_write(ringBuffer->addr + ringBuffer->head, &data, EXAMPLE_DATA_SIZE);
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
        ringBuffer->full = false;
    }

    MEMORY_read(ringBuffer->addr + ringBuffer->tail, data, EXAMPLE_DATA_SIZE);
    ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->size;

    return BUFFER_SUCCESS;
}

int BUFFER_getLast(RingBuffer *ringBuffer, uint16_t *data) {
    if (BUFFER_isEmpty(ringBuffer)) {
        return BUFFER_ERROR;
    }

    if (ringBuffer->full) {
        ringBuffer->full = false;
    }

    (ringBuffer->head) ? (ringBuffer->head--) : (ringBuffer->head = ringBuffer->size - 1);
    /// maybe it's better:
    /// ringBuffer->head = (ringBuffer->head + ringBuffer->size - 1) % ringBuffer->size;
    MEMORY_read(ringBuffer->addr + ringBuffer->head, data, EXAMPLE_DATA_SIZE);

    return BUFFER_SUCCESS;
}

int BUFFER_getAllFromHead(RingBuffer *ringBuffer, uint16_t *buffer, int size) {
    if ((!ringBuffer) || (!buffer) || (!size) || (BUFFER_isEmpty(ringBuffer))) {
        return BUFFER_ERROR;
    }

    if (ringBuffer->full) {
        ringBuffer->full = false;
    }
    
    for (int i = 0; i < size; i++) {
        (ringBuffer->head) ? (ringBuffer->head--) : (ringBuffer->head = ringBuffer->size - 1);
        /// ringBuffer->head = (ringBuffer->head + ringBuffer->size - 1) % ringBuffer->size;
        MEMORY_read(ringBuffer->addr + ringBuffer->head, &buffer[i], EXAMPLE_DATA_SIZE);
        
        if (ringBuffer->head == ringBuffer->tail) {
            MEMORY_read(ringBuffer->addr + ringBuffer->head, &buffer[i], EXAMPLE_DATA_SIZE);
            break;
        }
    }
    
    return BUFFER_SUCCESS;
}

int BUFFER_getAllFromTail(RingBuffer *ringBuffer, uint16_t *buffer, int size) {
    if ((!ringBuffer) || (!buffer) || (!size) || (BUFFER_isEmpty(ringBuffer))) {
        return BUFFER_ERROR;
    }

    if (ringBuffer->full) {
        ringBuffer->full = false;
    }

    for (int i = 0; i < size; i++) {
        MEMORY_read(ringBuffer->addr + ringBuffer->tail, &buffer[i], EXAMPLE_DATA_SIZE);
        ringBuffer->tail = (ringBuffer->tail + 1) % ringBuffer->size;
        
        if (ringBuffer->tail == ringBuffer->head) {
            break;
        }
    }
    
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
    ringBuffer->full = false;
    ringBuffer->head = 0;
    ringBuffer->tail = 0;
}
