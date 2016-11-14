/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#include "prj2.h"
// prj2.h includes prj2_thread.h
#include "prj2_time.h"

extern thread_list_t unblockQ;
extern int min_time;
extern int max_time;
extern int seed_multiplier;


int thread_execution(void *p)
{
  int runN = 0;
  struct timespec next_ts;
  thread_data_t  *t = (thread_data_t *)p;
  unsigned int seed = (t->sid+1) * seed_multiplier;

  // Generate a random total runtime for the thread
  timerand_ms(&next_ts, &seed, min_time, max_time);
  t->remain_usec = TIMEUSEC(&zero_ts, &next_ts);

  pthread_mutex_lock(&simlock);

  clock_gettime(CLOCK_REALTIME, &t->event_ts);
  t->start_usec = TIMEUSEC(&sim_ts, &t->event_ts);
  LOG("%8ld: thread[%d] is starting with remain_usec=%d\n",
      t->start_usec, t->sid, t->remain_usec);

  // Thread is initially blocked tick time right after started
  next_ts = tick_ts;

  while (t->remain_usec > 0) {
    int  rv;
    int  next_usec;

    switch (t->state) {

    case RUNNING:
      runN ++;

      // Update next_ts so it's not more than t->remain_usec
      next_usec = TIMEUSEC(&zero_ts, &next_ts);
      if (next_usec - t->remain_usec > 0) {
        timesubusec(&next_ts, &next_ts, next_usec - t->remain_usec);
        next_usec = t->remain_usec;
      }

      clock_gettime(CLOCK_REALTIME, &t->event_ts);
      LOG("%8ld: thread[%d] with remain_usec=%d begins run#%d"
          " for up to %.1f msec\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, t->remain_usec, runN,
          TIMEUSEC(&zero_ts, &next_ts)/1000.0);

      // Calculate the ending time of the run period
      timeadd(&next_ts, &t->event_ts, &next_ts);

      // The simulated thread "runs" by setting run_sid to simulated thread ID
      // while making the *real* thread wait on condition variable run_cv
      run_sid = t->sid;
      rv = pthread_cond_timedwait(&run_cv, &simlock, &next_ts);

      if (t->state == READY) {
        // Thread was preempted by scheduler to ready state
        // Calculate the remaining time in the run period
        // t->event_ts should have been set to preemption time by scheduler
        timesub(&next_ts, &next_ts, &t->event_ts);

      } else if (t->state == RUNNING && run_sid == -1) {
        // Thread was preempted and selected right back to running state
        // Calculate the remaining time in the run period
        // t->event_ts should have been set to preemption time by scheduler
        timesub(&next_ts, &next_ts, &t->event_ts);

      } else {
        // Thread finished the run period

        if (rv == 0)
          errx(1, "thread[%d] was preempted when in %d state, run_sid=%d",
               t->sid, t->state, run_sid);
        if (rv != ETIMEDOUT)
          errx(1, "thread[%d] failed timedwait on run_cv, rv=%d", t->sid, rv);
        if (t->state != RUNNING)
          errx(1, "thread[%d] finished run not in running state!?!", t->sid);

        // rv == ETIMEDOUT && t->state == RUNNING

        clock_gettime(CLOCK_REALTIME, &next_ts);
        t->remain_usec -= TIMEUSEC(&t->event_ts, &next_ts);
        t->event_ts = next_ts;

        LOG("%8ld: thread[%d] with remain_usec=%d finished run#%d\n",
            TIMEUSEC(&sim_ts, &next_ts), t->sid, t->remain_usec, runN);

        if (t->remain_usec > 0) {
          // Thread enters block period
          t->state = BLOCKED;
          run_sid = -1;
          block_sid = t->sid;

          // Generate the duration of the next block time
          timerand_ms(&next_ts, &seed, 200, 300);

        } else {
          // Thread terminates
          t->remain_usec = 0;
          t->state = TERMINATED;
          run_sid = block_sid = -1;
        }

        // Signals scheduler to select another thread to run
        pthread_cond_signal(&sched_cv);
      }
      break;

    case READY:
      clock_gettime(CLOCK_REALTIME, &t->event_ts);
      LOG("%8ld: thread[%d] with remain_usec=%d is ready for run#%d\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, t->remain_usec, runN);

      // Thread waits until scheduler signals it to run
      pthread_cond_wait(&t->ready_cv, &simlock);
      break;

    case BLOCKED:
      clock_gettime(CLOCK_REALTIME, &t->event_ts);
      LOG("%8ld: thread[%d] enters block#%d for %.1f msec\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, runN,
          TIMEUSEC(&zero_ts, &next_ts)/1000.0);

      // Calculate the ending time of the block period
      timeadd(&next_ts, &t->event_ts, &next_ts);

      // The simulated thread "blocks" by making the *real* thread wait on
      // condition variable block_cv
      rv = pthread_cond_timedwait(&t->block_cv, &simlock, &next_ts);

      if (t->state != BLOCKED)
        errx(1, "thread[%d] finished block not in blocked state!?!", t->sid);
      if (rv == 0)
        errx(1, "thread[%d] was preempted in block state!", t->sid);
      if (rv != ETIMEDOUT)
        errx(1, "thread[%d] failed timedwait on block_cv, rv=%d", t->sid, rv);

      clock_gettime(CLOCK_REALTIME, &t->event_ts);
      LOG("%8ld: thread[%d] finished block#%d\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, runN);

      // Thread adds itself to unblock queue, so scheduler can move the
      // thread formally from blocked to ready state
      add_to_Q_back(&unblockQ, t);

      if (unblock_signal) {
        pthread_cond_signal(&sched_cv);
      }

      // Wait for scheduler to formally unblock thread
      pthread_cond_wait(&t->block_cv, &simlock);

      // Generate the duration of the next run
      timerand_ms(&next_ts, &seed, 300, 800);
      break;

    default:
      errx(1, "Invalid thread[%d] state: %d!!", t->sid, t->state);
    }
  };

  clock_gettime(CLOCK_REALTIME, &next_ts);
  t->term_usec = TIMEUSEC(&sim_ts, &next_ts);
  LOG("%8ld: thread[%d] terminated\n", t->term_usec, t->sid);

  // Inform the scheduling that thread has terminated
  pthread_cond_signal(&sched_cv);

  pthread_mutex_unlock(&simlock);
  return 0;
}


void fork_thread(thread_data_t *t)
{
  // allocate stack space for the thread
  if ((t->stack = malloc(STACK_SIZE)) == NULL) {
    t->tid = 0;
    warn("malloc() failed for thread[%d]", t->sid);
    return;
  }

  // stack grows downward
  t->stackTop = t->stack + STACK_SIZE;

  // condition variable used to synchronize event simulation
  pthread_cond_init(&t->block_cv, NULL);
  pthread_cond_init(&t->ready_cv, NULL);

  t->tid = clone(thread_execution, t->stackTop, SIGCHLD|CLONE_VM, t);
    if (t->tid == -1) {
      warn("clone() failed for thread[%d]", t->sid);
    }
}


void clear_thread(thread_data_t *t)
{
  if (t->tid != 0) {
    pthread_cond_destroy(&t->block_cv);
    pthread_cond_destroy(&t->ready_cv);
    free(t->stack);
  }
}

