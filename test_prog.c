#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer.h"

#define EXAMPLE_BUFFER_SIZE 5

enum menuActions {
    EXIT,
    INSERT,
    GET_LAST,
    GET_FIRST,
    GET_ALL_FROM_HEAD,
    GET_ALL_FROM_TAIL,
    INFO
};

const char message[] = "Error! Buffer is empty!\n";

void TEST_printRingBufferInfo(RingBuffer *ringBuffer);
void TEST_printBuffer(uint16_t *destBuffer, int size);

int main(int argc, char **argv) {
    uint16_t data;
    uint16_t *buffer = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint16_t));
    uint16_t *destBuffer = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint16_t));
    RingBuffer *ringBuffer = malloc(sizeof(*ringBuffer));

    BUFFER_init(ringBuffer, buffer, EXAMPLE_BUFFER_SIZE);

    int menuNumber;
    for (;;) {
        fputs("0 - Exit\n1 - Insert\n2 - Get last\n3 - Get first\n4 - Get all from head\n5 - Get all from tail\n6 - Info\n> ", stdout);
        scanf("%d", &menuNumber);
        switch (menuNumber) {
            case EXIT: {
                free(buffer);
                free(ringBuffer);
                return 0;
                break;
            }
            case INSERT: {
                fputs("> ", stdout);
                scanf("%hd", &data);
                BUFFER_insert(ringBuffer, data);
                break;
            }
            case GET_FIRST: {
                BUFFER_getFirst(ringBuffer, &data) ? fputs(message, stdout) : printf("%hd\n", data);
                break;
            }
            case GET_LAST: {
                BUFFER_getLast(ringBuffer, &data) ? fputs(message, stdout) : printf("%hd\n", data);
                break;
            }
            case GET_ALL_FROM_HEAD: {
                BUFFER_getAllFromHead(ringBuffer, destBuffer, EXAMPLE_BUFFER_SIZE) ? fputs(message, stdout) : TEST_printBuffer(destBuffer, EXAMPLE_BUFFER_SIZE);
                break;
            }
            case GET_ALL_FROM_TAIL: {
                BUFFER_getAllFromTail(ringBuffer, destBuffer, EXAMPLE_BUFFER_SIZE) ? fputs(message, stdout) : TEST_printBuffer(destBuffer, EXAMPLE_BUFFER_SIZE);
                break;
            }
            case INFO: {
                TEST_printRingBufferInfo(ringBuffer);
                break;
            }
            default: {
                fputs("An invalid menu number!\n", stdout);
            }
        }
    }
    
    return 0;
}

void TEST_printRingBufferInfo(RingBuffer *ringBuffer)
{
    printf("********************\n");
    printf("   Size       : %d\n", ringBuffer->size);
    printf("   Count      : %d\n", BUFFER_getCount(ringBuffer));
    printf("   Head index : %d\n", ringBuffer->head);
    printf("   Tail index : %d\n", ringBuffer->tail);
    printf("   is full    : %d\n", BUFFER_isFull(ringBuffer));
    printf("   is empty   : %d\n", BUFFER_isEmpty(ringBuffer));
    printf("********************\n");
}

void TEST_printBuffer(uint16_t *destBuffer, int size) {
    printf("> ");
    for (int i = 0; i < size; i++) {
            printf("%hd ", destBuffer[i]);
    }
    printf("\n");
}
