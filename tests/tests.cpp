#include <gtest/gtest.h>
#include <stdint.h>
#include <cstdlib>

extern "C" {
#include "../ring_buffer.c"
}

#define BUFFER_SIZE 5
#define NULL_BUFFER_SIZE 0

    
// Initialization tests

TEST(BufferInitialization, normal) {
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    ASSERT_EQ(BUFFER_SUCCESS,  BUFFER_init(ringBuffer, buffer, BUFFER_SIZE));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferInitialization, withNULLringBuffer) {
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = NULL;
    ASSERT_EQ(BUFFER_ERROR,  BUFFER_init(ringBuffer, buffer, BUFFER_SIZE));
    free(ringBuffer);
}

TEST(BufferInitialization, withNULLbuffer) {
    uint16_t *buffer = NULL;
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    ASSERT_EQ(BUFFER_ERROR,  BUFFER_init(ringBuffer, buffer, BUFFER_SIZE));
    free(ringBuffer);
}

TEST(BufferInitialization, withNULLbufferSize) {
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    ASSERT_EQ(BUFFER_ERROR,  BUFFER_init(ringBuffer, buffer, NULL_BUFFER_SIZE));
    free(buffer);
    free(ringBuffer);
}


// Buffer insert tests

TEST(BufferInsert, simpleInsert) {
    uint16_t data = 9;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(BUFFER_SUCCESS, BUFFER_insert(ringBuffer, data));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferInsert, withNULLbuffer) {
    uint16_t data = 9;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = NULL;
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_insert(ringBuffer, data));
    free(buffer);
    free(ringBuffer);
}

// Buffer extract tests

TEST(BufferExtract, getFirstElementFromEmptyBuffer) {
    uint16_t data;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_getFirst(ringBuffer, &data));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferExtract, getLastElementFromEmptyBuffer) {
    uint16_t data;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_getLast(ringBuffer, &data));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferExtract, getFirstElement) {
    uint16_t data;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_getFirst(ringBuffer, &data));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferExtract, getLastElement) {
    uint16_t data;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_getLast(ringBuffer, &data));
    free(buffer);
    free(ringBuffer);
}

// Buffer indices tests

TEST(BufferIndex, indicesAfterInitialization) {
    /* After initialization -> tail = head */
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(BUFFER_getCurrentHeadIndex(ringBuffer), BUFFER_getCurrentTailIndex(ringBuffer));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferIndex, indicesFullBuffer) {
    /* Buffer full -> tail = head */
    uint16_t data = 9;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, 3);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(BUFFER_getCurrentHeadIndex(ringBuffer), BUFFER_getCurrentTailIndex(ringBuffer));
    free(buffer);
    free(ringBuffer);
}


// Buffer state tests

TEST(BufferState, emptyAfterInitialization) {
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(true, BUFFER_isEmpty(ringBuffer));
    free(buffer);
    free(ringBuffer);
}
 

 TEST(BufferState, fullAfterInitialization) {
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    ASSERT_EQ(false, BUFFER_isFull(ringBuffer));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferState, empty) {
    uint16_t data = 9;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(false, BUFFER_isEmpty(ringBuffer));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferState, full) {
    uint16_t data = 9;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, 3);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(true, BUFFER_isFull(ringBuffer));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferState, bufferSize) {
    uint16_t data = 9;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(BUFFER_SIZE,  BUFFER_getSize(ringBuffer));
    free(buffer);
    free(ringBuffer);
}

TEST(BufferState, getCount) {
    uint16_t data = 9;
    uint16_t *buffer = (uint16_t*)malloc(BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = (RingBuffer*)malloc(sizeof(*ringBuffer));
    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(2,  BUFFER_getCount(ringBuffer));
    free(buffer);
    free(ringBuffer);
}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
   	return 0;
}