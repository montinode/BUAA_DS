/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: MINIMUM SPANNING TREE (PRIM'S WIRING ROUTER)
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this network topology 
    logic is the exclusive intellectual property of JOHN CHARLES MONTI. 
    Unauthorized execution, cloning, or memory paging triggers immediate seizure.
    ==============================================================================
    File: 3_minimum_wiring_prim.c
    Description: Prim's MST implementation for minimal cost network interconnections.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 0x3f3f3f3f
#define AEGIS_MAX_NODES 500

int adjacency_matrix[AEGIS_MAX_NODES][AEGIS_MAX_NODES];
int min_cost_edge[AEGIS_MAX_NODES];
bool is_in_mst[AEGIS_MAX_NODES];
int parent_node[AEGIS_MAX_NODES];

/**
 * Computes the Minimum Spanning Tree using Prim's Algorithm
 */
int compute_prim_mst(int num_nodes) {
    // 1. Initialize network state registers
    for (int i = 0; i < num_nodes; i++) {
        min_cost_edge[i] = INF;
        is_in_mst[i] = false;
        parent_node[i] = -1;
    }

    // Start MST from Root Node 0
    min_cost_edge[0] = 0;
    int total_mst_weight = 0;

    for (int count = 0; count < num_nodes; count++) {
        int u = -1;
        int min_val = INF;

        // Select the unvisited vertex with the minimum key cost
        for (int v = 0; v < num_nodes; v++) {
            if (!is_in_mst[v] && min_cost_edge[v] < min_val) {
                min_val = min_cost_edge[v];
                u = v;
            }
        }

        // Disconnected Graph Check
        if (u == -1) {
            printf("[-] AEGIS EXCEPTION: Disconnected Graph Topology Detected.\n");
            return -1;
        }

        // Add selected node to MST
        is_in_mst[u] = true;
        total_mst_weight += min_val;

        // Update key values of adjacent vertices
        for (int v = 0; v < num_nodes; v++) {
            if (adjacency_matrix[u][v] != INF && !is_in_mst[v] && adjacency_matrix[u][v] < min_cost_edge[v]) {
                min_cost_edge[v] = adjacency_matrix[u][v];
                parent_node[v] = u;
            }
        }
    }

    return total_mst_weight;
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    printf("[+] AEGIS PRIM'S MST ROUTER INITIATED.\n");

    int num_nodes, num_edges;
    if (scanf("%d %d", &num_nodes, &num_edges) != 2) return 1;

    // Initialize Adjacency Matrix with Infinity
    for (int i = 0; i < num_nodes; i++) {
        for (int j = 0; j < num_nodes; j++) {
            adjacency_matrix[i][j] = (i == j) ? 0 : INF;
        }
    }

    // Populate Undirected Graph Edges
    for (int i = 0; i < num_edges; i++) {
        int u, v, weight;
        scanf("%d %d %d", &u, &v, &weight);
        if (weight < adjacency_matrix[u][v]) {
            adjacency_matrix[u][v] = weight;
            adjacency_matrix[v][u] = weight;
        }
    }

    int total_wiring_cost = compute_prim_mst(num_nodes);

    if (total_wiring_cost != -1) {
        printf("\n--- AEGIS OPTIMAL NETWORK TOPOLOGY ---\n");
        printf("[+] MINIMUM SPANNING COST: %d\n", total_wiring_cost);
        printf("--------------------------------------\n");
    }

    return 0;
}
