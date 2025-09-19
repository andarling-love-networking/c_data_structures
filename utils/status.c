#ifndef __C_STATUS__
#define __C_STATUS__

typedef enum status_t status_t;

/**
 * @brief a collection of error codes
 * 
 * If no error happens, it is equals to 0 and if an error happens then it is
 * non-zero
 */
enum status_t {
  NO_ERROR= 0, SEGFAULT, NO_SPACE
};

#endif // __C_STATUS__