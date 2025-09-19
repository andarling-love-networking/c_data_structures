#ifndef __C_STATUS__
#define __C_STATUS__

/**
 * @brief contains codes to error may happen in a program
 * 
 * Possible Errors:
 * IndexError
 * SizeError
 * AllocationError
 * ValueError
 */

typedef enum status_t status_t;

/**
 * @brief a collection of error codes
 * 
 * If no error happens, it is equals to 0 and if an error happens then it is
 * non-zero
 */
enum status_t {
  NO_ERROR= 0, SEGFAULT, NO_SPACE, INVALID_SIZE, HEAP_FAILURE, INVALID_INSTANCE,
  INVALID_INDEX
};

#endif // __C_STATUS__