#include <gtest/gtest.h>
#include <cstdlib>
#include <stdint.h>

extern "C" {
#include "../ring_buffer.h"
}

#define EXAMPLE_BUFFER_ADDRESS 10   /// 32-bit address in flash MEMORY
#define EXAMPLE_BUFFER_SIZE 3
#define NULL_BUFFER_SIZE 0
#define EXAMPLE_DATA 9

class TestRingBuffer : public ::testing::Test {
public:
    TestRingBuffer() {
        ringBuffer = new RingBuffer;
    }
    
    ~TestRingBuffer() {
        delete(ringBuffer);
    }
    
protected:
    uint16_t data = EXAMPLE_DATA;
    uint32_t addr;  
    RingBuffer *ringBuffer;
};


// TESTS

// Buffer initialization tests 

TEST_F(TestRingBuffer, correctInitialization) {
    ASSERT_EQ(BUFFER_SUCCESS, BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE));
}


TEST_F(TestRingBuffer, initializationWithNullBufferSize) {
    ASSERT_EQ(BUFFER_ERROR, BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, NULL_BUFFER_SIZE));
}

TEST_F(TestRingBuffer, initializationWithNullRingBuffer) {
    ASSERT_EQ(BUFFER_ERROR, BUFFER_init(NULL, EXAMPLE_BUFFER_ADDRESS, NULL_BUFFER_SIZE));
}


// Buffer write tests

TEST_F(TestRingBuffer, writeDataInBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(BUFFER_SUCCESS, BUFFER_insert(ringBuffer, data));
}

TEST_F(TestRingBuffer, writeDataInNullBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_insert(NULL, data));
}

// Buffer read tests

TEST_F(TestRingBuffer, getLastElementFromEmptyBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_getLast(ringBuffer, &data));
}

TEST_F(TestRingBuffer, getLastElementFromNotEmptyBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(BUFFER_SUCCESS, BUFFER_getLast(ringBuffer, &data));
}

TEST_F(TestRingBuffer, getFirstElementFromEmptyBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(BUFFER_ERROR, BUFFER_getFirst(ringBuffer, &data));
}

TEST_F(TestRingBuffer, getFirstElementFromNotEmptyBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(BUFFER_SUCCESS, BUFFER_getFirst(ringBuffer, &data));
}

// Buffer state tests (full or empty)

TEST_F(TestRingBuffer, isBufferEmptyWhenEmpty) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(true, BUFFER_isEmpty(ringBuffer));
}

TEST_F(TestRingBuffer, isBufferEmptyWhenNotEmpty) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(false, BUFFER_isEmpty(ringBuffer));
}

TEST_F(TestRingBuffer, isBufferEmptyWhenFull) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(false, BUFFER_isEmpty(ringBuffer));
}

TEST_F(TestRingBuffer, isBufferFullWhenEmpty) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(false, BUFFER_isFull(ringBuffer));
}

TEST_F(TestRingBuffer, isBufferFullWhenNotFull) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(false, BUFFER_isFull(ringBuffer));
}

TEST_F(TestRingBuffer, isBufferFullWhenFull) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(true, BUFFER_isFull(ringBuffer));
}

// Buffer state tests (buffer size and elemets number)

TEST_F(TestRingBuffer, isSizeCorrect) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(EXAMPLE_BUFFER_SIZE, BUFFER_getSize(ringBuffer));
}

TEST_F(TestRingBuffer, isElemetsNumberCorrect) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(EXAMPLE_BUFFER_SIZE, BUFFER_getSize(ringBuffer));
}

TEST_F(TestRingBuffer, isElemetsNumberCorrectWhenRewrite) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    BUFFER_insert(ringBuffer, data);
    ASSERT_EQ(EXAMPLE_BUFFER_SIZE, BUFFER_getSize(ringBuffer));
}

TEST_F(TestRingBuffer, isElementsNumberNullAfterInitialization) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(NULL_BUFFER_SIZE, BUFFER_getCount(ringBuffer));
}


// Buffer state tests (head and tail indices)
 
 TEST_F(TestRingBuffer, isHeadIndexNullAfterInitialization) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(0, BUFFER_getCurrentHeadIndex(ringBuffer));
}

 TEST_F(TestRingBuffer, isTailIndexNullAfterInitialization) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    ASSERT_EQ(0, BUFFER_getCurrentTailIndex(ringBuffer));
}

 TEST_F(TestRingBuffer, isTailandHeadIndicesEqualAfterFlush) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(ringBuffer, data);
    BUFFER_flush(ringBuffer);
    ASSERT_EQ(BUFFER_getCurrentHeadIndex(ringBuffer), BUFFER_getCurrentTailIndex(ringBuffer));
}

// Buffer flush tests

TEST_F(TestRingBuffer, fulshNotEmptyBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_insert(NULL, data);
    BUFFER_flush(ringBuffer);
    ASSERT_EQ(true, BUFFER_isEmpty(ringBuffer));
}

TEST_F(TestRingBuffer, fulshEmptyBuffer) {
    BUFFER_init(ringBuffer, EXAMPLE_BUFFER_ADDRESS, EXAMPLE_BUFFER_SIZE);
    BUFFER_flush(ringBuffer);
    ASSERT_EQ(true, BUFFER_isEmpty(ringBuffer));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
