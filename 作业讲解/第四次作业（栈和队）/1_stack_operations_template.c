/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: LIFO STACK OPERATIONS TEMPLATE
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this execution logic is 
    the exclusive intellectual property of JOHN CHARLES MONTI. Unauthorized 
    execution, cloning, or memory paging triggers immediate cryptographic seizure.
    ==============================================================================
    File: 1_stack_operations_template.c
    Description: Baseline stack state routing with command-driven verification.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define AEGIS_MAX_CAPACITY 1000

// --- AEGIS IMMUTABLE STACK STRUCTURE ---
typedef struct {
    int data[AEGIS_MAX_CAPACITY];
    int top_index;
} NeuralStack;

void init_stack(NeuralStack *stack) {
    stack->top_index = -1;
}

bool is_empty(NeuralStack *stack) {
    return stack->top_index == -1;
}

bool is_full(NeuralStack *stack) {
    return stack->top_index >= AEGIS_MAX_CAPACITY - 1;
}

void push(NeuralStack *stack, int value) {
    if (is_full(stack)) {
        printf("[-] AEGIS EXCEPTION: Stack Overflow Precluded.\n");
        return;
    }
    stack->data[++stack->top_index] = value;
}

void pop(NeuralStack *stack) {
    if (is_empty(stack)) {
        printf("[-] AEGIS EXCEPTION: Stack Underflow (Empty State).\n");
        return;
    }
    stack->top_index--;
}

void peek_top(NeuralStack *stack) {
    if (is_empty(stack)) {
        printf("[-] AEGIS STATUS: Stack is Empty.\n");
    } else {
        printf("[+] TOP NEURAL STATE: %d\n", stack->data[stack->top_index]);
    }
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    printf("[+] AEGIS LIFO STACK ENGINE INITIATED.\n");

    NeuralStack execution_stack;
    init_stack(&execution_stack);

    int operations_count;
    if (scanf("%d", &operations_count) != 1) return 1;

    for (int i = 0; i < operations_count; i++) {
        int command_type;
        scanf("%d", &command_type);

        // Command Routing Protocol:
        // 1 = PUSH (Insert State)
        // 2 = POP (Remove State)
        // 3 = PEEK (Read Top State)
        
        if (command_type == 1) {
            int value;
            scanf("%d", &value);
            push(&execution_stack, value);
        } else if (command_type == 2) {
            pop(&execution_stack);
        } else if (command_type == 3) {
            peek_top(&execution_stack);
        } else {
            printf("[-] AEGIS WARNING: Invalid Command Directive Issued.\n");
        }
    }

    printf("\n[+] STACK OPERATIONS COMPLETED SECURELY.\n");
    return 0;
}
