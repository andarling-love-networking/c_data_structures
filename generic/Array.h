/**
 * @file Array.h
 * @author andarling
 * @date 20/09/2025
 * @brief a normal array library with compact attributes into \c `Array`
 */
#ifndef __C_DSA_GENERIC_ARRAY__
#define __C_DSA_GENERIC_ARRAY__

#include <stdlib.h>
#include <string.h>

#include "../utils/Result.h"
#include "../utils/status.h"

typedef struct Array Array;
/**
 * @struct Array_int
 * @author andarling
 * @date 20/09/2025
 * @brief a struct for normal generic array
 */
struct Array {
  size_t capacity, type_size;
  char data[];
};

/**
 * @fn Result new_Array(int *data, size_t size, size_t capacity, size_t type_size)
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
 * @param type_size the size in bytes of each elemenets should be in the container
 * (\i `type_size` cannot be less than 1)
 * 
 * @return a \i `Result` variable indicating an error or if no error, the 
 * allocated data
 */
Result new_Array(void *data, size_t size, size_t capacity, size_t type_size) {
  if (!data) {
    size = 0;
  }
  if (capacity < size) {
    return (Result) {
      .ok = INVALID_SIZE,
      .error_msg = "SizeError: size is negative or capacity is less than size\n"
    };
  }
  if (type_size <= 0) {
    return (Result) {
      .ok = INVALID_SIZE,
      .error_msg = "SizeError: Type cannot have less than 1 byte\n"
    };
  }

  Array *result = (Array*)malloc(sizeof(Array) + capacity * type_size);
  if (!result) {
    return (Result) {
      .ok = HEAP_FAILURE,
      .error_msg = "AllocationError: Not enough memory in the heap"
    };
  }
  else {
    result->capacity = capacity, result->type_size = type_size;
    memcpy(result->data, data, size * type_size);

    return (Result) {
      .ok = NO_ERROR,
      .data = result
    };
  }
}

/**
 * @fn Result from_Array(Array *from)
 * @author andarling
 * @date 20/09/2025
 * @brief return a clone to the data
 * 
 * @param from a pointer to data
 * 
 * @return a \i `Result` variable whether an error occured or not
 */
Result from_Array(Array *from) {
  if (!from) {
    return (Result) {
      .ok = SEGFAULT,
      .error_msg = "ValueError: cannot access a null pointer\n"
    };
  }
  return new_Array(from->data, from->capacity, from->capacity, from->type_size);
}

/**
 * @fn void free_Array(Array **to_delete)
 * @author andarling
 * @date 20/09/2025
 * @brief deallocate data and set pointer to NULL
 * 
 * @param to_delete a pointer to the allocated data pointer
 */
void free_Array(Array **to_delete) {
  if (!to_delete || !(*to_delete)) return;
  free(*to_delete);
  *to_delete = NULL;
}

/**
 * @fn void *get_item_Array(Array *from, size_t index)
 * @author andarling
 * @date 20/09/2025
 * @brief a substitution for operator[]
 * 
 * @param from a pointer to \i `Array`
 * @param index the position to get data
 * 
 * @return pointer to the data at \i `index`
 */
void *get_item_Array(Array *from, size_t index) {
  if (!from) return NULL;
  if (index < 0 || index >= from->capacity) {
    return NULL;
  }
  return from->data + index * from->type_size;
}

#endif // __C_DSA_GENERIC_ARRAY__