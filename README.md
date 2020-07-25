# Ring Buffer API

A simple C implementation for a ring (circular) buffer.

## API

````c
int BUFFER_init(RingBuffer *ringBuffer, uint16_t *buffer, int size);
````
````c
int BUFFER_insert(RingBuffer *ringBuffer, uint16_t data);
````
````c
int BUFFER_getFirst(RingBuffer *ringBuffer, uint16_t *data);
````
````c
int BUFFER_getLast(RingBuffer *ringBuffer, uint16_t *data);
````
````c
int BUFFER_getCurrentHeadIndex(RingBuffer *ringBuffer);
````
````c
int BUFFER_getCurrentTailIndex(RingBuffer *ringBuffer);
````
````c
int BUFFER_getSize(RingBuffer *ringBuffer);
````
````c
int BUFFER_getCount(RingBuffer *ringBuffer);
````
````c
int BUFFER_isFull(RingBuffer *ringBuffer);
````
````c
int BUFFER_isEmpty(RingBuffer *ringBuffer);
````
````c
void BUFFER_flush(RingBuffer *ringBuffer);
````



#### Definition of ring buffer structure

```c
typedef struct RingBuffer {
    uint16_t *buffer;
    int head;
    int tail;
    int size;
    bool full;
} RingBuffer;
```
## Build

To compile this project use bash script:
```
./build
```

## Author

[Khalyamin Vladimir](https://github.com/vkhalyamin) &ndash; vkhalyamin@protonmail.com

## License

This project is licensed under the MIT License &ndash; see the LICENSE file for details.

