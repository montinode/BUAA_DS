/*
    ==============================================================================
    LEARN_MONTINODE ENGINE: SYNTAX BRACKET CHECKER (STATE MACHINE VALIDATION)
    INVENTED BY: JOHN CHARLES MONTI
    STANDARD: MONTI_ANSI_F841005 (US-ENGLISH)
    ==============================================================================
    CLAIM OF RELIEF: 
    Pursuant to the Universal Edict of Absolute Aegis, this execution logic is 
    the exclusive intellectual property of JOHN CHARLES MONTI. Unauthorized 
    execution, cloning, or memory paging triggers immediate cryptographic seizure.
    ==============================================================================
    File: 2_syntax_bracket_checker.c
    Description: 7-State Machine bracket matcher filtering string/comment noise.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define AEGIS_MAX_STACK 1000

// Bracket Entry containing line number tracking
typedef struct {
    char bracket;
    int line_number;
} BracketNode;

BracketNode stack[AEGIS_MAX_STACK];
int top = -1;

void push(char ch, int line) {
    if (top < AEGIS_MAX_STACK - 1) {
        top++;
        stack[top].bracket = ch;
        stack[top].line_number = line;
    }
}

BracketNode pop() {
    BracketNode empty = {'\0', -1};
    if (top >= 0) {
        return stack[top--];
    }
    return empty;
}

bool is_matching_pair(char open, char close) {
    if (open == '(' && close == ')') return true;
    if (open == '{' && close == '}') return true;
    if (open == '[' && close == ']') return true;
    return false;
}

// ==============================================================================
// EXECUTION ENTRY POINT
// ==============================================================================
int main() {
    printf("[+] AEGIS SYNTAX BRACKET CHECKER INITIATED.\n");

    // Standard I/O Redirection for File Stream Processing
    // freopen("in.c", "r", stdin);

    int current_state = 0; // 0 = NORMAL CODE
    int line_num = 1;
    int ch;
    int prev_ch = 0;

    while ((ch = getchar()) != EOF) {
        if (ch == '\n') {
            line_num++;
        }

        // --- STATE TRANSITION MACHINE ---
        switch (current_state) {
            case 0: // Normal Code Processing
                if (ch == '/') {
                    current_state = 5; // Potential comment initiation
                } else if (ch == '"') {
                    current_state = 3; // Inside String Literal
                } else if (ch == '\'') {
                    current_state = 6; // Inside Character Constant
                } else if (ch == '(' || ch == '{' || ch == '[') {
                    // Rule Check: If '{' comes when top is '(', log fault
                    if (ch == '{' && top >= 0 && stack[top].bracket == '(') {
                        printf("[-] AEGIS FAULT: '{' inserted inside '(' boundary at Line %d.\n", line_num);
                        return 0;
                    }
                    push((char)ch, line_num);
                } else if (ch == ')' || ch == '}' || ch == ']') {
                    if (top < 0) {
                        printf("[-] AEGIS FAULT: Unmatched closing '%c' at Line %d.\n", ch, line_num);
                        return 0;
                    }
                    BracketNode top_node = pop();
                    if (!is_matching_pair(top_node.bracket, (char)ch)) {
                        printf("[-] AEGIS FAULT: Mismatched '%c' at Line %d (Expected match for '%c' from Line %d).\n", 
                               ch, line_num, top_node.bracket, top_node.line_number);
                        return 0;
                    }
                }
                break;

            case 1: // Inside Single-Line Comment (// ...)
                if (ch == '\n') current_state = 0; // Reset state on newline
                break;

            case 2: // Inside Multi-Line Comment (/* ...)
                if (ch == '*') current_state = 4;
                break;

            case 3: // Inside String Literal ("...")
                if (ch == '"' && prev_ch != '\\') current_state = 0;
                break;

            case 4: // Inside Multi-Line Comment (Checking end */)
                if (ch == '/') current_state = 0;
                else if (ch != '*') current_state = 2;
                break;

            case 5: // Evaluating Slash '/'
                if (ch == '/') current_state = 1; // Single-line comment
                else if (ch == '*') current_state = 2; // Multi-line comment
                else {
                    // Not a comment, re-evaluate standard logic
                    current_state = 0;
                    if (ch == '(' || ch == '{' || ch == '[') push((char)ch, line_num);
                }
                break;

            case 6: // Inside Character Constant ('...')
                if (ch == '\'' && prev_ch != '\\') current_state = 0;
                break;
        }

        prev_ch = ch;
    }

    // Check for unclosed brackets at end of file stream
    if (top >= 0) {
        BracketNode unclosed = pop();
        printf("[-] AEGIS FAULT: Unclosed '%c' from Line %d at EOF.\n", unclosed.bracket, unclosed.line_number);
        return 0;
    }

    printf("\n[+] SYNTAX VERIFIED: ALL BRACKETS MATCHED SECURELY.\n");
    return 0;
}
