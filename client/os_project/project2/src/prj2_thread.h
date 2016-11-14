/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <pthread.h>


#ifndef PRJ2_THREAD_H
#define PRJ2_THREAD_H

#define DEBUG_FPRINTF 0

// stack size of a thread
#define  STACK_SIZE  (1024*1024)

/**
 * states of a thread
 */
typedef enum {
  STARTING,
  TERMINATED,
  READY,
  RUNNING,
  BLOCKED,
} thread_state_t;


/**
 * data structure of a thread
 */
typedef struct {
  int  tid;             // Host thread ID for logging purpose
  int  sid;             // Simulated thread ID (index in thread array)

  char *stack;          // thread-specific stack memory
  char *stackTop;       // stack growing downward

  struct timespec event_ts; // time of the last thread event
  long int start_usec;
  long int term_usec;
  int  remain_usec;     // total remaining runtime

  pthread_cond_t  block_cv; // cond.var. for thread to wait in block state
  pthread_cond_t  ready_cv; // cond.var. for thread to wait in ready state

  thread_state_t  state;
} thread_data_t;


int thread_execution(void *p);
void fork_thread(thread_data_t *t);
void clear_thread(thread_data_t *t);


/**
 * a circular list of thread_data_t
 */
typedef struct {
  thread_data_t **tparr;    // array of thread pointers
  int    max_size;          // maximum size of the list
  int    head;              // first occupied slot in tparr, -1 if empty
  int    tail;              // first empty slot in tparr, -1 if full
} thread_list_t;


/**
 * Initialize an empty circular thread queue *qp with max_size slots.
 */
inline static
void init_thread_Q(thread_list_t *qp, int max_size)
{
  qp->tparr = calloc(max_size, sizeof(thread_data_t*));

  qp->max_size = max_size;
  qp->head = -1;        // queue is empty
  qp->tail = 0;         // initial index to add new thread

#if DEBUG_FPRINTF
  fprintf(stderr, "%s(%#lx, %d): %d, %d\n", __func__, (size_t)qp, max_size,
          qp->head, qp->tail);
#endif
}


/**
 * Destroy the circular thread queue *qp
 */
inline static
void destroy_thread_Q(thread_list_t *qp)
{
  if (qp->tparr)
    free(qp->tparr);
  qp->tparr = NULL;
}


/**
 * Add thread *tp to the tail of circular queue in *qp.
 * @return remaining empty slots after the add, or -1 if queue was full.
 */
inline static
int add_to_Q_back(thread_list_t *qp, thread_data_t *tp)
{
  int count = 0;

#if DEBUG_FPRINTF
  fprintf(stderr, "%s(%#lx, %d): %d, %d\n", __func__, (size_t)qp, tp->sid,
          qp->head, qp->tail);
#endif

  if (qp->tail == -1)           // queue was full
    return -1;

  if (qp->head == -1)           // queue was empty
    qp->head = 0;

  qp->tparr[qp->tail] = tp;
  qp->tail++;

  if (qp->tail == qp->max_size)
    qp->tail = 0;               // wrap around tail index

  if (qp->tail == qp->head) {   // queue becomes full
    qp->tail = -1;
    return 0;
  }

  count = qp->tail - qp->head;
  return count > 0 ? count : count + qp->max_size;
}


/**
 * Remove a thread pointer from the head of circular queue in *qp.
 * @return the remove thread pointer, or NULL if queue was empty.
 */
inline static
thread_data_t* remove_from_Q_front(thread_list_t *qp)
{
  thread_data_t *rp;

#if DEBUG_FPRINTF
  fprintf(stderr, "%s(%#lx): %d, %d\n", __func__, (size_t)qp,
          qp->head, qp->tail);
#endif

  if (qp->head == -1)           // queue was empty
    return NULL;

  // Remove the thread pointer at head
  rp = qp->tparr[qp->head];
  qp->tparr[qp->head] = NULL;

  if (qp->tail == -1)           // queue was full
    qp->tail = qp->head;

  qp->head++;
  if (qp->head == qp->max_size)
    qp->head = 0;               // wrap around head index

  if (qp->head == qp->tail) {   // queue becomes empty
    qp->head = -1;
    qp->tail = 0;
  }

  return rp;
}


/**
 * Find and remove a thread pointer with given simulated thread ID from
 * the circular queue in *qp.
 * @return the removed thread pointer, or NULL if thread not found.
 */
inline static
thread_data_t* remove_from_Q(thread_list_t *qp, int sid)
{
  thread_data_t *rp = NULL;     // thread pointer to be removed
  int ridx = 0;

#if DEBUG_FPRINTF
  fprintf(stderr, "%s(%#lx, %d): %d, %d\n", __func__, (size_t)qp, sid,
          qp->head, qp->tail);
#endif

  if (qp->head == -1)           // queue was empty
    return NULL;

  while (ridx < qp->max_size) {
    if (qp->tparr[ridx] != NULL && qp->tparr[ridx]->sid == sid) {
      rp = qp->tparr[ridx];     // remove thread at index ridx
      break;
    }
    ridx++;
  }

  if (ridx == qp->max_size)     // can't find the thread
    return NULL;

  if (qp->tail == -1)           // queue was full
    qp->tail = (qp->head == 0 ? qp->max_size-1 : qp->head-1);
  else if (qp->tail == 0)
    qp->tail = qp->max_size-1;
  else
    qp->tail--;

  if (qp->tail == qp->head)     // queue becomes empty
    qp->head = -1;

  // shift rest of queue to fill the gap
  while (ridx != qp->tail) {
    int nidx = (ridx+1 == qp->max_size) ? 0 : ridx+1;
    qp->tparr[ridx] = qp->tparr[nidx];
    ridx = nidx;
  }

  qp->tparr[ridx] = NULL;       // clear the removed slot in queue
  return rp;
}

#endif  // PRJ2_THREAD_H
