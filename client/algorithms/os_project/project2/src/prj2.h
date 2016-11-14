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

#include "prj2_thread.h"

extern pthread_mutex_t simlock; // critical region of simulation
extern pthread_cond_t  run_cv;  // cond.var. that simulates thread running
extern pthread_cond_t  sched_cv;// cond.var. for scheduler to wait for event
extern struct timespec sim_ts;  // time when simulation begins

extern int run_sid;             // index of thread currently running
extern int block_sid;           // index of thread entering block state
extern int unblock_signal;      // signal scheduler when thread unblocks?

extern const struct timespec zero_ts;
extern const struct timespec tick_ts;


#define LOG(...)                    \
  do {                              \
    printf("[run=%2d, block=%2d]",  \
           run_sid, block_sid);     \
    printf(__VA_ARGS__);            \
  } while (0)

#endif //PRJ2_H
