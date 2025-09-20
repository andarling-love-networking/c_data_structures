/**
 * @file int/Array.h
 * @author andarling
 * @date 20/09/2025
 * @brief a library for Array for integers
 * 
 * @details this library only make a \c `struct` for normal array in C, as it 
 * contains an additional attribute \i `capacity` to denote the maximum elements
 * the container can hold
 * 
 * API:
 * @li new_T ~ create
 * @li from_T ~ copy
 * @li free_T ~ free()
 * @li get_item_T ~ a[]
 */
#ifndef __C_DSA_INT_ARRAY__
#define __C_DSA_INT_ARRAY__

#include <stdlib.h>
#include <string.h>

#include "../utils/Result.h"
#include "../utils/status.h"

typedef struct Array_int Array_int;
/**
 * @struct Array_int
 * @author andarling
 * @date 20/09/2025
 * @brief a struct for normal integer array
 */
struct Array_int {
  size_t capacity;
  int data[];
};

/**
 * @fn Result new_Array_int(int *data, size_t size, size_t capacity)
 * 
 * @author andarling
 * @date 20/09/2025
 * @brief a function return \c `Result` to whether an error code or the allocated
 * data
 * 
 * @param data a pointer to where existing elements should be added to array
 * (if \i `data` is NULL, there will be no elements added)
 * @param size the number of elements in \i `data` to be copied
 * (\i `size` cannot be less than 0)
 * @param capacity the desired maximum elements to be held in the container
 * (\i `capacity` cannot be less than \i `size`)
 * 
 * @return a \i `Result` variable indicating an error or if no error, the 
 * allocated data
 */
Result new_Array_int(int *data, size_t size, size_t capacity) {
  if (!data) {
    size = 0;
  }
  if (capacity < size) {
    return (Result) {
      .ok = INVALID_SIZE,
      .error_msg = "SizeError: size is negative or capacity is less than size\n"
    };
  }
  Array_int *result = (Array_int*)malloc(sizeof(Array_int) + capacity * sizeof(int));
  if (!result) {
    return (Result) {
      .ok = HEAP_FAILURE,
      .error_msg = "AllocationError: Not enough memory in the heap"
    };
  }
  else {
    result->capacity = capacity;
    memcpy(result->data, data, size * sizeof(int));

    return (Result) {
      .ok = NO_ERROR,
      .data = result
    };
  }
}

/**
 * @fn Result from_Array_int(Array_int *from)
 * @author andarling
 * @date 20/09/2025
 * @brief return a clone to the data
 * 
 * @param from a pointer to data
 * 
 * @return a \i `Result` variable whether an error occured or not
 */
Result from_Array_int(Array_int *from) {
  if (!from) {
    return (Result) {
      .ok = SEGFAULT,
      .error_msg = "ValueError: cannot access a null pointer\n"
    };
  }
  return new_Array_int(from->data, from->capacity, from->capacity);
}

/**
 * @fn void free_Array_int(Array_int **to_delete)
 * @author andarling
 * @date 20/09/2025
 * @brief deallocate data and set pointer to NULL
 * 
 * @param to_delete a pointer to the allocated data pointer
 */
void free_Array_int(Array_int **to_delete) {
  if (!to_delete || !(*to_delete)) return;
  free(*to_delete);
  *to_delete = NULL;
}

/**
 * @fn int *get_item_Array_int(Array_int *from, size_t index)
 * @author andarling
 * @date 20/09/2025
 * @brief a substitution for operator[]
 * 
 * @param from a pointer to \i `Array_int`
 * @param index the position to get data
 * 
 * @return pointer to the data at \i `index`
 */
int *get_item_Array_int(Array_int *from, size_t index) {
  if (!from) return NULL;
  if (index < 0 || index >= from->capacity) {
    return NULL;
  }
  return from->data + index;
}

#endif // __C_DSA_INT_ARRAY__