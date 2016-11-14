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

int last_run_sid = -1; //store the last run thread sid

//get the current size of readyQ
int get_list_count(thread_list_t list)
{
  int count;
  if ( list.tail == -1 ) //queue is full
	count = list.max_size;
  else if(list.head == -1) //queue is empty
	  count = 0;
  else
    count = list.tail - list.head;
  if(count < 0){
	  count = count + list.max_size;
  }
  return count;
}
    

/**
 * Select a ready thread with the lowest simulated thread ID (sid) to run.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int static_priority(core_data_t* c)
{
  int count = get_list_count(c->readyQ);
  //core_log(c, "ready thread list count:%d\n", count);
  int selected = c->readyQ.max_size; //start up with value great than max sid
  if ( count != 0 ){
  	for(int i = 0; i < count; i++){ //traversal the ready queue
        int q_i = i + c->readyQ.head;
        if(q_i >= c->readyQ.max_size)
        	q_i = q_i - c->readyQ.max_size;
        //core_log(c, "static priority qi:%d\n", q_i);
  		if ((c->readyQ.tparr[q_i]->sid < selected)
            &&(c->readyQ.tparr[q_i]->state == READY)){
			selected = c->readyQ.tparr[q_i]->sid; //find the lowest sid
			//core_log(c, "static priority select:%d\n", selected);
        	}
	  }
  }
  else
	  selected = -1; //no ready threads
  return selected;
}


/**
 * Select a ready thread with the most remain_usec to run.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int most_remaining_time(core_data_t* c)
{
  int count = get_list_count(c->readyQ);
  int max_remain_usec = 0;
  int selected = -1;

  if ( count != 0 ){
  	for(int i = 0; i < count; i++){
		//match thread with the most remaining run time
  		int q_i = i + c->readyQ.head;
		if(q_i >= c->readyQ.max_size)
			q_i = q_i - c->readyQ.max_size;
		if (c->readyQ.tparr[q_i]->remain_usec >= max_remain_usec){
			max_remain_usec = c->readyQ.tparr[q_i]->remain_usec;
			selected = c->readyQ.tparr[q_i]->sid;
		}
	}
  }
  return selected;
}


/**
 * Select the next thread in the ready queue.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int round_robin_queue(core_data_t* c) 
{
  int selected = -1;
  int count = get_list_count(c->readyQ);

  if ( count > 0 )
	/*the readyQ is maintained as FIFO
 	 *so the first thread in readyQ
	 */
	selected = c->readyQ.tparr[0]->sid;
   
  return  selected;
}


/**
 * Select a ready thread with the nearest next thread ID.
 * @return sid of the selected thread, or -1 if no thread is in ready state.
 */
int round_robin_static(core_data_t* c)
{
  int count = get_list_count(c->readyQ);
  int min_delta = c->readyQ.max_size; //minimal distance between thread and last run thread
  int delta = 0;
  int selected = -1;

  //printf("count is %d\n",count);
  if ( count > 0 ){
  	for(int i = 0; i < count; i++){
  		int q_i = i + c->readyQ.head;
		if(q_i >= c->readyQ.max_size)
			q_i = q_i - c->readyQ.max_size;
		if (c->readyQ.tparr[q_i]->sid > last_run_sid )
			delta = c->readyQ.tparr[q_i]->sid - last_run_sid;
		else
			//roll-over case, max_size is used trickly
			delta = ( c->readyQ.tparr[q_i]->sid + c->readyQ.max_size ) - last_run_sid;

		//the nearest next thread is selected
		if (delta <= min_delta){
			min_delta = delta; 
			selected = c->readyQ.tparr[q_i]->sid;
		}
        }
  }
  if ( selected != -1)
  	last_run_sid = selected;
  return  selected;
}


name_func_t MY_SCHED[NUM_SCHED] = {
  {"static_priority", static_priority},
  {"most_remaining_time", most_remaining_time},
  {"round_robin_queue", round_robin_queue},
  {"round_robin_static", round_robin_static}
};
