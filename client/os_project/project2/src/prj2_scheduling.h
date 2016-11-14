/**
 * Code for SCU COEN283 Winter 2015 PRJ2
 * @author: Edward Yang <yyang@scu.edu>
 * @author: Your Name <username@scu.edu> m/d/y
 */

#define NUM_SCHED   4
typedef struct {
  char *name;
  int (*func)();
} name_func_t;

extern name_func_t MY_SCHED[];
