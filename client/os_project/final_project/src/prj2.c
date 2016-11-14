/**
 * Template code for SCU COEN283 Winter 2015 PRJ2
 * @author Yi-Hua Edward Yang <edward.yang@xilinx.com>, 5/1/2014
 **/

#define _GNU_SOURCE

#include <string.h>

#include "prj2.h"
// prj2.h includes prj2_thread.h
// prj2.h includes multicore_sim.h

#include "prj2_time.h"
#include "prj2_scheduling.h"


#include "dispatch_func.h"
#include "balance_func.h"

/*
 * Variables below can be accessed from everywhere.
 * (They have extern declarations in prj2.h)
 */
pthread_mutex_t simlock;    // critical region of simulation
pthread_mutex_t loglock;    // prevent log interweaving

pthread_cond_t  run_cv;     // cond.var. that simulates thread running
pthread_cond_t  sched_cv;   // cond.var. that scheduler or dispatcher is running

struct timespec sim_ts;     // time when simulation begins

int run_sid = -1;           // index of thread currently running
int block_sid = -1;         // index of thread entering blocked state
int unblock_signal = 0;     // signal scheduler when thread unblocks?
int affinity_enabled = 0;   // flag for cpu affinity
int is_terminated = 0;  	// global flag for terminating all the simulation threads.

const struct timespec zero_ts = { 0, 0 };
const struct timespec tick_ts = { 0, 200000000 };
const struct timespec affinity_ts = {0, 600000000};

thread_list_t global_waitingQ;  //list of threads waiting for dispatching to cores

thread_data_t *tarr = NULL; // array of thread data structures
core_data_t *carr = NULL; //array of cores
int (*sched_func)() = NULL; // scheduling function picked at run time
int (*balance_func)(core_data_t*) = NULL; // balance function picked at run time

int num_cores = 0;        // number of processor cores to simulate
int num_thrds = 0;        // number of user threads to simulate

char* threads_data_filename = NULL;
/*
 * Variables below can also be accessed from prj2_scheduling.c only.
 */



/*
 * Variables below can also be accessed from prj2_thread.c only.
 */

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
  "\nUSAGE: %s <sched_func>[+] <num_thrds> <balance_func> <num_cores> [<threads_data_filename> <min_time> <max_tim>]\n"
  "    <sched_func>: name of the scheduling function for a single core\n"
  "    <num_thrds>: number of user threads to simulate\n"
  "    <balance_func>: name of the load balance function\n"
  "    <num_cores>: number of processor cores to simulate\n"
  "    <threads_binding_filename>:  Predefined core binding information for each thread\n"
  "    <min_time>: min. run time per user thread in ms (default: 1000)\n"
  "    <max_time>: max. run time per user thread in ms (default: 1500)\n"
  "NOTE: If <sched_func> is followed immediately by '+' (without quotes),\n"
  "      unblocking user threads will signal scheduler to wake up.\n\n";



int main(int argc, char* argv[])
{
   int tmp = 0;
  if (argc < 5) {
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
  
  tmp = strlen(argv[3]);
  if (argv[3][tmp-1] == '+') {
    affinity_enabled = 1;
    argv[3][tmp-1] = '\0';
  }

  for (int i=0 ; i < NUM_BALANCE ; i++) {
    if (strcmp(argv[3], MY_BALANCE[i].name) == 0) {
      balance_func = MY_BALANCE[i].func;
      break;
    }
  }
  if (balance_func == NULL) {
    errx(1, "Balance function %s not found!", argv[1]);
  }

  num_cores = strtol(argv[4], NULL, 0);
  threads_data_filename = NULL;
  if(argc > 5){
	  threads_data_filename = argv[5];
  }

  if (argc > 6)
    min_time = strtol(argv[5], NULL, 0);
  if (argc > 7)
    max_time = strtol(argv[6], NULL, 0);

  // Get simulation start time for logging reference
  clock_gettime(CLOCK_REALTIME, &sim_ts);

    

  pthread_mutex_init(&simlock, NULL);
  pthread_cond_init(&sched_cv, NULL);
  pthread_cond_init(&run_cv, NULL);

  init_thread_Q(&global_waitingQ, num_thrds);
  pthread_mutex_lock(&simlock);

  // Create and fork number of cores as requested
  carr = calloc(num_cores, sizeof(core_data_t));
  for(int i = 0; i < num_cores; i++){
    carr[i].cid = i;
    fork_core(&carr[i]);
    core_log(&carr[i],"Core tid=%d created with cid=%d\n", carr[i].tid, carr[i].cid);
  }
  fork_dispatcher();
  // Create and fork number of threads as requested
  tarr = calloc(num_thrds, sizeof(thread_data_t));
  for (int i=0 ; i < num_thrds ; i++) {
    tarr[i].sid = i;
    tarr[i].cid = -1; //processor core not assigned

    // Thread is put to blocked state right after start
    tarr[i].state = BLOCKED;
    add_to_Q_back(&global_waitingQ, &tarr[i]);
    fork_thread(&tarr[i]);
    //pthread_cond_signal(&sched_cv); //notify dispatcher
    core_log(NULL, "Thread tid=%d created with sid=%d\n", tarr[i].tid, tarr[i].sid);
  }
  


  pthread_mutex_unlock(&simlock);

  sched_yield();

  for (int i=0 ; i < num_thrds ; i++) {
    int rv;
    int tid = wait(&rv);        // wait for an (only) child to exit
    core_log(NULL, "Thread tid=%d exited with status %d\n", tid, WEXITSTATUS(rv));
  }

  core_log(NULL, "All user created threads terminated.\n");
  is_terminated = 1;
  //waiting for all the simulator threads : cores and dispatcher.
  for (int i=0 ; i < num_cores + 1  ; i++) {
	int rv;
	int tid = wait(&rv);        // wait for an (only) child to exit
	core_log(NULL, "Simulator system thread tid=%d exited with status %d\n", tid, WEXITSTATUS(rv));
  }

  for (int i=0 ; i < num_thrds ; i++) {
    clear_thread(&tarr[i]);
  }

  free(tarr);
  free(carr);
  destroy_thread_Q(&global_waitingQ);
  pthread_mutex_destroy(&simlock);
  pthread_cond_destroy(&sched_cv);
  pthread_cond_destroy(&run_cv);
  return 0;
}

void core_log(core_data_t* c, const char *templ, ...)
{
    pthread_mutex_lock(&loglock);
    if(c!=NULL){
      printf("[core=%2d, run=%2d, block=%2d]",  \
           c->cid, c->run_sid, c->block_sid);
    }else{
      printf("[Simulator global message ]");
    }
    va_list args;
    va_start(args, templ);
    vprintf(templ, args);
    va_end(args);
    pthread_mutex_unlock(&loglock);
}
