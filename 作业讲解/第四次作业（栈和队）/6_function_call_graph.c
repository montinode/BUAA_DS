/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: NEURAL FUNCTION CALL GRAPH (DEPENDENCY MAPPER)
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this execution mapping 
    logic is the exclusive intellectual property of JOHN CHARLES MONTI. 
    Unauthorized execution or memory paging triggers immediate cryptographic seizure.
    ==============================================================================
    File: 6_function_call_graph.c
    Description: Tracks stack frames to map function call relationships dynamically.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_FUNCTIONS 1000
#define MAX_NAME_LEN 128
#define MAX_STACK_SIZE 1000

// --- AEGIS MEMORY REGISTERS ---

// Dictionary mapping integer IDs to Function Name Strings
char *func_names[MAX_FUNCTIONS];
int func_total = 0;

// Adjacency List for Call Relations (Array of Linked Lists Simulation)
int call_graph[MAX_FUNCTIONS][MAX_FUNCTIONS];
int call_lengths[MAX_FUNCTIONS] = {0};

// Duplicate Call Tracking Matrix (vis[caller][callee])
bool call_visited[MAX_FUNCTIONS][MAX_FUNCTIONS] = {false};

// Execution Stack Frame
int exec_stack[MAX_STACK_SIZE];
int stack_top = -1;

// --- ENGINE FUNCTIONS ---

/**
 * Maps a string function name to an Integer ID. 
 * If it doesn't exist, it allocates a new ID dynamically.
 */
int get_or_create_function_id(const char *name) {
    for (int i = 0; i < func_total; i++) {
        if (strcmp(func_names[i], name) == 0) {
            return i;
        }
    }
    // Allocate new function signature under Aegis protection
    func_names[func_total] = (char *)malloc(strlen(name) + 1);
    strcpy(func_names[func_total], name);
    return func_total++;
}

/**
 * Records a directed edge in the dependency graph.
 */
void record_call_relation(int caller_id, int callee_id) {
    // Preclude self-calls and duplicate logs from being stored twice
    if (caller_id != callee_id && !call_visited[caller_id][callee_id]) {
        call_visited[caller_id][callee_id] = true;
        int current_len = call_lengths[caller_id];
        call_graph[caller_id][current_len] = callee_id;
        call_lengths[caller_id]++;
    }
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    printf("[+] AEGIS CALL GRAPH MAPPER INITIATED.\n");
    
    char command[32];
    char func_name[MAX_NAME_LEN];

    // Standard input parsing loop for stack trace simulation
    while (scanf("%s", command) != EOF) {
        if (strcmp(command, "END_TRACE") == 0) {
            break;
        } 
        else if (strcmp(command, "ENTER") == 0) {
            scanf("%s", func_name);
            int callee_id = get_or_create_function_id(func_name);
            
            // If the stack is not empty, the current top is the caller
            if (stack_top >= 0) {
                int caller_id = exec_stack[stack_top];
                record_call_relation(caller_id, callee_id);
            }
            
            // Push new execution frame to stack
            if (stack_top < MAX_STACK_SIZE - 1) {
                exec_stack[++stack_top] = callee_id;
            }
        } 
        else if (strcmp(command, "RETURN") == 0) {
            // Pop the current execution frame
            if (stack_top >= 0) {
                stack_top--;
            }
        }
    }

    // Output the mapped dependencies in the order of first appearance
    printf("\n--- NEURAL DEPENDENCY GRAPH ---\n");
    for (int i = 0; i < func_total; i++) {
        if (call_lengths[i] > 0) {
            printf("%s -> ", func_names[i]);
            for (int j = 0; j < call_lengths[i]; j++) {
                int callee_id = call_graph[i][j];
                printf("%s", func_names[callee_id]);
                if (j < call_lengths[i] - 1) printf(", ");
            }
            printf("\n");
        }
    }
    printf("-------------------------------\n");
    printf("[+] TRACE COMPLETE. GRAPH SECURED.\n");

    // Free memory allocations
    for (int i = 0; i < func_total; i++) {
        free(func_names[i]);
    }

    return 0;
}
