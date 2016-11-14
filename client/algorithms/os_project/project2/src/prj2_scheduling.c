/**
 * Code for SCU COEN283 Winter 2015 PRJ2
 * @author: Yi-Hua Edward Yang <yyang@scu.edu>
 * @author: Your Name <username@scu.edu> m/d/y
 */

#include "prj2_thread.h"
#include "prj2_scheduling.h"

#include <limits.h>

extern thread_list_t readyQ;
extern thread_list_t blockedQ;


/**
 * Select a ready thread with the lowest simulated thread ID (sid) to run.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int static_priority()
{
  return -1;
}


/**
 * Select a ready thread with the most remain_usec to run.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int most_remaining_time()
{
  return -1;
}


/**
 * Select the next thread in the ready queue.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int round_robin_queue()
{
  return -1;
}


/**
 * Select a ready thread with the nearest next thread ID.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int round_robin_static()
{
  return -1;
}


name_func_t MY_SCHED[NUM_SCHED] = {
  {"static_priority", static_priority},
  {"most_remaining_time", most_remaining_time},
  {"round_robin_queue", round_robin_queue},
  {"round_robin_static", round_robin_static}
};
