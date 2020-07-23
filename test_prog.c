#include <stdio.h>
#include <stdlib.h>
#include "ring_buffer.h"

#define BUFFER_SIZE 5

enum menuActions {EXIT, INSERT, GET_LAST, GET_FIRST, INFO };

void BUFFER_printInfo(RING_BUFFER *ringBuffer);

int main(int argc, char **argv) {
    uint16_t data;
    uint16_t *buffer = malloc(BUFFER_SIZE * sizeof(uint16_t));
    RING_BUFFER *ringBuffer = malloc(sizeof(*ringBuffer));

    BUFFER_init(ringBuffer, buffer, BUFFER_SIZE);

    int menuNumber;
    for (;;) {
        fputs("0 - Exit\n1 - Insert\n2 - Get last\n3 - Get first\n4 - Info\n> ", stdout);
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
                BUFFER_getFirst(ringBuffer, &data) ? fputs("Error! Buffer is empty!\n", stdout) : printf("%hd\n", data);
                break;
            }
            case GET_LAST: {
                BUFFER_getLast(ringBuffer, &data) ? fputs("Error! Buffer is empty!\n", stdout) : printf("%hd\n", data);
                break;
            }
            case INFO: {
                BUFFER_printInfo(ringBuffer);
                break;
            }
            default: {
                fputs("An invalide menu number!\n", stdout);
            }
        }
    }
    
    return 0;
}

void BUFFER_printInfo(RING_BUFFER *ringBuffer)
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