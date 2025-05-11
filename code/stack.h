#ifndef STACK_H // Include guard start
#define STACK_H

#include <stdio.h>  // For standard types if needed (like size_t, though not used here)
#include <stdlib.h> // For standard types if needed
#include <limits.h> // For INT_MIN used in pop/peek prototypes

// --- Structure Definitions ---

// Node structure for the linked list implementation of the stack
// Note: Using 'struct StackNode' within the file is fine, but the typedef
// can make it slightly cleaner if you prefer. Let's stick to struct tag for now.
struct StackNode { // Renamed struct tag slightly (optional, Stack_node is also fine)
    int data;
    struct StackNode *next;
};

// Stack structure containing the top pointer
struct Stack {
    struct StackNode *top;
};


// --- Function Prototypes ---

// Initializes an existing Stack struct. Call this before using the stack.
void stack_init(struct Stack *s);

// Pushes an element onto the top of the stack. Handles memory allocation.
void stack_push(struct Stack *s, int data);

// Pops (removes and returns) the element from the top of the stack.
// Returns INT_MIN if the stack is empty (stack underflow).
int stack_pop(struct Stack *s);

// Peeks at (returns without removing) the element at the top of the stack.
// Returns INT_MIN if the stack is empty.
int stack_peek(struct Stack *s);

// Checks if the stack is empty. Returns 1 if empty, 0 otherwise.
int stack_is_empty(struct Stack *s);

// Frees all nodes in the stack and resets the top pointer.
// Does NOT free the Stack struct itself.
void stack_destroy(struct Stack *s);


#endif // STACK_H // Include guard end