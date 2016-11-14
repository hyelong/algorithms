compile and run in Linux with reasonable version gcc

Clean:
make clean
Build:
make

USAGE: 

./prj2 <sched_func>[+] <num_thrds> <balance_func> <num_cores> [<threads_data_filename> <min_time> <max_tim>]
    <sched_func>: name of the scheduling function for a single core
    <num_thrds>: number of user threads to simulate
    <balance_func>: name of the load balance function
    <num_cores>: number of processor cores to simulate
    <threads_binding_filename>:  Predefined core binding information for each thread    
    <min_time>: min. run time per user thread in ms (default: 1000)
    <max_time>: max. run time per user thread in ms (default: 1500)
NOTE: If <sched_func> is followed immediately by '+' (without quotes),
      unblocking user threads will signal scheduler to wake up.

      
Suported scheduling function (for each single core)
 static_priority
 most_remaining_time
 round_robin_queue
 round_robin_static
 
Support load balance function
 noop
 more_frequent_work_stealing
 less_frequent_work_stealing
 
Format of thread binding data
<thread sid>  <core id>
<thread sid>  <core id>
<thread sid>  <core id>
<thread sid>  <core id>
.....




 
  
