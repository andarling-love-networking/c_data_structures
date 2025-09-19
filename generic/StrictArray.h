/**
 * @file Array.h
 * @brief a generic strict array header
 * @author andarling
 * @date 19/09/2025
 * 
 * @details This library introduces a structure \c `StrictArray` that behaves the 
 * same as normal array of \b `any types` but is allocated explicitly on heap, and 
 * also have the \i `size` and \i `capacity` attributes.
 * For generic concept, a \i `type_size` is added to every generic data structure.
 * \b `Strictness` in array means that values can only be appended and deleted on 
 * last position, but elements can be changes or subsituted on any place. Any 
 * way to index elements out side of [0, \i `size` - 1] is undefined and the
 * only safe way to index is through \c `get_item(index)`.
 * 
 * Array's APIs:
 * @li new_T : dynamically create type T on the heap
 * @li from_T : dynamically clone type T on the heap of the same type
 * @li free_T : deallocate type T
 * @li push_back_T : insert data to type T on last position
 * @li pop_back_T : remove last element in type T
 * @li get_item_T : get the pointer to item on \i `index`
 * @li clear_T : reset the data in T
 */
#ifndef __C_DSA_GENERIC_STRICT_ARRAY_H__
#define __C_DSA_GENERIC_STRICT_ARRAY_H__


#include <stdlib.h>
#include <string.h>

#include "../utils/status.h"
#include "../utils/Result.h"

typedef struct StrictArray StrictArray;

/**
 * @struct StrictArray
 * @author andarling
 * @date 19/09/2025
 * @brief a structure represent traditional C-array but stricter to increase speed
 * 
 * This type includes the pointer to the array (dynamically allocated) and the
 * size and capacity attribute, note that once the \i `size` reach \i `capacity` 
 * then the array is no longer appendable.
 * To support Generic concept in C, every data structure must be \b `dynamically`
 * allocated, as \c `Result` type only acceps a pointer to data.
 */
struct StrictArray {
  size_t size, capacity, type_size;
  char data[];
};

/**
 * @fn Result new_StrictArray(int *data, size_t type_size, size_t size, size_t cap)
 * @author andarling
 * @date 19/09/2025
 * @brief returns a \c `Result` type to the allocation
 * 
 * This type return an error code of non-zero if an error occured and a error message,
 * or the successfully allocated data is returned with code 0.
 * It is better to get the returned \i `data` through \c `get_data(*from, **to)`
 * 
 * @param[in] data a pointer to an array
 * (if null pointer then defaults to 0 elements in array)
 * @param[in] type_size size of every elements in the array
 * (type_size > 0)
 * @param[in] size the size of the \i `data` array
 * (size >= 0)
 * @param[in] cap the desired capacity of the rertured \c `StrictArray`
 * (cap >= size)
 * 
 * @return a \c `Result` type to the successfully allocated data or a error message
 */
Result new_StrictArray(void *data, size_t type_size, size_t size, size_t cap) {
  if (!data) {
    size = 0;
  }
  if (size < 0 || cap < size) {
    return (Result) {
      .ok = INVALID_SIZE,
      .error_msg = "SizeError: Size is negative or capacity is less than size\n"
    };
  }
  if (type_size <= 0) {
    return (Result) {
      .ok = INVALID_SIZE,
      .error_msg = "SizeError: Type cannot have less than 1 byte\n"
    };
  }

  StrictArray *result = (StrictArray*)malloc(sizeof(StrictArray) + type_size * cap);
  if (!result) {
    return (Result) {
      .ok = HEAP_FAILURE,
      .error_msg = "AllocationError: Not enough memory in the heap"
    };
  }
  else {
    result->size = size, result->capacity = cap, result->type_size = type_size;
    memcpy(result->data, data, size * type_size);
    return (Result) {
      .ok = NO_ERROR,
      .data = result
    };
  }
}

/**
 * @fn Result from_StrictArray(StrictArray *from)
 * @author andarling
 * @date 19/09/2025
 * @brief creates a copy of an existed \c `StrictArray`
 * 
 * @param[in] from an existed \c `StrictArray` instance
 * (from is not a null pointer)
 * 
 * @return the \c `Result` type of the successfully allocated data or an error message
 */
Result from_StrictArray(StrictArray *from) {
  if (!from) {
    return (Result) {
      .ok = SEGFAULT,
      .error_msg = "ValueError: cannot access a null pointer\n"
    };
  }

  StrictArray *result = (StrictArray*)malloc(
    sizeof(StrictArray) + from->capacity * from->type_size
  );
  if (!result) {
    return (Result) {
      .ok = HEAP_FAILURE,
      .error_msg = "AllocationError: Not enough memory in the heap\n"
    };
  }
  else {
    result->capacity = from->capacity, result->size = from->size;
    memcpy(result->data, from->data, from->size * from->type_size);
    return (Result) {
      .ok = NO_ERROR,
      .data = result
    };
  }
}

/**
 * @fn void free_StrictArray(StrictArray **arr)
 * @author andarling
 * @date 19/09/2025
 * @brief deallocate the data and set the pointer to NULL
 * 
 * @param[in] arr a pointer to the address of the data
 * (if arr is a null pointer then exits the function)
 * 
 * @return void
 */
void free_StrictArray(StrictArray **arr) {
  if (!arr || !*arr) return;
  free(*arr);
  *arr = NULL;
}


/**
 * @fn push_back_StrictArray(StrictArray *arr, int value)
 * @author andarling
 * @date 19/09/2025
 * @brief insert \i `value` to the end of the array
 * 
 * @param[in] arr a pointer to \c `StrictArray` type
 * (if arr is a null pointer then an error of invalid instance is returned)
 * @param[in] value a value to insert
 * 
 * @return 0 if success and non-zero if an error occurs
 */
status_t push_back_StrictArray(StrictArray *arr, void *value) {
  size_t size = arr->size, type_size = arr->type_size;
  if (!arr) return SEGFAULT;
  if (size == arr->capacity) {
    return NO_SPACE;
  }
  memcpy(arr->data + type_size * size, value, type_size);
  arr->size++;
  return NO_ERROR;
}


/**
 * @fn void pop_back_StrictArray(StrictArray *arr)
 * @author andarling
 * @date 19/09/2025
 * @brief remove the last elements in \c `StrictArray`
 * 
 * @param[in] arr a pointer to \c `StrictArray` type
 * (if arr is a null pointer then exits the function)
 * 
 * @return void
 */
void pop_back_StrictArray(StrictArray *arr) {
  if (!arr) return;
  if (arr->size) arr->size--;
}

/**
 * @fn clear_StrictArray(StrictArray *arr)
 * @author andarling
 * @date 19/09/2025
 * @brief remove all elements in array
 * 
 * clear all values and set them to \i `default`
 * 
 * @param[in] arr a pointer to \c `StrictArray` type
 * (if arr is a null pointer then exits the function)
 * 
 * @return void
 */
void clear_StrictArray(StrictArray *arr) {
  if (!arr) return;
  arr->size = 0;
}

/**
 * @fn void *get_item(StrictArray *arr, size_t index)
 * @author andarling
 * @date 19/09/2025
 * @brief return a pointer to the desired elements
 * 
 * This function returns a pointer to the desired elements, if it is out-of-bound
 * (outside of [0, \c `size` - 1]), the output is a null pointer
 */
void *get_item(StrictArray *arr, size_t index) {
  if (index < 0 && index >= arr->size) {
    return NULL;
  }
  return arr->data + arr->type_size * index;
}

#endif // __C_DSA_GENERIC_STRICT_ARRAY_H__