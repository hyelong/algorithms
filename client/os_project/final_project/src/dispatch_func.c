

#include "dispatch_func.h"
#include <stdio.h>





int* read_core_bind_file(){
	FILE *data_file;
	int* bind_array = malloc(num_thrds * sizeof(int));
	for(int i = 0; i < num_thrds; i ++){
		bind_array[i] = -1;
	}

	if(threads_data_filename == NULL)
		return bind_array;

	data_file = fopen(threads_data_filename, "r");


	int sid, cid;
	while(!feof (data_file)){
		fscanf(data_file, "%d %d ", &sid, &cid);
		//core_log(NULL, "read data from file sid %d\n", sid);

		//core_log(NULL, "read data from file cid %d\n", cid);
		bind_array[sid] = cid;
	}
	return bind_array;
}

void fork_dispatcher(){
  
  char *stack_for_dispatcher;


  // allocate stack space for the thread
  if ((stack_for_dispatcher = malloc(DEFALT_STACK_SIZE)) == NULL) {
    warn("malloc() failed for dispatcher");
    return;
  }
  
  int dispatcher_tid = clone(dispatcher_execution, 
    stack_for_dispatcher + DEFALT_STACK_SIZE, SIGCHLD|CLONE_VM, NULL);
  if (dispatcher_tid == -1) {
    warn("clone() failed for dispatcher");
  }
}


int dispatcher_execution(){
  //core_log(NULL, "dispather entering\n");
  struct timespec event_ts;
  const struct timespec d_tick_ts = { 0, 20000000 };
  pthread_mutex_lock(&simlock);
  int core_pointer = 0;
  int *thread_bind = read_core_bind_file();
  while(1){
	if(is_terminated)
		break;
    while(global_waitingQ.head != -1){ //queue is not empty
      //pthread_cond_wait(&sched_cv, &simlock);
    	thread_data_t *t = remove_from_Q_front(&global_waitingQ);
    	if(thread_bind[t->sid] == -1){
			t->cid = core_pointer % num_cores;
			core_pointer ++;
			t->binded = 0;
			//core_log(NULL, "A %d \n", t->cid);
    	}else{
    		t->cid = thread_bind[t->sid];
    		t->binded = 1;
    		//core_log(NULL, "B %d \n", t->cid);
    	}
    	clock_gettime(CLOCK_REALTIME, &t->core_ts);

		pthread_mutex_lock(&carr[t->cid].simlock);
		core_log(NULL, "Thread:%d is assigned to core:%d\n", t->sid, t->cid);
		pthread_cond_signal(&t->core_cv);
		pthread_mutex_unlock(&carr[t->cid].simlock);
    }
    //core_log(NULL, "Call balance function ----------------------------\n");
    balance_func(carr);

    clock_gettime(CLOCK_REALTIME, &event_ts);
	timeadd(&event_ts, &event_ts, &d_tick_ts);
	//wait a core need balancing
	pthread_cond_timedwait(&sched_cv, &simlock, &event_ts);

  }
  pthread_mutex_unlock(&simlock);
  return 0;
}
