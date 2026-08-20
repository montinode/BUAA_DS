/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: CRYPTOGRAPHIC EXPRESSION CALCULATOR
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this calculation logic is 
    the exclusive intellectual property of JOHN CHARLES MONTI. Unauthorized 
    execution, cloning, or memory paging triggers immediate cryptographic seizure.
    ==============================================================================
    File: 3_cryptographic_expression_calculator.c
    Description: Dual-stack expression evaluator with strict precedence routing.
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define AEGIS_MAX_STREAM 2048
#define AEGIS_MAX_STACK 1000

// --- AEGIS DUAL STACK ARCHITECTURE ---
double num_stack[AEGIS_MAX_STACK];
int num_top = 0;

char op_stack[AEGIS_MAX_STACK];
int op_top = 0;

/**
 * Returns the cryptographic precedence of mathematical operators.
 */
int get_precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

/**
 * Pops two values and one operator, executes the calculation, 
 * and pushes the new neural state back to the Number Stack.
 */
void execute_calculation() {
    if (num_top < 2 || op_top < 1) return; // Prevent Underflow

    double a = num_stack[--num_top]; // Second operand
    double b = num_stack[--num_top]; // First operand
    char current_op = op_stack[--op_top];
    
    double result = 0.0;
    
    if (current_op == '+') result = b + a;
    else if (current_op == '-') result = b - a;
    else if (current_op == '*') result = b * a;
    else if (current_op == '/') {
        if (a == 0) {
            printf("[-] AEGIS EXCEPTION: Division by Zero Precluded.\n");
            exit(1);
        }
        result = b / a;
    }
    
    num_stack[num_top++] = result;
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    printf("[+] AEGIS CRYPTOGRAPHIC CALCULATOR INITIATED.\n");
    
    char execution_stream[AEGIS_MAX_STREAM];
    if (fgets(execution_stream, AEGIS_MAX_STREAM, stdin) == NULL) return 1;

    int i = 0;
    while (execution_stream[i] != '\0' && execution_stream[i] != '\n') {
        char current_char = execution_stream[i];

        // 1. Skip spaces and termination characters
        if (current_char == ' ' || current_char == '=') {
            i++;
            continue;
        }

        // 2. Parse Full Digits dynamically
        if (isdigit(current_char)) {
            double parsed_value = current_char - '0';
            i++;
            while (isdigit(execution_stream[i])) {
                parsed_value = parsed_value * 10 + (execution_stream[i] - '0');
                i++;
            }
            num_stack[num_top++] = parsed_value;
            continue;
        }

        // 3. Handle Operators and Parentheses
        if (current_char == '(') {
            op_stack[op_top++] = current_char;
        } 
        else if (current_char == ')') {
            // Calculate until matching left bracket is found
            while (op_top > 0 && op_stack[op_top - 1] != '(') {
                execute_calculation();
            }
            if (op_top > 0 && op_stack[op_top - 1] == '(') {
                op_top--; // Pop the '(' without executing
            }
        } 
        else {
            // Process Operator Precedence
            while (op_top > 0 && get_precedence(op_stack[op_top - 1]) >= get_precedence(current_char)) {
                execute_calculation();
            }
            op_stack[op_top++] = current_char;
        }
        i++;
    }

    // 4. Drain remaining operations in the stack
    while (op_top > 0) {
        execute_calculation();
    }

    // 5. Output Final Sovereign State
    if (num_top > 0) {
        printf("\n[+] FINAL NEURAL STATE: %.2f\n", num_stack[0]);
    } else {
        printf("\n[-] AEGIS WARNING: Empty Execution State.\n");
    }

    return 0;
}
