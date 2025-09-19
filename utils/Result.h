#ifndef __C_DSA_UTILS_RESULT__
#define __C_DSA_UTILS_RESULT__

#include "status.h"
#include <stdlib.h>

typedef struct Result Result;

/**
 * @breif this type make sure the user know if something went wrong with data creation
 * 
 * The Result type will have an error code with status_t type and the user can
 * read the detailed error message with  error_msg,
 * else it return a void pointer to the data (must be allocated dynamically)
 */
struct Result {
  status_t ok;
  union {
    const char *error_msg;
    void *data;
  };
};
/**
 * @fn const char *get_data_p(Result *from, void **to)
 * @brief get the data from Result type
 * 
 * @param from The result obtained
 * @param to The pointer to a pointer of the desired type
 * 
 * @return a message if an error occured, else a null pointer
 */
const char *get_data_p(Result *from, void **to) {
  if (from == NULL || to == NULL) {
    return "ValueError: cannot access a null pointer.\n";
  }
  if (from->ok != NO_ERROR) {
    *to = NULL;
    return from->error_msg;
  }
  else {
    *to = from->data;
    return NULL;
  }
}

const char *get_data(Result from, void **to) {
  if (to == NULL) return NULL;
  if (from.ok != NO_ERROR) return from.error_msg;
  else {
    *to = from.data;
  }
}

#endif // C_DSA_UTILS_RESULT__