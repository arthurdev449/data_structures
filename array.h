#ifndef ARRAY_H // Start of include guard
#define ARRAY_H

#include <limits.h> // For INT_MIN used in dynamic_array_get_element prototype
#include <stdio.h> // For size_t (might be needed, good practice)
#include <stdlib.h> // For size_t (often needed for malloc/realloc prototypes)


// Structure definition (Needs to be in the header so other files know its layout)
typedef struct Array {
    int *data;
    int capacity;
    int count;
} Array;


// ----- Function Prototypes -----

// Initializes an existing Array struct. Returns 1 on success, 0 on failure.
// NOTE: You named the initialization function 'start_array' in the image.
// 'array_init' is more conventional. I'll list both, choose one.
int array_init(Array *arr); // Your name from image
// int array_init(Array *arr); // Conventional name


// Inserts data onto the end of the array, resizing if necessary.
void array_append(Array *arr, int data);


// Prints the array elements.
// NOTE: You named the print function 'array_init' in the image, which is incorrect.
// 'array_print' is correct.
void array_print(Array *arr); // Correct name for printing


// Deletes the element at the specified 1-based index.
void array_delete_at(Array *arr, int index);


// Frees the internal data buffer and resets members. Does NOT free the Array struct itself.
void array_destroy(Array *arr);


// Finds the 1-based index of the first occurrence of 'data'. Returns -1 if not found.
// NOTE: You named this 'array_get_element' in the image, but it finds by VALUE.
// 'array_find' or 'array_index_of' is correct.
int array_find(Array *arr, int data); // Correct name for finding by value


// Gets the element at the specified 1-based index. Returns INT_MIN on error.
// NOTE: You named this 'array_show_element' in the image. 'array_get' is conventional.
int array_get(Array *arr, int index); // Correct name for getting by index

// Returns the number of elements currently in the array.
int array_size(Array *arr); // You'll need to implement this (returns arr->count)

// Returns the current allocated capacity of the array.
int array_capacity(Array *arr); // You'll need to implement this (returns arr->capacity)

// Checks if the array is empty. Returns 1 if empty, 0 otherwise.
int array_is_empty(Array *arr); // You'll need to implement this (checks arr->count == 0)

#endif // ARRAY_H // End of include guard