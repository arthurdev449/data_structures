#include "array.h" // Include your header file
#include <stdio.h> // Keep includes needed for function bodies (printf, etc.)
#include <stdlib.h> // Keep includes needed for function bodies (malloc, realloc, free, exit)
#include <limits.h> // Keep includes needed for function bodies (if INT_MIN is used)

// Function to initialize the dynamic array (MODIFIED)
// Takes a pointer to an EXISTING Array struct and initializes its members.
// Returns 1 on success, 0 on failure (e.g., memory allocation failed).
int array_init(Array *arr) {
    if (arr == NULL) {
        fprintf(stderr, "Error: Cannot initialize NULL array pointer.\n");
        return 0; // Indicate failure
    }

    // Allocate memory for the data buffer
    arr->data = malloc(10 * sizeof(int));
    if (arr->data == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for array data.\n");
        arr->capacity = 0; // Ensure consistent state on failure
        arr->count = 0;
        return 0; // Indicate failure
    }

    // Initialize capacity and count of the struct pointed to by arr
    arr->capacity = 10;
    arr->count = 0;
    return 1; // Indicate success
}

// Function to insert an element into the dynamic array
void array_append(Array *arr, int data) {
    if (arr->count < arr->capacity) {
        arr->data[arr->count] = data;
        arr->count++;
    } else {
        int more_size = (arr->capacity * 2) * sizeof(int);
        arr->data = realloc(arr->data, more_size);
        if (arr->data == NULL) {
            printf("Memory allocation failed\n");
            exit(1);
        }
        arr->data[arr->count] = data;
        arr->count++;
        arr->capacity *= 2;
    }
}

// Function to print the array elements
void array_print(Array *arr) {
    printf("Array elements: | ");
    for (int i = 0; i < arr->count; i++) {
        printf("%d | ", arr->data[i]);
    }
    printf("\n");
}

// Function to delete an element at a specific index
void array_delete_at(Array *arr, int index) {
    index -= 1; // Convert to 0-based index
    if (index < 0 || index >= arr->count) {
        printf("Index out of bounds\n");
        return;
    }
    for (int i = index; i < arr->count - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->count--;
}

// Function to delete all elements and free internal data (MODIFIED)
void array_destroy(Array *arr) {
    if (arr == NULL) {
        return; // Nothing to do if arr is NULL
    }
    if (arr->data != NULL) {
        free(arr->data); // Free only the internal data buffer
    }
    // Reset members to represent an empty state
    arr->data = NULL;
    arr->count = 0;
    arr->capacity = 0;

    // DO NOT free(arr) here.
    // DO NOT set arr = NULL here (it wouldn't affect the caller).
}

// Function to find the index of a specific value
int array_find(Array *arr, int data) {
    for (int i = 0; i < arr->count; i++) {
        if (arr->data[i] == data) {
            return i + 1; // Return 1-based index
        }
    }
    return -1; // Element not found
}

// Function to get the element at a specific index
int array_get(Array *arr, int index) {
    index -= 1; // Convert to 0-based index
    if (index < 0 || index >= arr->count) {
        printf("Index out of bounds\n");
        return INT_MIN; // Return a special value to indicate error
    }
    return arr->data[index];
}

int array_size(Array *arr) {
    return arr->count; // Return the number of elements in the array
}

int array_capacity(Array *arr) {
    return arr->capacity; // Return the current allocated capacity of the array
}

int array_is_empty(Array *arr) {
    return arr->count == 0; // Return 1 if empty, 0 otherwise
}
