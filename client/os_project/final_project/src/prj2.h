/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#ifndef PRJ2_H
#define PRJ2_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <time.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sched.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdarg.h>

#include "prj2_thread.h"
#include "multicore_sim.h"

extern pthread_mutex_t simlock; // critical region of simulation
extern pthread_cond_t  run_cv;  // cond.var. that simulates thread running
extern pthread_cond_t  sched_cv;// cond.var. for scheduler to wait for event
extern struct timespec sim_ts;  // time when simulation begins

extern const struct timespec tick_ts;
extern const struct timespec affinity_ts;  //the time for core build up affinity (build private cache state)

//extern int run_sid;             // index of thread currently running
//extern int block_sid;           // index of thread entering block state
extern int unblock_signal;      // signal scheduler when thread unblocks?
extern int affinity_enabled;    //flag for cpu affinity

extern const struct timespec zero_ts;
extern const struct timespec tick_ts;

extern thread_list_t global_waitingQ;  //list of threads waiting for dispatching to cores

extern thread_data_t *tarr;        // array of thread data structures
extern core_data_t *carr;        // array of thread data structures

extern int (*sched_func)(core_data_t*); // scheduling function picked at run time
extern int (*balance_func)(core_data_t*); // balance function picked at run time
extern int num_cores;  //number of cores
extern int num_thrds;        // number of user threads to simulate

extern char* threads_data_filename;  //thread and core binding information

extern int is_terminated;

#define LOG(...)                    \
  do {                              \
    printf(__VA_ARGS__);            \
  } while (0)


void core_log(core_data_t* c, const char *templ, ...);

#endif //PRJ2_H
