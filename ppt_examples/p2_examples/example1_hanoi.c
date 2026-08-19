/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: TOWERS OF HANOI RECURSIVE SOLVER (US ENGLISH)
    DEVELOPMENT NODE: Monti11.studio.ai (MONTIDROID.COM)
    AUTHORIZATION: JOHN CHARLES MONTI EXCLUSIVE
    STANDARD: MONTI_ANSI_F841005
    VALIDATION: JOHNCHARLESMONTI.COM?IDENTITY
    CERTIFICATE: cert_monti_1787175335749_nu0ph
    SIGNATURE: 0xd1c8694c3543fbf08dbd47cfaf2ca2aa72cc2dcfb1b0af4fac3881b9ca173208
    ==============================================================================
    File: example1_hanoi.c
    Description: Recursive state-transition execution model for N-disk transfers.
*/

#include <stdio.h>
#include <stdint.h>

static uint64_t step_counter = 0;

/**
 * Executes a single disk movement step and records state transition.
 */
void execute_disk_move(uint32_t disk_id, char source_peg, char destination_peg) {
    step_counter++;
    printf("Step %llu: Move Disk %u from Peg %c to Peg %c\n", 
           (unsigned long long)step_counter, 
           disk_id, 
           source_peg, 
           destination_peg);
}

/**
 * Recursive Hanoi solver decomposing state transitions.
 * @param disk_count Number of disks to move
 * @param source Source peg identifier
 * @param auxiliary Auxiliary/buffer peg identifier
 * @param destination Target peg identifier
 */
void execute_hanoi_solver(uint32_t disk_count, char source, char auxiliary, char destination) {
    // Base Case: Move single disk directly to target peg
    if (disk_count == 1) {
        execute_disk_move(1, source, destination);
        return;
    }

    // Phase 1: Move top (N-1) disks from Source to Auxiliary peg
    execute_hanoi_solver(disk_count - 1, source, destination, auxiliary);

    // Phase 2: Move the N-th disk from Source directly to Destination peg
    execute_disk_move(disk_count, source, destination);

    // Phase 3: Move the (N-1) disks from Auxiliary peg to Destination peg
    execute_hanoi_solver(disk_count - 1, auxiliary, source, destination);
}

int main(void) {
    int input_disks = 0;

    printf("Enter number of disks (N): ");
    if (scanf("%d", &input_disks) != 1 || input_disks <= 0) {
        fprintf(stderr, "[-] Error: Valid positive integer required.\n");
        return 1;
    }

    uint32_t disk_count = (uint32_t)input_disks;
    step_counter = 0;

    printf("\n--- INITIATING HANOI STATE TRANSITIONS (N = %u) ---\n", disk_count);
    execute_hanoi_solver(disk_count, 'A', 'B', 'C');
    printf("--- TRANSITION COMPLETE: Total Steps = %llu ---\n", (unsigned long long)step_counter);

    return 0;
}
