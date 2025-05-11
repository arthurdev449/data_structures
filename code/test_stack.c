#include <stdio.h>
#include <stdlib.h> // Added for exit() if needed, good practice
#include <assert.h>
#include <limits.h> // Needed for INT_MIN checks

#include "stack.h" // Include the header for your stack implementation

void test_push_peek() {
    printf("Testing stack_push and stack_peek...\n");
    struct Stack stack;      // Declare the stack struct variable
    struct Stack *stack_p = &stack; // Create a pointer to the stack
    stack_init(stack_p);      // Initialize it using the pointer

    // Test push onto empty stack
    stack_push(stack_p, 10);
    assert(stack_peek(stack_p) == 10); // Use stack_peek with pointer
    assert(!stack_is_empty(stack_p));  // Check it's not empty

    // Test push onto non-empty stack
    stack_push(stack_p, 20);
    assert(stack_peek(stack_p) == 20); // Should be 20 now
    assert(!stack_is_empty(stack_p));

    stack_push(stack_p, 30);
    assert(stack_peek(stack_p) == 30); // Should be 30 now

    stack_destroy(stack_p); // Clean up allocated nodes
    printf("stack_push/stack_peek tests passed.\n");
}

void test_pop() {
    printf("Testing stack_pop...\n");
    struct Stack stack;
    struct Stack *stack_p = &stack;
    stack_init(stack_p);

    stack_push(stack_p, 10);
    stack_push(stack_p, 20);
    stack_push(stack_p, 30);

    // Pop elements and check values
    assert(stack_pop(stack_p) == 30);
    assert(stack_peek(stack_p) == 20); // Check top after pop
    assert(!stack_is_empty(stack_p));

    assert(stack_pop(stack_p) == 20);
    assert(stack_peek(stack_p) == 10); // Check top after pop
    assert(!stack_is_empty(stack_p));

    assert(stack_pop(stack_p) == 10);
    assert(stack_is_empty(stack_p));  // Should be empty now
    assert(stack_peek(stack_p) == INT_MIN); // Check peek on empty returns error

    stack_destroy(stack_p); // Should already be empty, but good practice
    printf("stack_pop tests passed.\n");
}

void test_is_empty() {
    printf("Testing stack_is_empty...\n");
    struct Stack stack;
    struct Stack *stack_p = &stack;
    stack_init(stack_p);

    assert(stack_is_empty(stack_p) == 1); // Should be empty initially

    stack_push(stack_p, 10);
    assert(stack_is_empty(stack_p) == 0); // Not empty after push

    stack_pop(stack_p);
    assert(stack_is_empty(stack_p) == 1); // Empty again after pop

    stack_destroy(stack_p);
    printf("stack_is_empty tests passed.\n");
}

void test_empty_stack_operations() {
    printf("Testing operations on empty stack...\n");
    struct Stack stack;
    struct Stack *stack_p = &stack;
    stack_init(stack_p);

    assert(stack_is_empty(stack_p) == 1);
    assert(stack_peek(stack_p) == INT_MIN); // Peek on empty
    assert(stack_pop(stack_p) == INT_MIN);  // Pop on empty

    // Test destroy on empty stack (should not crash)
    stack_destroy(stack_p);
    printf("Empty stack operations tests passed.\n");
}


int main() {
    test_push_peek();       // Combined push and peek tests for clarity
    test_pop();
    test_is_empty();
    test_empty_stack_operations(); // Added specific tests for empty stack

    printf("\nAll stack tests passed (if no assertions failed)!\n");
    return 0;
}