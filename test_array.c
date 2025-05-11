#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // Needed if you check against INT_MIN
#include <assert.h>

#include "array.h" // Include the header for your dynamic array

/*
Structure definition is now in array.h:
typedef struct Array {
    int *data;
    int capacity;
    int count;
} Array;
*/

int main() {
    Array array;           // Allocate the struct itself on the stack
    Array *arr = &array;   // Create a pointer pointing to it

    // --- Initialization ---
    // Using start_array based on your previous image for init function name
    if (!start_array(arr)) {
        printf("Failed to initialize dynamic array.\n");
        return 1; // Exit if initialization failed
    }
    printf("Array initialized successfully.\n");
    assert(arr->data != NULL); // Basic check after successful init

    // --- Test Insertion (Append) ---
    printf("Adding elements to the array using array_append...\n");
    for (int i = 0; i < 15; i++) {
        array_append(arr, i * 10); // Use array_append
        // Check state after each append
        assert(arr->count == i + 1);
        // Verify the last added element using array_get (assuming 1-based index)
        assert(array_get(arr, i + 1) == i * 10);
    }
    printf("Elements added successfully. Count: %d, Capacity: %d\n", arr->count, arr->capacity);
    // Optional: Print the array to see the content
    array_print(arr);

    // --- Test Resizing ---
    printf("Testing array resizing (implicitly tested by append)...\n");
    assert(arr->capacity >= 15); // Ensure capacity increased during appends
    printf("Array resized successfully (Capacity is now %d).\n", arr->capacity);

    // --- Test Getting Elements ---
    printf("Testing array_get...\n");
    assert(array_get(arr, 1) == 0 * 10);  // 1st element (1-based index)
    assert(array_get(arr, 8) == 7 * 10);  // 8th element
    assert(array_get(arr, 15) == 14 * 10); // 15th element (last)
    printf("array_get tests passed.\n");

    // --- Test Finding Elements ---
    printf("Testing array_find...\n");
    assert(array_find(arr, 7 * 10) == 8);   // Value 70 should be at 1-based index 8
    assert(array_find(arr, 0 * 10) == 1);   // Value 0 should be at 1-based index 1
    assert(array_find(arr, 14 * 10) == 15); // Value 140 should be at 1-based index 15
    assert(array_find(arr, 999) == -1);     // Value not present
    printf("array_find tests passed.\n");

    // --- Test Deleting Elements ---
    printf("Deleting elements using array_delete_at...\n");
    // Delete from the middle
    int value_at_index_5 = array_get(arr, 5); // Get value before deleting (0-based 4 -> 40)
    array_delete_at(arr, 5); // Delete 1-based index 5
    assert(arr->count == 14);
    assert(array_find(arr, value_at_index_5) == -1); // Should not find 40 anymore
    printf("Deleted element at index 5. Count: %d\n", arr->count);

    // Delete from the beginning
    int first_value = array_get(arr, 1); // Get value before deleting
    array_delete_at(arr, 1); // Delete 1-based index 1
    assert(arr->count == 13);
    assert(array_find(arr, first_value) == -1);
    printf("Deleted element at index 1. Count: %d\n", arr->count);

    // Delete from the end
    int last_value = array_get(arr, arr->count); // Get value before deleting (count is now 13)
    array_delete_at(arr, arr->count); // Delete last element (1-based index is current count)
    assert(arr->count == 12);
    assert(array_find(arr, last_value) == -1);
    printf("Deleted element at end. Count: %d\n", arr->count);

    printf("Elements deleted successfully.\n");
    array_print(arr);

    // --- Test Destroy (was array_clear) ---
    printf("Destroying array using array_destroy...\n");
    array_destroy(arr); // Use array_destroy
    assert(arr->data == NULL);
    assert(arr->count == 0);
    assert(arr->capacity == 0);
    printf("Array destroyed successfully.\n");

    // --- Test Edge Cases on Destroyed/Empty Array ---
    printf("Testing edge cases on empty/destroyed array...\n");
    // Re-initialize to test deleting from empty after destroy
    if (!start_array(arr)) { return 1; } // Re-initialize for safety checks
    array_delete_at(arr, 1); // Deleting from an empty array (should print msg & return)
    assert(arr->count == 0); // Count should remain 0
    assert(array_get(arr, 1) == INT_MIN);    // Accessing invalid index 1
    assert(array_find(arr, 10) == -1);       // Finding in empty array
    array_destroy(arr); // Clean up the re-initialized array
    printf("Edge cases handled successfully.\n");


    printf("\nAll dynamic array tests passed (if no assertions failed).\n");
    return 0;
}