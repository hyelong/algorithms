/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#include <string.h>

#include "prj2.h"
// prj2.h includes prj2_thread.h
#include "prj2_time.h"
#include "prj2_scheduling.h"


/*
 * Variables below can be accessed from everywhere.
 * (They have extern declarations in prj2.h)
 */
pthread_mutex_t simlock;    // critical region of simulation
pthread_cond_t  run_cv;     // cond.var. that simulates thread running
pthread_cond_t  sched_cv;   // cond.var. for scheduler to wait for event
struct timespec sim_ts;     // time when simulation begins

int run_sid = -1;           // index of thread currently running
int block_sid = -1;         // index of thread entering blocked state
int unblock_signal = 0;     // signal scheduler when thread unblocks?

const struct timespec zero_ts = { 0, 0 };
const struct timespec tick_ts = { 0, 200000000 };


/*
 * Variables below can also be accessed from prj2_scheduling.c only.
 */
thread_list_t readyQ;       // list of threads in ready state
thread_list_t blockedQ;     // list of threads in blocked state


/*
 * Variables below can also be accessed from prj2_thread.c only.
 */
thread_list_t unblockQ;     // list of threads leaving blocked state

int min_time = 1000;        // minimum total runtime of simulated thread in ms
int max_time = 1500;        // maximum total runtime of simulated thread in ms

/* Some prime numbers between 4000 and 5000:
   4001   4003   4007   4013   4019   4021   4027   4049   4051   4057 
   4073   4079   4091   4093   4099   4111   4127   4129   4133   4139 
   4153   4157   4159   4177   4201   4211   4217   4219   4229   4231 
   4241   4243   4253   4259   4261   4271   4273   4283   4289   4297 
   4327   4337   4339   4349   4357   4363   4373   4391   4397   4409 
   4421   4423   4441   4447   4451   4457   4463   4481   4483   4493 
   4507   4513   4517   4519   4523   4547   4549   4561   4567   4583 
   4591   4597   4603   4621   4637   4639   4643   4649   4651   4657 
   4663   4673   4679   4691   4703   4721   4723   4729   4733   4751 
   4759   4783   4787   4789   4793   4799   4801   4813   4817   4831 
   4861   4871   4877   4889   4903   4909   4919   4931   4933   4937 
   4943   4951   4957   4967   4969   4973   4987   4993   4999   */
// compile-time multipler to rand_r seed for varying pseudo-random sequence
const int seed_multiplier = 4001;

char *usage =\
  "\nUSAGE: %s <sched_func>[+] <num_thrds> [<min_time> <max_tim>]\n"
  "    <sched_func>: name of the scheduling function\n"
  "    <num_thrds>: number of user threads to simulate\n"
  "    <min_time>: min. run time per user thread in ms (default: 1000)\n"
  "    <max_time>: max. run time per user thread in ms (default: 1500)\n"
  "NOTE: If <sched_func> is followed immediately by '+' (without quotes),\n"
  "      unblocking user threads will signal scheduler to wake up.\n\n";


int main(int argc, char* argv[])
{
  struct timespec event_ts;   // local event timestamp

  int num_thrds = 0;        // number of user threads to simulate
  thread_data_t *tarr = NULL; // array of thread data structures

  int sel_sid = -1;           // index of thread selected by scheduler
  thread_data_t *tsel = NULL; // pointer to the selected thread

  int tmp = 0;
  int (*sched_func)() = NULL; // scheduling function picked at run time

  if (argc < 3) {
    fprintf(stderr, usage, argv[0]);
    exit(1);
  }

  tmp = strlen(argv[1]);
  if (argv[1][tmp-1] == '+') {
    unblock_signal = 1;
    argv[1][tmp-1] = '\0';
  }

  for (int i=0 ; i < NUM_SCHED ; i++) {
    if (strcmp(argv[1], MY_SCHED[i].name) == 0) {
      sched_func = MY_SCHED[i].func;
      break;
    }
  }
  if (sched_func == NULL) {
    errx(1, "Scheduling function %s not found!", argv[1]);
  }

  num_thrds = strtol(argv[2], NULL, 0);
  if (argc > 3)
    min_time = strtol(argv[3], NULL, 0);
  if (argc > 4)
    max_time = strtol(argv[4], NULL, 0);

  // Get simulation start time for logging reference
  clock_gettime(CLOCK_REALTIME, &sim_ts);

  pthread_mutex_init(&simlock, NULL);
  pthread_cond_init(&sched_cv, NULL);
  pthread_cond_init(&run_cv, NULL);
  init_thread_Q(&unblockQ, num_thrds);
  init_thread_Q(&readyQ, num_thrds);
  init_thread_Q(&blockedQ, num_thrds);

  pthread_mutex_lock(&simlock);

  // Create and fork number of threads as requested
  tarr = calloc(num_thrds, sizeof(thread_data_t));
  for (int i=0 ; i < num_thrds ; i++) {
    tarr[i].sid = i;

    // Thread is put to blocked state right after start
    tarr[i].state = BLOCKED;
    add_to_Q_back(&blockedQ, &tarr[i]);

    fork_thread(&tarr[i]);
    LOG("Thread tid=%d created with sid=%d\n", tarr[i].tid, tarr[i].sid);
  }

  run_sid = -1;         // no thread is initially running
  block_sid = -1;       // no thread is initially entering block state

  do {
    if (block_sid != -1) {
      // Scheduler was waken up by the running thread blocking
      // Handle thread entering blocked state from running state
      if (run_sid != -1)
        errx(1, "thread[%d] was blocked while thread[%d] is still running",
             block_sid, run_sid);

      add_to_Q_back(&blockedQ, &tarr[block_sid]);
      block_sid = -1;

    } else if (run_sid != -1) {
      // Scheduler was waken up by the tick_ts timeout
      // Preempt running (and non-blocking) thread to ready state
      thread_data_t *t = &tarr[run_sid];

      if (t->state != RUNNING)
        errx(1, "thread[%d] to be preempted is in %d state",
             run_sid, t->state);

      clock_gettime(CLOCK_REALTIME, &event_ts);
      t->remain_usec -= TIMEUSEC(&t->event_ts, &event_ts);
      t->event_ts = event_ts;

      LOG("%8ld: scheduler preempts running thread[%d] with remain_usec=%d\n",
          TIMEUSEC(&sim_ts, &event_ts), run_sid, t->remain_usec);

      // Change the preempted thread into ready state
      t->state = READY;
      add_to_Q_back(&readyQ, t);
      run_sid = -1;
      // Signal the thread to stop running
      pthread_cond_signal(&run_cv);
    }

    while (unblockQ.head >= 0) {
      // Handle threads unblocking from blocked state into ready state
      thread_data_t *t = remove_from_Q_front(&unblockQ);

      clock_gettime(CLOCK_REALTIME, &event_ts);
      t->event_ts = event_ts;

      LOG("%8ld: scheduler changes thread[%d] with remain_usec=%d to ready\n",
          TIMEUSEC(&sim_ts, &event_ts), t->sid, t->remain_usec);

      // Change the unblocking thread into ready state
      t->state = READY;
      remove_from_Q(&blockedQ, t->sid);
      add_to_Q_back(&readyQ, t);
      // Signal the thread to become formally unblocked
      pthread_cond_signal(&t->block_cv);
    }

    if (unblockQ.head >= 0)     // unblockQ is not empty
      errx(1, "unblockQ has pending threads from %d to %d!?!",
           unblockQ.head, unblockQ.tail);
    if (run_sid != -1)
      errx(1, "scheduler is running with running thread[%d]!?!", run_sid);
    if (block_sid != -1)
      errx(1, "thread[%d] was blocking but not handled!?!", block_sid);

    if (readyQ.head == -1 && blockedQ.head == -1) {
      // no thread is running, neither in ready or blocked list
      clock_gettime(CLOCK_REALTIME, &event_ts);
      LOG("%8ld: all threads appear to have terminated\n",
          TIMEUSEC(&sim_ts, &event_ts));
      break;
    }

    if (tsel != NULL && tsel->state == RUNNING) {
      // Scheduler was waken up (by unblocking or terminating threads) before
      // last selected thread could startrunning -- do not select again
      /*** Do nothing ***/

    } else {
      // Either scheduler did not select a thread last time, or the selected
      // thread is not running any more (blocked, preempted or finished)

      // Run the scheduling algorithm to select a new thread
      sel_sid = sched_func();

      clock_gettime(CLOCK_REALTIME, &event_ts);

      if (sel_sid < 0) {
        tsel = NULL;
        LOG("%8ld: scheduler cannot find any thread to run\n",
            TIMEUSEC(&sim_ts, &event_ts));

      } else {
        tsel = &tarr[sel_sid];

        if (tsel->state != READY)
          errx(1, "scheduler selects thread[%d] not in ready state", sel_sid);

        LOG("%8ld: scheduler selects thread[%d] with remain_usec=%d to run\n",
            TIMEUSEC(&sim_ts, &event_ts), sel_sid, tsel->remain_usec);

        // Change the selected thread to running state
        tsel->state = RUNNING;
        remove_from_Q(&readyQ, tsel->sid);
        // Signal the selected thread to run
        pthread_cond_signal(&tsel->ready_cv);
      }
    }

    // Scheduler wait for either a signal or tick_ts until next preemption
    timeadd(&event_ts, &event_ts, &tick_ts);
    pthread_cond_timedwait(&sched_cv, &simlock, &event_ts);

  } while (1);

  pthread_mutex_unlock(&simlock);
  sched_yield();

  for (int i=0 ; i < num_thrds ; i++) {
    int rv;
    int tid = wait(&rv);        // wait for an (only) child to exit
    LOG("Thread tid=%d exited with status %d\n", tid, WEXITSTATUS(rv));
  }

  for (int i=0 ; i < num_thrds ; i++) {
    clear_thread(&tarr[i]);
  }
  free(tarr);

  destroy_thread_Q(&unblockQ);
  pthread_mutex_destroy(&simlock);
  pthread_cond_destroy(&sched_cv);
  pthread_cond_destroy(&run_cv);
  return 0;
}
