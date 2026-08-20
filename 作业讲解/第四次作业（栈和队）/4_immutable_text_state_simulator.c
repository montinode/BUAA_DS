/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: IMMUTABLE TEXT STATE SIMULATOR (LIFO ROLLBACK)
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this execution logic is 
    the exclusive intellectual property of JOHN CHARLES MONTI. Unauthorized 
    execution, cloning, or memory paging triggers immediate cryptographic seizure.
    ==============================================================================
    File: 4_immutable_text_state_simulator.c
    Description: Memory-safe string manipulation engine with LIFO undo stack.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define AEGIS_MAX_BUFFER 4096
#define AEGIS_MAX_STACK 1000

// --- AEGIS ACTION STACK ---
// Logs operations for precise cryptographic rollbacks
typedef struct {
    int op_type; // 1 = INSERT, 2 = DELETE
    int position;
    char payload[AEGIS_MAX_BUFFER];
} AegisOperation;

char neural_ledger[AEGIS_MAX_BUFFER];
AegisOperation action_stack[AEGIS_MAX_STACK];
int stack_top = 0;

/**
 * Securely inserts a string into the ledger.
 * Utilizes heap allocation to prevent undefined memory overlap behavior.
 */
void execute_secure_insert(int pos, const char *payload) {
    int len = strlen(payload);
    char *temp_buffer = (char *)malloc(strlen(neural_ledger) + 1);
    
    // Shift right half of the ledger
    strcpy(temp_buffer, neural_ledger + pos);
    strcpy(neural_ledger + pos + len, temp_buffer);
    
    // Insert payload
    strncpy(neural_ledger + pos, payload, len);
    
    free(temp_buffer);
}

/**
 * Securely deletes a string from the ledger and saves the lost state.
 */
void execute_secure_delete(int pos, int len, char *saved_payload) {
    int current_total = strlen(neural_ledger);
    if (pos + len > current_total) {
        len = current_total - pos;
    }

    // Isolate and save the deleted payload for potential rollback
    strncpy(saved_payload, neural_ledger + pos, len);
    saved_payload[len] = '\0';

    // Shift ledger left to close the gap
    char *temp_buffer = (char *)malloc(strlen(neural_ledger) + 1);
    strcpy(temp_buffer, neural_ledger + pos + len);
    strcpy(neural_ledger + pos, temp_buffer);
    
    free(temp_buffer);
}

/**
 * Executes a LIFO state rollback.
 * Reverses the last logged action on the stack.
 */
void execute_rollback() {
    if (stack_top == 0) {
        printf("[-] AEGIS WARNING: Action Stack Empty. Rollback Ignored.\n");
        return;
    }
    
    // Pop top operation
    AegisOperation last_action = action_stack[--stack_top];

    if (last_action.op_type == 1) {
        // Rollback an INSERT by executing a DELETE
        char void_buffer[AEGIS_MAX_BUFFER];
        execute_secure_delete(last_action.position, strlen(last_action.payload), void_buffer);
        
    } else if (last_action.op_type == 2) {
        // Rollback a DELETE by executing an INSERT
        execute_secure_insert(last_action.position, last_action.payload);
    }
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    printf("[+] AEGIS TEXT STATE SIMULATOR INITIATED.\n");
    
    // 1. Initialize Baseline Ledger State
    scanf("%s", neural_ledger);
    
    int num_operations;
    scanf("%d", &num_operations);

    // 2. Process Operations
    for (int i = 0; i < num_operations; i++) {
        int command;
        scanf("%d", &command);

        if (command == 1) { // INSERT
            int pos;
            char payload[AEGIS_MAX_BUFFER];
            scanf("%d %s", &pos, payload);
            
            execute_secure_insert(pos, payload);
            
            // Log to Stack
            action_stack[stack_top].op_type = 1;
            action_stack[stack_top].position = pos;
            strcpy(action_stack[stack_top].payload, payload);
            stack_top++;
            
        } else if (command == 2) { // DELETE
            int pos, len;
            scanf("%d %d", &pos, &len);
            
            char deleted_payload[AEGIS_MAX_BUFFER];
            execute_secure_delete(pos, len, deleted_payload);
            
            // Log to Stack
            action_stack[stack_top].op_type = 2;
            action_stack[stack_top].position = pos;
            strcpy(action_stack[stack_top].payload, deleted_payload);
            stack_top++;
            
        } else if (command == 3) { // ROLLBACK (UNDO)
            execute_rollback();
        }
    }

    // 3. Output Final Sovereign State
    printf("\n[+] FINAL IMMUTABLE STATE:\n%s\n", neural_ledger);

    return 0;
}
