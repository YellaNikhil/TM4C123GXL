#ifndef _QUEUE_H_
#define _QUEUE_H_   

#include <stdint.h>
#include <stdbool.h>
#include "gpio_registers.h"


#define QUEUE_SIZE 256

typedef struct __attribute__((packed)) {
    uint8_t data[QUEUE_SIZE];
    uint32_t head;
    uint32_t tail;
    uint8_t size; // Optional: to keep track of the current size
} queue_t;

void queue_init(queue_t *queue);
bool queue_is_empty(queue_t *queue);
bool queue_is_full(queue_t *queue);
bool queue_enqueue(queue_t *queue, uint8_t value);
bool queue_dequeue(queue_t *queue, uint8_t *value);

#endif // _QUEUE_H_