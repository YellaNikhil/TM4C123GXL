#include "queue.h"

void queue_init(queue_t *queue){
    queue->head = 0;
    queue->tail = 0;
    queue->size = 0; // Initialize size to 0
    for (uint32_t i = 0; i < QUEUE_SIZE; i++)
        queue->data[i] = '\0'; // Initialize all elements to zero   
}

bool queue_is_empty(queue_t *queue) {
    return queue->head == queue->tail;
}

bool queue_is_full(queue_t *queue){
    return queue->size == QUEUE_SIZE; // Check if the queue is full
}

bool queue_enqueue(queue_t *queue, uint8_t value){
    if (queue_is_full(queue)) {
        return false; // Queue is full, cannot enqueue
    }
    queue->data[queue->tail] = value;
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;

    // Disable interrupts to prevent premature access to the queue
    // This is a critical section to ensure thread safety
    /* Atomic operation */
    // __ASM volatile ("cpsid i" : : : "memory"); // Disable interrupts
    uint32_t masking_state = __get_PRIMASK(); // Save current interrupt state

    __disable_irq(); // Disable interrupts
    
    queue->size++; // Increment size if tracking is needed

    __set_PRIMASK(masking_state); // Restore previous interrupt state
    
    return true; // Successfully enqueued
}

bool queue_dequeue(queue_t *queue, uint8_t *value){
    if (queue_is_empty(queue)) {
        return false; // Queue is empty, cannot dequeue
    }
    *value = queue->data[queue->head];
    queue->data[queue->head] = '\0'; // Optional: Clear the dequeued value
    queue->head = (queue->head + 1) % QUEUE_SIZE;

    // Disable interrupts to prevent premature access to the queue
    // This is a critical section to ensure thread safety
    /* Atomic operation */
    // __ASM volatile ("cpsid i" : : : "memory"); // Disable interrupts
    uint32_t masking_state = __get_PRIMASK(); // Save current interrupt state

    __disable_irq(); // Disable interrupts
    
    queue->size--; // Increment size if tracking is needed

    __set_PRIMASK(masking_state); // Restore previous interrupt state

    return true; // Successfully dequeued
}

uint32_t queue_size(queue_t *queue){
    return (queue->tail - queue->head + QUEUE_SIZE) % QUEUE_SIZE; // Calculate the size of the queue
}