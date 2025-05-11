#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h> // For bool return types

#include "linked_list.h" // Include the header for your linked list

// Helper function to check node data at a specific index (0-based)
// Returns -1 if index is out of bounds, otherwise returns data.
// Useful for assertions.
static int get_data_at(struct Node *head, int index) {
    struct Node *current = head;
    int count = 0;
    while (current != NULL) {
        if (count == index) {
            return current->data;
        }
        count++;
        current = current->next;
    }
    return -1; // Index out of bounds or list empty
}

void test_insertion() {
    printf("Testing list insertion (prepend, append, insert_at)...\n");
    struct Node *head = NULL;
    list_init(&head); // Initialize

    // Prepend (old insert_at_beginning)
    list_prepend(&head, 10); // List: 10
    assert(list_length(head) == 1);
    assert(get_data_at(head, 0) == 10);

    // Append (old insert_at_end)
    list_append(&head, 20); // List: 10 -> 20
    assert(list_length(head) == 2);
    assert(get_data_at(head, 0) == 10);
    assert(get_data_at(head, 1) == 20);

    // Insert_at (old insert_at_position), 0-based index
    assert(list_insert_at(&head, 15, 1) == true); // List: 10 -> 15 -> 20
    assert(list_length(head) == 3);
    assert(get_data_at(head, 0) == 10);
    assert(get_data_at(head, 1) == 15);
    assert(get_data_at(head, 2) == 20);

    // Append more
    list_append(&head, 30); // List: 10 -> 15 -> 20 -> 30
    list_append(&head, 29); // List: 10 -> 15 -> 20 -> 30 -> 29
    list_append(&head, 5);  // List: 10 -> 15 -> 20 -> 30 -> 29 -> 5
    assert(list_length(head) == 6);
    assert(get_data_at(head, 5) == 5);

    // Test inserting at beginning using insert_at
    assert(list_insert_at(&head, 55, 0) == true); // List: 55 -> 10 -> 15 -> ...
    assert(list_length(head) == 7);
    assert(get_data_at(head, 0) == 55);
    assert(get_data_at(head, 1) == 10);

    // Test inserting at end using insert_at
    assert(list_insert_at(&head, 99, 7) == true); // List: ... -> 5 -> 99
    assert(list_length(head) == 8);
    assert(get_data_at(head, 7) == 99);

    // Test insert out of bounds
    assert(list_insert_at(&head, 100, 10) == false); // Position 10 is out of bounds
    assert(list_length(head) == 8); // Length should not change

    printf("Insertion tests passed.\n");
    list_print(head); // Optional: print final state
    list_destroy(&head); // Cleanup
    assert(head == NULL); // Destroy should set head to NULL
}

void test_deletion() {
    printf("Testing list deletion (first, last, at)...\n");
    struct Node *head = NULL;
    list_init(&head);

    // Setup list: 10 -> 15 -> 20 -> 30 -> 29 -> 5
    list_append(&head, 10);
    list_append(&head, 15);
    list_append(&head, 20);
    list_append(&head, 30);
    list_append(&head, 29);
    list_append(&head, 5);
    assert(list_length(head) == 6);

    // Delete first (old delete_from_beginning)
    assert(list_delete_first(&head) == true); // List: 15 -> 20 -> 30 -> 29 -> 5
    assert(list_length(head) == 5);
    assert(get_data_at(head, 0) == 15);

    // Delete last (old delete_from_end)
    assert(list_delete_last(&head) == true); // List: 15 -> 20 -> 30 -> 29
    assert(list_length(head) == 4);
    assert(get_data_at(head, 3) == 29);
    assert(get_data_at(head, 4) == -1); // Index 4 should now be out of bounds

    // Delete at index 1 (value 20)
    assert(list_delete_at(&head, 1) == true); // List: 15 -> 30 -> 29
    assert(list_length(head) == 3);
    assert(get_data_at(head, 0) == 15);
    assert(get_data_at(head, 1) == 30);
    assert(get_data_at(head, 2) == 29);

    // Delete out of bounds
    assert(list_delete_at(&head, 5) == false);
    assert(list_length(head) == 3);

    // Delete only element
    list_destroy(&head);
    list_append(&head, 100);
    assert(list_delete_at(&head, 0) == true);
    assert(list_length(head) == 0);
    assert(head == NULL);

    // Delete from empty list
    assert(list_delete_first(&head) == false);
    assert(list_delete_last(&head) == false);
    assert(list_delete_at(&head, 0) == false);

    printf("Deletion tests passed.\n");
    list_destroy(&head); // Cleanup just in case
}

void test_find_set_length() {
    printf("Testing find, set_at, length...\n");
    struct Node *head = NULL;
    list_init(&head);
    list_append(&head, 10);
    list_append(&head, 20);
    list_append(&head, 15);
    list_append(&head, 30);
    // List: 10 -> 20 -> 15 -> 30

    // Length (old calculate_length)
    assert(list_length(head) == 4);

    // Find (old search_list)
    struct Node *found_node = list_find(head, 15);
    assert(found_node != NULL);
    assert(found_node->data == 15);

    struct Node *not_found_node = list_find(head, 99);
    assert(not_found_node == NULL);

    // Set_at (old update_node)
    assert(list_set_at(head, 2, 111) == true); // Change 15 to 111 at index 2
    assert(get_data_at(head, 2) == 111);
    found_node = list_find(head, 15); // Should not find 15 anymore
    assert(found_node == NULL);
    found_node = list_find(head, 111); // Should find 111
    assert(found_node != NULL);
    assert(found_node->data == 111);

    // Set out of bounds
    assert(list_set_at(head, 5, 999) == false);

    printf("Find, set_at, length tests passed.\n");
    list_destroy(&head);
}

void test_reverse() {
    printf("Testing list_reverse...\n");
    struct Node *head = NULL;
    list_init(&head);
    list_append(&head, 10);
    list_append(&head, 20);
    list_append(&head, 30);
    list_append(&head, 40);
    // List: 10 -> 20 -> 30 -> 40

    list_reverse(&head);
    // Expected: 40 -> 30 -> 20 -> 10
    assert(list_length(head) == 4);
    assert(get_data_at(head, 0) == 40);
    assert(get_data_at(head, 1) == 30);
    assert(get_data_at(head, 2) == 20);
    assert(get_data_at(head, 3) == 10);

    // Reverse empty list
    list_destroy(&head);
    list_reverse(&head); // Should not crash
    assert(head == NULL);

    // Reverse list with one element
    list_append(&head, 55);
    list_reverse(&head);
    assert(list_length(head) == 1);
    assert(get_data_at(head, 0) == 55);

    printf("Reverse tests passed.\n");
    list_destroy(&head);
}

int main() {
    test_insertion();
    test_deletion();
    test_find_set_length();
    test_reverse();

    printf("\nAll linked list tests passed (if no assertions failed)!\n");
    return 0;
}