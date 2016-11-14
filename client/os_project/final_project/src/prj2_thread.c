/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#include "prj2.h"
// prj2.h includes prj2_thread.h
#include "prj2_time.h"

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
  if(t->cid == -1){
    pthread_cond_wait(&t->core_cv, &simlock);
  }
  pthread_mutex_unlock(&simlock);

  //request per core lock
  //pthread_mutex_lock(&carr[t->cid].simlock);

  clock_gettime(CLOCK_REALTIME, &t->event_ts);
  t->start_usec = TIMEUSEC(&sim_ts, &t->event_ts);
  core_log(NULL, "%8ld: thread[%d] at core[%d] is starting with remain_usec=%d\n",
      t->start_usec, t->sid, t->cid, t->remain_usec);

  // Thread is initially blocked tick time right after started
  next_ts = tick_ts;

  while (t->remain_usec > 0) {
    int  rv;
    int  next_usec;
    int last_cid = t->cid;
    pthread_mutex_lock(&carr[last_cid].simlock);
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
      core_log(&carr[t->cid], "%8ld: thread[%d] with remain_usec=%d begins run#%d"
          " for up to %.1f msec\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, t->remain_usec, runN,
          TIMEUSEC(&zero_ts, &next_ts)/1000.0);

      // Calculate the ending time of the run period
      timeadd(&next_ts, &t->event_ts, &next_ts);

      // The simulated thread "runs" by setting run_sid to simulated thread ID
      // while making the *real* thread wait on condition variable run_cv
      carr[last_cid].run_sid = t->sid;
      rv = pthread_cond_timedwait(&carr[last_cid].run_cv, &carr[last_cid].simlock, &next_ts);

      if (t->state == READY) {
        // Thread was preempted by scheduler to ready state
        // Calculate the remaining time in the run period
        // t->event_ts should have been set to preemption time by scheduler
        timesub(&next_ts, &next_ts, &t->event_ts);

      } else if (t->state == RUNNING && carr[t->cid].run_sid == -1) {
        // Thread was preempted and selected right back to running state
        // Calculate the remaining time in the run period
        // t->event_ts should have been set to preemption time by scheduler
        timesub(&next_ts, &next_ts, &t->event_ts);

      } else {
        // Thread finished the run period

        if (rv == 0)
          errx(1, "thread[%d] was preempted when in %d state, run_sid=%d",
               t->sid, t->state, carr[t->cid].run_sid);
        if (rv != ETIMEDOUT)
          errx(1, "thread[%d] failed timedwait on run_cv, rv=%d", t->sid, rv);
        if (t->state != RUNNING)
          errx(1, "thread[%d] finished run not in running state!?!", t->sid);

        // rv == ETIMEDOUT && t->state == RUNNING

        clock_gettime(CLOCK_REALTIME, &next_ts);
        int run_time = TIMEUSEC(&t->event_ts, &next_ts);
        t->remain_usec -= run_time;
        t->event_ts = next_ts;

        struct timespec time_in_core;
        timesub(&time_in_core, &next_ts, &t->core_ts);
        if(TIMEUSEC(&affinity_ts, &time_in_core) > 0 && t->remain_usec > 0){
        	//if the time of the current thread in the current core is longer than affinity_ts
        	//that means core private cache can provide high performance.
        	int bonus_time = run_time * 0.3;
        	if(bonus_time > t->remain_usec){
        		bonus_time = t->remain_usec;
        	}
        	t->remain_usec -= bonus_time;
        	core_log(&carr[t->cid], "%8ld: [CPU_Cache Effort] thread[%d] got hitting private cache of core bonus#%d\n",
        			TIMEUSEC(&sim_ts, &next_ts),t->sid, bonus_time);


        }

        core_log(&carr[t->cid], "%8ld: thread[%d] with remain_usec=%d finished run#%d\n",
            TIMEUSEC(&sim_ts, &next_ts), t->sid, t->remain_usec, runN);

        if (t->remain_usec > 0) {
          // Thread enters block period
          t->state = BLOCKED;
          carr[t->cid].run_sid = -1;
          carr[t->cid].block_sid = t->sid;

          // Generate the duration of the next block time
          timerand_ms(&next_ts, &seed, 200, 300);

        } else {
          // Thread terminates
          t->remain_usec = 0;
          t->state = TERMINATED;
          carr[t->cid].run_sid = carr[t->cid].block_sid = -1;
        }

        // Signals core scheduler to select another thread to run
        //printf("send signal to core sched_cv");
        pthread_cond_broadcast(&carr[t->cid].sched_cv);
        //pthread_cond_signal(&sched_cv);
      }
      break;

    case READY:
      clock_gettime(CLOCK_REALTIME, &t->event_ts);
      core_log(&carr[t->cid], "%8ld: thread[%d] with remain_usec=%d is ready for run#%d\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, t->remain_usec, runN);

      // Thread waits until scheduler signals it to run

      pthread_cond_wait(&t->ready_cv, &carr[last_cid].simlock);
      break;

    case BLOCKED:
      clock_gettime(CLOCK_REALTIME, &t->event_ts);
      core_log(&carr[t->cid], "%8ld: thread[%d] enters block#%d for %.1f msec\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, runN,
          TIMEUSEC(&zero_ts, &next_ts)/1000.0);

      // Calculate the ending time of the block period
      timeadd(&next_ts, &t->event_ts, &next_ts);

      // The simulated thread "blocks" by making the *real* thread wait on
      // condition variable block_cv
      rv = pthread_cond_timedwait(&t->block_cv, &carr[last_cid].simlock, &next_ts);

      if (t->state != BLOCKED)
        errx(1, "thread[%d] finished block not in blocked state!?!", t->sid);
      if (rv == 0)
        errx(1, "thread[%d] was preempted in block state!", t->sid);
      if (rv != ETIMEDOUT)
        errx(1, "thread[%d] failed timedwait on block_cv, rv=%d", t->sid, rv);

      clock_gettime(CLOCK_REALTIME, &t->event_ts);
      core_log(&carr[t->cid], "%8ld: thread[%d] finished block#%d\n",
          TIMEUSEC(&sim_ts, &t->event_ts), t->sid, runN);

      // Thread adds itself to unblock queue, so scheduler can move the
      // thread formally from blocked to ready state

      add_to_Q_back(&carr[t->cid].unblockQ, t);

      if (unblock_signal) {
        if(&carr[t->cid].sched_cv != NULL)
        	pthread_cond_broadcast(&carr[t->cid].sched_cv);
        //pthread_cond_signal(&sched_cv);
      }

      // Wait for scheduler to formally unblock thread
      pthread_cond_wait(&t->block_cv, &carr[last_cid].simlock);

      // Generate the duration of the next run
      timerand_ms(&next_ts, &seed, 300, 800);
      break;

    default:
      errx(1, "Invalid thread[%d] state: %d!!", t->sid, t->state);
    }
    pthread_mutex_unlock(&carr[last_cid].simlock);  //core might be changed, so using last_cid
  };

  clock_gettime(CLOCK_REALTIME, &next_ts);
  t->term_usec = TIMEUSEC(&sim_ts, &next_ts);
  core_log(NULL, "%8ld: thread[%d] terminated\n", t->term_usec, t->sid);
  pthread_mutex_lock(&carr[t->cid].simlock);
  // Inform the scheduling that thread has terminated
  pthread_cond_signal(&carr[t->cid].sched_cv); //notify core
  //pthread_cond_signal(&sched_cv); //notify global sim
  //release per core lock
  pthread_mutex_unlock(&carr[t->cid].simlock);
  
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
  pthread_cond_init(&t->core_cv, NULL);

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
    pthread_cond_destroy(&t->core_cv);
    free(t->stack);
  }
}

