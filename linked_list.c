#include "linked_list.h" // Include the header file
#include <stdio.h>       // For printf (used in list_print and potentially errors)
#include <stdlib.h>      // For malloc, free
#include <stdbool.h>     // For bool return type

// Initializes the list by setting the head pointer to NULL.
void list_init(struct Node **head_ptr) {
    if (head_ptr != NULL) {
        *head_ptr = NULL;
    }
}

// Adds a new node with 'data' to the beginning of the list.
void list_prepend(struct Node **head_ptr, int data) {
    if (head_ptr == NULL) return; // Safety check

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in list_prepend.\n");
        return; // Consider other error handling?
    }
    new_node->data = data;
    new_node->next = *head_ptr;
    *head_ptr = new_node;
}

// Adds a new node with 'data' to the end of the list.
void list_append(struct Node **head_ptr, int data) {
     if (head_ptr == NULL) return; // Safety check

    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
     if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in list_append.\n");
        return;
    }
    new_node->data = data;
    new_node->next = NULL; // New last node points to NULL

    // If the list is empty, the new node becomes the head
    if (*head_ptr == NULL) {
        *head_ptr = new_node;
        return;
    }

    // Otherwise, traverse to the current last node
    struct Node* last = *head_ptr;
    while (last->next != NULL) {
        last = last->next;
    }
    // Link the new node after the current last node
    last->next = new_node;
}

// Inserts a new node with 'data' at the specified 0-based position.
// Returns true on success, false on failure.
bool list_insert_at(struct Node **head_ptr, int data, int position) {
    if (head_ptr == NULL || position < 0) {
        fprintf(stderr, "Error: Invalid arguments for list_insert_at.\n");
        return false; // Invalid position or NULL head pointer address
    }

    // Handle insertion at the beginning (position 0)
    if (position == 0) {
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        if (new_node == NULL) {
             fprintf(stderr, "Error: Memory allocation failed in list_insert_at.\n");
             return false;
        }
        new_node->data = data;
        new_node->next = *head_ptr;
        *head_ptr = new_node;
        return true;
    }

    // Traverse to the node *before* the desired insertion point
    struct Node* current = *head_ptr;
    for (int i = 0; i < position - 1 && current != NULL; i++) {
        current = current->next;
    }

    // Check if position is out of bounds (current is NULL or current->next is needed for exact pos)
    // If current is NULL, position was > list length
    if (current == NULL) {
        fprintf(stderr, "Error: Position %d out of bounds for list_insert_at.\n", position);
        return false;
    }

    // Now insert after 'current'
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
     if (new_node == NULL) {
        fprintf(stderr, "Error: Memory allocation failed in list_insert_at.\n");
        return false;
    }
    new_node->data = data;
    new_node->next = current->next;
    current->next = new_node;
    return true;
}

// Deletes the first node from the list. Returns true if successful, false otherwise.
bool list_delete_first(struct Node **head_ptr) {
    if (head_ptr == NULL || *head_ptr == NULL) {
        // List is empty or invalid arguments
        return false;
    }

    struct Node* temp = *head_ptr; // Node to be deleted
    *head_ptr = (*head_ptr)->next; // Update head
    free(temp);                   // Free the old head
    return true;
}

// Deletes the last node from the list. Returns true if successful, false otherwise.
bool list_delete_last(struct Node **head_ptr) {
    if (head_ptr == NULL || *head_ptr == NULL) {
        // List is empty or invalid arguments
        return false;
    }

    // Handle list with only one node
    if ((*head_ptr)->next == NULL) {
        free(*head_ptr);
        *head_ptr = NULL;
        return true;
    }

    // Traverse to the second-to-last node
    struct Node* second_last = *head_ptr;
    while (second_last->next->next != NULL) {
        second_last = second_last->next;
    }

    // Free the last node and update the second-to-last node's next pointer
    free(second_last->next);
    second_last->next = NULL;
    return true;
}

// Deletes the node at the specified 0-based position.
// Returns true on success, false on failure.
bool list_delete_at(struct Node **head_ptr, int position) {
     if (head_ptr == NULL || *head_ptr == NULL || position < 0) {
        // List empty, invalid args, or negative position
        return false;
    }

    // Handle deletion of the first node (position 0)
    if (position == 0) {
        struct Node* temp = *head_ptr;
        *head_ptr = (*head_ptr)->next;
        free(temp);
        return true;
    }

    // Traverse to the node *before* the one to be deleted
    struct Node* prev = *head_ptr;
    for (int i = 0; i < position - 1 && prev->next != NULL; i++) {
        prev = prev->next;
    }

    // Check if position is out of bounds (prev->next is the node to delete)
    if (prev->next == NULL) {
         fprintf(stderr, "Error: Position %d out of bounds for list_delete_at.\n", position);
        return false;
    }

    // Delete the node after 'prev'
    struct Node* node_to_delete = prev->next;
    prev->next = node_to_delete->next; // Bypass the node
    free(node_to_delete);             // Free the node
    return true;
}

// Prints the elements of the list. (Takes Node*, not Node**)
void list_print(struct Node *head) {
    struct Node* current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Finds the first node containing 'value'. (Takes Node*)
// Returns a pointer to the node if found, NULL otherwise.
struct Node* list_find(struct Node *head, int value) {
    struct Node* current = head;
    while (current != NULL) {
        if (current->data == value) {
            return current; // Return pointer to the found node
        }
        current = current->next;
    }
    return NULL; // Value not found
}

// Updates the data of the node at the specified 0-based position. (Takes Node*)
// Returns true on success, false on failure.
bool list_set_at(struct Node *head, int position, int new_value) {
    if (position < 0) {
        fprintf(stderr, "Error: Position cannot be negative for list_set_at.\n");
        return false;
    }

    struct Node* current = head;
    for (int i = 0; i < position && current != NULL; i++) {
        current = current->next;
    }

    // Check if position is out of bounds
    if (current == NULL) {
        fprintf(stderr, "Error: Position %d out of bounds for list_set_at.\n", position);
        return false;
    }

    // Update the data
    current->data = new_value;
    return true;
}

// Calculates and returns the number of nodes in the list. (Takes Node*)
int list_length(struct Node *head) {
    struct Node* current = head;
    int length = 0;
    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length; // Return the calculated length
}

// Reverses the order of nodes in the list in-place.
void list_reverse(struct Node **head_ptr) {
    if (head_ptr == NULL || *head_ptr == NULL || (*head_ptr)->next == NULL) {
        return; // Nothing to reverse (empty or single node list)
    }

    struct Node* prev = NULL;
    struct Node* current = *head_ptr;
    struct Node* next_node = NULL; // Renamed from 'next' to avoid confusion

    while (current != NULL) {
        next_node = current->next; // Store the next node
        current->next = prev;     // Reverse the current node's pointer
        prev = current;           // Move prev one step forward
        current = next_node;      // Move current one step forward
    }
    *head_ptr = prev; // New head is the previous tail
}

// Frees all nodes in the list and sets the head pointer (via address) to NULL.
void list_destroy(struct Node **head_ptr) {
     if (head_ptr == NULL) return; // Safety check

    struct Node* current = *head_ptr;
    struct Node* next_node;

    while (current != NULL) {
        next_node = current->next;
        free(current);
        current = next_node;
    }
    *head_ptr = NULL; // Set the caller's head pointer to NULL
}