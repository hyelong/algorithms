#ifndef BALANCE_FUNC_H
#define BALANCE_FUNC_H

#include "multicore_sim.h"

#define NUM_BALANCE   3
typedef struct {
  char *name;
  int (*func)(core_data_t*);
} bal_name_func_t;

extern bal_name_func_t MY_BALANCE[];



#endif //BALANCE_FUNC_H