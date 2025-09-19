/**
 * @file Array.h
 * @brief a structured array header
 * @author andarling
 * @date 19/09/2025
 * 
 * @details This library introduces a structure \c `StrictArray_int` that behaves the 
 * same as normal array of integers but is allocated explicitly on heap, and 
 * also have the \i `size` and \i `capacity` attributes.
 * 
 * StrictArray_int's APIs:
 * @li new_T : dynamically create type T on the heap
 * @li from_T : dynamically clone type T on the heap of the same type
 * @li free_T : deallocate type T
 * @li push_back_T : insert data to type T on last position
 * @li pop_back_T : remove last element in type T
 * @li clear_T : reset the data in T
 */
#ifndef __C_DSA_INT_STRICT_ARRAY_H__
#define __C_DSA_INT_STRICT_ARRAY_H__


#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../utils/status.h"
#include "../utils/Result.h"

typedef struct StrictArray_int StrictArray_int;

/**
 * @struct StrictArray_int
 * @author andarling
 * @date 19/09/2025
 * @brief a structure represent traditional C-array stricter for speed purpose
 * 
 * This type includes the pointer to the array (dynamically allocated) and the
 * size and capacity attribute, note that once the \i `size` reach \i `capacity` 
 * then the array is no longer insertable.
 * \b `Stricter` means the only operation available is inserting and removing at the
 * back, read and change data at any point.
 */
struct StrictArray_int {
  size_t size, capacity; 
  int data[];
};

/**
 * @fn Result new_StrictArray_int(int *data, size_t size, size_t cap)
 * @author andarling
 * @date 19/09/2025
 * @brief returns a \c `Result` type to the allocation
 * 
 * This type return an error code of non-zero if an error occured and a error message,
 * or the successfully allocated data is returned with code 0.
 * It is better to get the returned \i `data` through get_data(*from, **to)
 * 
 * @param[in] data a pointer to an array
 * (if null pointer then defaults to 0 elements in array)
 * @param[in] size the size of the \i `data` array
 * (size >= 0)
 * @param[in] cap the desired capacity of the rertured \c `StrictArray_int`
 * (cap >= size)
 * 
 * @return a \c `Result` type to the successfully allocated data or a error message
 */
Result new_StrictArray_int(int *data, size_t size, size_t cap) {
  if (!data) {
    size = 0;
  }
  if (size < 0 || cap < size) {
    return (Result) {
      .ok = INVALID_SIZE,
      .error_msg = "SizeError: size is negative or capacity is less than size\n"
    };
  }

  StrictArray_int *result = (StrictArray_int*)malloc(sizeof(StrictArray_int) + sizeof(int) * cap);
  if (!result) {
    return (Result) {
      .ok = HEAP_FAILURE,
      .error_msg = "AllocationError: Not enough memory in the heap"
    };
  }
  else {
    result->size = size, result->capacity = cap;
    memcpy(result->data, data, size * sizeof(int));

    for (int i = 0; i < size; i++) {
      printf("%d, ", *((int*)data + i));
    } printf("\n");

    return (Result) {
      .ok = NO_ERROR,
      .data = result
    };
  }
}

/**
 * @fn Result from_StrictArray_int(StrictArray_int *from)
 * @author andarling
 * @date 19/09/2025
 * @brief creates a copy of an existed \c `StrictArray_int`
 * 
 * @param[in] from an existed \c `StrictArray_int` instance
 * (from is not a null pointer)
 * 
 * @return the \c `Result` type of the successfully allocated data or an error message
 */
Result from_StrictArray_int(StrictArray_int *from) {
  if (!from) {
    return (Result) {
      .ok = SEGFAULT,
      .error_msg = "ValueError: cannot access a null pointer\n"
    };
  }

  StrictArray_int *result = (StrictArray_int*)malloc(
    sizeof(StrictArray_int) + from->capacity * sizeof(int)
  );
  if (!result) {
    return (Result) {
      .ok = HEAP_FAILURE,
      .error_msg = "AllocationError: Not enough memory in the heap\n"
    };
  }
  else {
    result->capacity = from->capacity, result->size = from->size;
    memcpy(result->data, from->data, from->capacity * sizeof(int));
    return (Result) {
      .ok = NO_ERROR,
      .data = result
    };
  }
}

/**
 * @fn void free_StrictArray_int(StrictArray_int **arr)
 * @author andarling
 * @date 19/09/2025
 * @brief deallocate the data and set the pointer to NULL
 * 
 * @param[in] arr a pointer to pointer of the data
 * (if arr is a null pointer then exits the function)
 * 
 * @return void
 */
void free_StrictArray_int(StrictArray_int **arr) {
  if (!arr) return;
  free(*arr);
  *arr = NULL;
}


/**
 * @fn push_back_StrictArray_int(StrictArray_int *arr, int data)
 * @author andarling
 * @date 19/09/2025
 * @brief insert \i `data` to the end of the array
 * 
 * @param[in] arr a pointer to \c `StrictArray_int` type
 * (if arr is a null pointer then an error of invalid instance is returned)
 * @param[in] data a value to insert
 * 
 * @return 0 if success and non-zero if an error occurs
 */
status_t push_back_StrictArray_int(StrictArray_int *arr, int data) {
  if (!arr) return SEGFAULT;
  size_t size = arr->size, cap = arr->capacity;
  if (size == cap) {
    return NO_SPACE;
  }
  arr->data[size] = data;
  arr->size++;
  return NO_ERROR;
}

/**
 * @fn void pop_back_StrictArray_int(StrictArray_int *arr)
 * @author andarling
 * @date 19/09/2025
 * @brief remove the last elements in \c `StrictArray_int`
 * 
 * @param[in] arr a pointer to \c `StrictArray_int` type
 * (if arr is a null pointer then exits the function)
 * 
 * @return void
 */
void pop_back_StrictArray_int(StrictArray_int *arr) {
  if (!arr) return;
  if (arr->size) arr->size--;
}

/**
 * @fn clear_StrictArray_int(StrictArray_int *arr)
 * @author andarling
 * @date 19/09/2025
 * @brief remove all elements in array
 * 
 * clear all values and set them to 0
 * 
 * @param[in] arr a pointer to \c `StrictArray_int` type
 * (if arr is a null pointer then exits the function)
 * 
 * @return void
 */
void clear_StrictArray_int(StrictArray_int *arr) {
  if (!arr) return;
  arr->size = 0;
}

/**
 * @fn int *get_item(size_t index)
 * @author andarling
 * @date 19/09/2025
 * @brief return a pointer to the \i `index`-th element
 * 
 * @param index the position of the output integer point to
 * 
 * @return a pointer to \i `index`-th interger, if \i `index` is out of bound
 * (not in [0, \i `index` - 1]) then a null pointer is returned
 */
int *get_item_StrictArray_int(StrictArray_int *arr, size_t index) {
  if (index < 0 || index >= arr->size) return NULL;
  else {
    return arr->data + index;
  }
}

#endif // __C_DSA_INT_STRICT_ARRAY_H__