/**
 * Code for SCU COEN283 Winter 2015 PRJ2
 * @author: Edward Yang <yyang@scu.edu>
 * @author: Your Name <username@scu.edu> m/d/y
 */
#ifndef PRJ2_SCHEDULING_H
#define PRJ2_SCHEDULING_H

#include "multicore_sim.h"
#define NUM_SCHED   4
typedef struct {
  char *name;
  int (*func)(core_data_t*);
} name_func_t;

extern name_func_t MY_SCHED[];

#endif //PRJ2_SCHEDULING_H