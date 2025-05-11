#include "stack.h"   // 1. Include the header file
#include <stdio.h>   // 3. Include for fprintf, stderr, printf
#include <stdlib.h>  // 3. Include for malloc, free
#include <limits.h>  // 3. Include for INT_MIN

// Initializes the stack
void stack_init(struct Stack *s) { // 4. Consistent use of 'struct'
    if (s == NULL) return; // Optional: Robustness check
    s->top = NULL;
}

// Pushes data onto the stack
void stack_push(struct Stack *s, int data) { // 4. Consistent use of 'struct'
    if (s == NULL) return; // Optional: Robustness check

    // Use 'struct StackNode' consistently
    struct StackNode *newNode = (struct StackNode *)malloc(sizeof(struct StackNode));
    if (newNode == NULL) {
        // It's often better to print errors to stderr
        fprintf(stderr, "Error: Memory allocation failed in stack_push.\n");
        return; // Or potentially exit(1) depending on requirements
    }
    newNode->data = data;
    newNode->next = s->top;
    s->top = newNode;
}

// Pops data from the stack
int stack_pop(struct Stack *s) { // 4. Consistent use of 'struct'
    // Check for NULL stack pointer AND empty stack
    if (s == NULL || s->top == NULL) {
        fprintf(stderr, "Error: Stack underflow on pop.\n");
        return INT_MIN; // Return error indicator
    }

    // Use 'struct StackNode' consistently
    struct StackNode *node_to_remove = s->top; // Temporary pointer
    int popped_data = node_to_remove->data;    // Get data before freeing

    s->top = node_to_remove->next; // Update top pointer

    free(node_to_remove); // Free the removed node

    return popped_data;
}

// Peeks at the top data element
int stack_peek(struct Stack *s) { // 4. Consistent use of 'struct'
    // Check for NULL stack pointer AND empty stack
    if (s == NULL || s->top == NULL) {
        fprintf(stderr, "Error: Stack underflow on peek.\n");
        return INT_MIN; // Return error indicator
    }
    return s->top->data;
}

// Checks if the stack is empty
int stack_is_empty(struct Stack *s) { // 4. Consistent use of 'struct'
    if (s == NULL) {
        // Depending on requirements, NULL could be treated as empty or an error
        fprintf(stderr, "Warning: stack_is_empty called with NULL stack pointer.\n");
        return 1; // Treat NULL as empty for this example
    }
    // Original logic: return 1 if empty (top is NULL), 0 otherwise
    // Simplified return statement
    return (s->top == NULL);
}

// Destroys the stack (frees all nodes)
void stack_destroy(struct Stack *s) { // 4. Consistent use of 'struct'
    if (s == NULL) return; // Optional: Robustness check

    // Use 'struct StackNode' consistently
    struct StackNode *current = s->top;
    struct StackNode *next_node;

    while (current != NULL) {
        next_node = current->next; // Store next pointer
        free(current);             // Free current node
        current = next_node;       // Move to next
    }
    s->top = NULL; // Reset top pointer
}