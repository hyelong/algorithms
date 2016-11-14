/**
 * Code for SCU COEN283 Winter 2015 PRJ2
 * @author: Edward Yang <yyang@scu.edu>
 * @author: Your Name <username@scu.edu> m/d/y
 */
#define _GNU_SOURCE
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>
#include <signal.h>
#include <sched.h>

#include "prj2_scheduling.h"  //include name_func_t
#include "prj2_thread.h"
#include "prj2.h"
#include "prj2_time.h"

#define NUM_DISPATCH 1

extern name_func_t MY_DISPATCH[];

#define DEFALT_STACK_SIZE (16 * 1024 * 1024)

int scheduler_execution();
int dispatcher_execution();
void fork_dispatcher();


void clear_scheduler_dispather();

