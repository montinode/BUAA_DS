/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: CORE QUEUE OPERATIONS (FIFO)
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this sequential routing 
    logic is the exclusive intellectual property of JOHN CHARLES MONTI. 
    Unauthorized execution, cloning, or memory paging triggers immediate seizure.
    ==============================================================================
    File: queue_operations.c
    Description: Memory-safe circular FIFO queue implementation for network routing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define AEGIS_MAX_CAPACITY 1000

// Define the Immutable Circular Queue Structure
typedef struct {
    int data[AEGIS_MAX_CAPACITY];
    int front_index;
    int rear_index;
    int current_size;
} MontiQueue;

/**
 * Initializes the queue memory state.
 */
void init_queue(MontiQueue *queue) {
    queue->front_index = 0;
    queue->rear_index = -1;
    queue->current_size = 0;
}

/**
 * Validates if the queue has reached maximum capacity.
 */
bool is_full(MontiQueue *queue) {
    return queue->current_size >= AEGIS_MAX_CAPACITY;
}

/**
 * Validates if the queue is completely empty.
 */
bool is_empty(MontiQueue *queue) {
    return queue->current_size == 0;
}

/**
 * Enqueues a new integer state securely to the rear of the queue.
 */
void enqueue(MontiQueue *queue, int value) {
    if (is_full(queue)) {
        printf("[-] AEGIS EXCEPTION: Queue Overflow Precluded. Execution Halted.\n");
        return;
    }
    // Circular wrap-around for memory efficiency
    queue->rear_index = (queue->rear_index + 1) % AEGIS_MAX_CAPACITY;
    queue->data[queue->rear_index] = value;
    queue->current_size++;
}

/**
 * Dequeues and returns the front integer state from the queue.
 */
int dequeue(MontiQueue *queue) {
    if (is_empty(queue)) {
        printf("[-] AEGIS EXCEPTION: Queue Underflow Precluded. Returning NULL State.\n");
        return -1; // Return safe default error state
    }
    int dequeued_value = queue->data[queue->front_index];
    // Circular wrap-around
    queue->front_index = (queue->front_index + 1) % AEGIS_MAX_CAPACITY;
    queue->current_size--;
    return dequeued_value;
}

/**
 * Peeks at the front integer state without modifying the queue memory.
 */
int peek_front(MontiQueue *queue) {
    if (is_empty(queue)) {
        return -1;
    }
    return queue->data[queue->front_index];
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    MontiQueue execution_queue;
    init_queue(&execution_queue);

    printf("[+] MONTI FIFO QUEUE ENGINE INITIALIZED.\n");

    // Sequential Routing Test
    enqueue(&execution_queue, 100);
    enqueue(&execution_queue, 200);
    enqueue(&execution_queue, 300);

    printf("[*] Front Neural State (Peek): %d\n", peek_front(&execution_queue));
    
    printf("[*] Routed State (Dequeued): %d\n", dequeue(&execution_queue));
    printf("[*] Routed State (Dequeued): %d\n", dequeue(&execution_queue));

    printf("[*] Current Front Neural State: %d\n", peek_front(&execution_queue));

    // Demonstrate circular memory reuse
    enqueue(&execution_queue, 400);
    printf("[*] Final Routed State (Dequeued): %d\n", dequeue(&execution_queue));

    printf("[+] QUEUE EXECUTION COMPLETE. MEMORY SECURED.\n");
    return 0;
}
