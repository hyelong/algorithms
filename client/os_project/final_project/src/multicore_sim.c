


#include "prj2.h"
#include "prj2_time.h"

#include "multicore_sim.h"



int core_execution(void *p)
{
  struct timespec event_ts;

  core_data_t  *c = (core_data_t *)p;
  core_log(c, "core simulation start\n");
  //entering critical section of this core
  pthread_mutex_lock(&c->simlock);
  c->run_sid = -1;         // no thread is initially running
  c->block_sid = -1;       // no thread is initially entering block state

  thread_data_t *tsel = NULL;
  do {
    if (c->block_sid != -1) {
      // Scheduler was waken up by the running thread blocking
      // Handle thread entering blocked state from running state
      if (c->run_sid != -1)
        errx(1, "thread[%d] was blocked while thread[%d] is still running",
             c->block_sid, c->run_sid);

      add_to_Q_back(&c->blockedQ, &tarr[c->block_sid]);
      c->block_sid = -1;

    } else if (c->run_sid != -1) {
      // Scheduler was waken up by the tick_ts timeout
      // Preempt running (and non-blocking) thread to ready state
      thread_data_t *t = &tarr[c->run_sid];

      if (t->state != RUNNING)
        errx(1, "thread[%d] to be preempted is in %d state",
             c->run_sid, t->state);

      clock_gettime(CLOCK_REALTIME, &event_ts);
      t->remain_usec -= TIMEUSEC(&t->event_ts, &event_ts);
      t->event_ts = event_ts;

      core_log(c, "%8ld: scheduler preempts running thread[%d] with remain_usec=%d\n",
          TIMEUSEC(&sim_ts, &event_ts), c->run_sid, t->remain_usec);

      // Change the preempted thread into ready state
      t->state = READY;
      add_to_Q_back(&c->readyQ, t);
      c->run_sid = -1;
      // Signal the thread to stop running
      pthread_cond_signal(&c->run_cv);
    }

    while (c->unblockQ.head >= 0) {

      // Handle threads unblocking from blocked state into ready state
      thread_data_t *t = remove_from_Q_front(&c->unblockQ);

      clock_gettime(CLOCK_REALTIME, &event_ts);
      t->event_ts = event_ts;

      core_log(c, "%8ld: scheduler changes thread[%d] with remain_usec=%d to ready\n",
          TIMEUSEC(&sim_ts, &event_ts), t->sid, t->remain_usec);

      // Change the unblocking thread into ready state
      t->state = READY;
      remove_from_Q(&c->blockedQ, t->sid);
      add_to_Q_back(&c->readyQ, t);
      
      // Signal the thread to become formally unblocked
      pthread_cond_signal(&t->block_cv);
    }

    if (c->unblockQ.head >= 0)     // unblockQ is not empty
      errx(1, "unblockQ has pending threads from %d to %d!?!",
           c->unblockQ.head, c->unblockQ.tail);
    if (c->run_sid != -1)
      errx(1, "scheduler is running with running thread[%d]!?!", c->run_sid);
    if (c->block_sid != -1)
      errx(1, "thread[%d] was blocking but not handled!?!", c->block_sid);

    if (c->readyQ.head == -1 && c->blockedQ.head == -1) {
      // no thread is running, neither in ready or blocked list
      clock_gettime(CLOCK_REALTIME, &event_ts);
      core_log(c, "%8ld: core[%d] is idling\n",
          TIMEUSEC(&sim_ts, &event_ts), c->cid);
      //break; 
//      //signal balancer
//      pthread_mutex_lock(&simlock);
//      pthread_cond_signal(&sched_cv);
//      pthread_mutex_unlock(&simlock);
      //waiting balance
//      timeadd(&event_ts, &event_ts, &tick_ts);
//      pthread_cond_timedwait(&c->sched_cv, &c->simlock, &event_ts);
    }

    if (tsel != NULL && tsel->state == RUNNING) {
      // Scheduler was waken up (by unblocking or terminating threads) before
      // last selected thread could startrunning -- do not select again
      /*** Do nothing ***/

    } else {
      // Either scheduler did not select a thread last time, or the selected
      // thread is not running any more (blocked, preempted or finished)

      // Run the scheduling algorithm to select a new thread
      int sel_sid = sched_func(c);

      clock_gettime(CLOCK_REALTIME, &event_ts);

      if (sel_sid < 0) {
        tsel = NULL;
        core_log(c, "%8ld: scheduler cannot find any thread to run: %d %d\n",
            TIMEUSEC(&sim_ts, &event_ts),c->readyQ.head, c->readyQ.tail);

      } else {
        tsel = &tarr[sel_sid];

        if (tsel->state != READY)
          errx(1, "scheduler selects thread[%d] not in ready state", sel_sid);

        core_log(c,"%8ld: scheduler selects thread[%d] with remain_usec=%d to run\n",
            TIMEUSEC(&sim_ts, &event_ts), sel_sid, tsel->remain_usec);

        // Change the selected thread to running state
        tsel->state = RUNNING;
        remove_from_Q(&c->readyQ, tsel->sid);
        // Signal the selected thread to run
        pthread_cond_broadcast(&tsel->ready_cv);
      }
    }

    // Scheduler wait for either a signal or tick_ts until next preemption
    //core_log(c, "core waiting----------------------------\n");
    timeadd(&event_ts, &event_ts, &tick_ts);
    pthread_cond_timedwait(&c->sched_cv, &c->simlock, &event_ts);
    if(is_terminated)
    		break;
  } while (1);

  pthread_mutex_unlock(&c->simlock);

  return 0;
}

void fork_core(core_data_t *c)
{
  // allocate stack space for the thread
  if ((c->stack = malloc(CORE_STACK_SIZE)) == NULL) {
    c->tid = 0;
    warn("malloc() failed for thread[%d]", c->cid);
    return;
  }

  // stack grows downward
  c->stackTop = c->stack + CORE_STACK_SIZE;

  pthread_mutex_init(&c->simlock, NULL);
  // condition variable used to core simulation
  pthread_cond_init(&c->run_cv, NULL);
  pthread_cond_init(&c->sched_cv, NULL);

  init_thread_Q(&c->readyQ, global_waitingQ.max_size);
  init_thread_Q(&c->blockedQ, global_waitingQ.max_size);
  init_thread_Q(&c->unblockQ, global_waitingQ.max_size);

  c->tid = clone(core_execution, c->stackTop, SIGCHLD|CLONE_VM, c);
  if (c->tid == -1) {
    warn("clone() failed for core thread[%d]", c->cid);
  }
}
