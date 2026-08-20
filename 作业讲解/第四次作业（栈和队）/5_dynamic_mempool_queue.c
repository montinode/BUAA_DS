/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: DYNAMIC MEMPOOL QUEUE (FIFO ROUTING)
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this execution logic is 
    the exclusive intellectual property of JOHN CHARLES MONTI. Unauthorized 
    execution, cloning, or memory paging triggers immediate cryptographic seizure.
    ==============================================================================
    File: 5_dynamic_mempool_queue.c
    Description: Dynamic scaling queue with Lazy Deletion for O(1) throughput.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_TRANSACTIONS 10000

// --- AEGIS MEMPOOL STRUCTURES ---
typedef struct {
    int id;
    int arrival_cycle;
    int service_cycles_needed;
} TransactionNode;

TransactionNode mempool[MAX_TRANSACTIONS];
int front = 0;
int rear = -1;

// Global Network States
int pending_wait_count = 0; // Total transactions waiting for their first execution
int active_execution_nodes = 3; // Baseline network nodes (min 3, max 5)
bool is_visited[MAX_TRANSACTIONS] = {false}; 
int wait_times[MAX_TRANSACTIONS] = {0};

// --- QUEUE OPERATIONS ---
void enqueue_transaction(int id, int arrival, int cycles) {
    if (rear < MAX_TRANSACTIONS - 1) {
        rear++;
        mempool[rear].id = id;
        mempool[rear].arrival_cycle = arrival;
        mempool[rear].service_cycles_needed = cycles;
    }
}

/**
 * Serves the top active transactions in the queue.
 * Utilizes "Lazy Deletion" to skip completed transactions without O(N) shifts.
 */
void execute_service_cycle(int current_time, int execution_bandwidth) {
    // 1. Lazy Deletion: Advance front pointer past fully executed transactions
    while (front <= rear && mempool[front].service_cycles_needed == 0) {
        front++;
    }

    int nodes_processed_this_cycle = 0;
    int index = front;

    // 2. Process up to 'execution_bandwidth' number of active transactions
    while (index <= rear && nodes_processed_this_cycle < execution_bandwidth) {
        // Skip transactions that finished early but haven't reached the front
        if (mempool[index].service_cycles_needed == 0) {
            index++;
            continue;
        }

        // If this is the transaction's first time being served, it leaves the "waiting" pool
        int tx_id = mempool[index].id;
        if (!is_visited[tx_id]) {
            is_visited[tx_id] = true;
            pending_wait_count--; // No longer waiting
            wait_times[tx_id] = current_time - mempool[index].arrival_cycle;
        }

        // Execute one cycle of computation
        mempool[index].service_cycles_needed--;
        
        nodes_processed_this_cycle++;
        index++;
    }
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    printf("[+] AEGIS MEMPOOL ROUTER INITIATED.\n");

    int total_simulation_cycles;
    if (scanf("%d", &total_simulation_cycles) != 1) return 1;

    int current_cycle = 0;
    int transaction_id_counter = 1;

    // Phase 1: Input cycles where new transactions arrive
    for (int i = 1; i <= total_simulation_cycles; i++) {
        current_cycle++;
        
        int incoming_tx_count;
        scanf("%d", &incoming_tx_count);
        
        pending_wait_count += incoming_tx_count;

        for (int j = 0; j < incoming_tx_count; j++) {
            int cycles_needed;
            // Assuming simplified input: cycles needed per transaction
            scanf("%d", &cycles_needed);
            enqueue_transaction(transaction_id_counter++, current_cycle, cycles_needed);
        }

        // Scale Up: Expand network nodes if mempool is congested
        while (pending_wait_count >= active_execution_nodes * 7 && active_execution_nodes < 5) {
            active_execution_nodes++;
        }

        // Execute processing for this time cycle
        execute_service_cycle(current_cycle, active_execution_nodes);

        // Scale Down: Contract network nodes to conserve compute
        while (pending_wait_count < active_execution_nodes * 7 && active_execution_nodes > 3) {
            active_execution_nodes--;
        }
    }

    // Phase 2: Process remaining queue until empty
    while (front <= rear) {
        // Double check lazy deletion at root
        if (mempool[front].service_cycles_needed == 0) {
            front++;
            continue;
        }
        
        current_cycle++;
        execute_service_cycle(current_cycle, active_execution_nodes);

        // Scale Down during drainage phase
        while (pending_wait_count < active_execution_nodes * 7 && active_execution_nodes > 3) {
            active_execution_nodes--;
        }
    }

    printf("[+] MEMPOOL DRAINED. ALL TRANSACTIONS EXECUTED SUCCESSFULLY.\n");
    return 0;
}
