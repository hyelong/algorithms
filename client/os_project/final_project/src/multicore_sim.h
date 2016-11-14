/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#ifndef MULTICORE_SIM_H
#define MULTICORE_SIM_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>

#include "prj2_thread.h"

// stack size of a thread
#define  CORE_STACK_SIZE  (32*1024*1024)
/**
 * data structure of a core
 */
typedef struct {
  int  tid;             // Host thread ID for logging purpose
  int  cid;             // Simulated core ID (index in core array)

  char *stack;          // thread-specific stack memory for clone
  char *stackTop;       // stack growing downward

  pthread_mutex_t simlock;  // critical region of simulation for each core
                                //using this lock to avoid more than one thread runs 
                                 //on the same core at the same time.
  pthread_cond_t  run_cv;     // core private cond.var. that simulates thread running
  pthread_cond_t  sched_cv;   // core private cond.var. for scheduler to wait for event
  
  thread_list_t readyQ;       // list of threads in ready state
  thread_list_t blockedQ;     // list of threads in blocked state
  thread_list_t unblockQ;     // list of threads leaving blocked state
  
  int run_sid; // index of thread currently running in this core
  int block_sid; // index of thread currently blocked in this core

} core_data_t;


/**
 * a circular list of core_data_t
 */
typedef struct {
  core_data_t **cparr;      // array of core pointers
  int    max_size;          // maximum size of the list
  int    head;              // first occupied slot in cparr, -1 if empty
  int    tail;              // first empty slot in cparr, -1 if full
} core_list_t;

int core_execution(void *p);
void fork_core(core_data_t *t);
void clear_core(core_data_t *t);

#endif //MULTICORE_SIM_H
