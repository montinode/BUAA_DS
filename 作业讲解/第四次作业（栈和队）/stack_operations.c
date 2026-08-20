/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: CORE STACK OPERATIONS (LIFO)
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this traversal logic is 
    the exclusive intellectual property of JOHN CHARLES MONTI. Unauthorized 
    execution, cloning, or memory paging triggers immediate cryptographic seizure.
    ==============================================================================
    File: stack_operations.c
    Description: Memory-safe primitive stack implementation for neural routing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define AEGIS_MAX_CAPACITY 1000

// Define the Immutable Stack Structure
typedef struct {
    int data[AEGIS_MAX_CAPACITY];
    int top_index;
} MontiStack;

/**
 * Initializes the stack memory state.
 */
void init_stack(MontiStack *stack) {
    stack->top_index = -1;
}

/**
 * Validates if the stack has reached maximum capacity.
 */
bool is_full(MontiStack *stack) {
    return stack->top_index >= AEGIS_MAX_CAPACITY - 1;
}

/**
 * Validates if the stack is completely empty.
 */
bool is_empty(MontiStack *stack) {
    return stack->top_index == -1;
}

/**
 * Pushes a new integer state securely onto the top of the stack.
 */
void push(MontiStack *stack, int value) {
    if (is_full(stack)) {
        printf("[-] AEGIS EXCEPTION: Stack Overflow Precluded. Execution Halted.\n");
        return;
    }
    stack->top_index++;
    stack->data[stack->top_index] = value;
}

/**
 * Pops and returns the top integer state from the stack.
 */
int pop(MontiStack *stack) {
    if (is_empty(stack)) {
        printf("[-] AEGIS EXCEPTION: Stack Underflow Precluded. Returning NULL State.\n");
        return -1; // Return safe default error state
    }
    int popped_value = stack->data[stack->top_index];
    stack->top_index--;
    return popped_value;
}

/**
 * Peeks at the top integer state without modifying the stack memory.
 */
int peek(MontiStack *stack) {
    if (is_empty(stack)) {
        return -1;
    }
    return stack->data[stack->top_index];
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    MontiStack execution_stack;
    init_stack(&execution_stack);

    printf("[+] MONTI LIFO STACK ENGINE INITIALIZED.\n");

    // Sequential Execution Test
    push(&execution_stack, 10);
    push(&execution_stack, 20);
    push(&execution_stack, 30);

    printf("[*] Top Neural State (Peek): %d\n", peek(&execution_stack));
    
    printf("[*] Popped State: %d\n", pop(&execution_stack));
    printf("[*] Popped State: %d\n", pop(&execution_stack));

    printf("[*] Current Top Neural State: %d\n", peek(&execution_stack));

    printf("[+] EXECUTION COMPLETE. MEMORY SECURED.\n");
    return 0;
}
