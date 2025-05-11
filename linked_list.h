#ifndef LINKED_LIST_H // Include guard start
#define LINKED_LIST_H

#include <stdio.h>  // For standard types/prototypes if needed
#include <stdlib.h> // For standard types/prototypes if needed
#include <stdbool.h> // For bool return types (optional, can use int 0/1)

// --- Structure Definitions ---

// Node structure for the singly linked list
struct Node {
    int data;
    struct Node *next;
};

// NOTE: Your current implementation manages the list directly via Node** head.
// No separate LinkedList management struct is used, which is fine for this style.

// --- Function Prototypes ---

// Initializes the list by setting the head pointer (passed by address) to NULL.
void list_init(struct Node **head_ptr);

// Adds a new node with 'data' to the beginning of the list.
void list_prepend(struct Node **head_ptr, int data);

// Adds a new node with 'data' to the end of the list.
void list_append(struct Node **head_ptr, int data);

// Inserts a new node with 'data' at the specified 0-based position.
// Returns true on success, false on failure (e.g., out of bounds, alloc fail).
bool list_insert_at(struct Node **head_ptr, int data, int position); // Changed return

// Deletes the first node from the list. Returns true if successful, false otherwise.
bool list_delete_first(struct Node **head_ptr); // Changed return

// Deletes the last node from the list. Returns true if successful, false otherwise.
bool list_delete_last(struct Node **head_ptr); // Changed return

// Deletes the node at the specified 0-based position.
// Returns true on success, false on failure (e.g., out of bounds).
bool list_delete_at(struct Node **head_ptr, int position); // Added this prototype, changed return

// Prints the elements of the list.
void list_print(struct Node *head); // Takes Node*, not Node**

// Finds the first node containing 'value'.
// Returns a pointer to the node if found, NULL otherwise.
struct Node* list_find(struct Node *head, int value); // Changed signature and return

// Updates the data of the node at the specified 0-based position.
// Returns true on success, false on failure (e.g., out of bounds).
bool list_set_at(struct Node *head, int position, int new_value); // Changed return

// Calculates and returns the number of nodes in the list.
int list_length(struct Node *head); // Changed return

// Reverses the order of nodes in the list in-place.
void list_reverse(struct Node **head_ptr);

// Frees all nodes in the list and sets the head pointer (via address) to NULL.
void list_destroy(struct Node **head_ptr);


#endif // LINKED_LIST_H // Include guard end