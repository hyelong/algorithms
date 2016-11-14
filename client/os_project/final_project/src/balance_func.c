

#include "prj2.h"
#include "prj2_time.h"
#include "balance_func.h"



int noop(core_data_t* c) {
	//core_log(NULL, "No balance operation.\n");
	return 0;
}

int less_frequent_work_stealing(core_data_t* c){
	for (int i = 0; i < num_cores; i++) {
		if (pthread_mutex_trylock(&carr[i].simlock) == 0) {
			//core_log(NULL, "A Entering lock of core %d \n", i);
			if (get_list_count(carr[i].readyQ) == 0
					&& carr[i].run_sid < 0) {
				//a core is idling
				for (int j = 0; j < num_cores; j++) {
					if (pthread_mutex_trylock(&carr[j].simlock) == 0) {
				//		core_log(NULL, "B Entering lock of core %d \n", j);
						int total_t_i = get_list_count(carr[i].readyQ) + get_list_count(carr[i].blockedQ) + get_list_count(carr[i].unblockQ);
						int total_t_j = get_list_count(carr[j].readyQ) + get_list_count(carr[j].blockedQ) + get_list_count(carr[j].unblockQ);

						if (2 * total_t_i + 1 < total_t_j && get_list_count(carr[j].readyQ) > 0) {
							//do balance, shift a thread from core j to core i

							thread_data_t *t = remove_from_Q_front(
									&carr[j].readyQ);
							if(t->binded){
								//core_log(&carr[j], "Balancer: Do noting, because the ready thread[%d] has already been binded to this core\n", t->sid, i);
								add_to_Q_back(&carr[j].readyQ, t); //add it back

							}else{
								core_log(&carr[j], "Balancer: A ready thread[%d] is moved to core:%d \n", t->sid, i);
								add_to_Q_back(&carr[i].readyQ, t);
								t->cid = i;
								core_log(&carr[i], "Balancer: A ready thread[%d] is added from core:%d \n",t->sid, j);
								//pthread_cond_signal(&carr[i].sched_cv); //notify core i to continue
								//pthread_cond_signal(&carr[j].sched_cv); //notify core j to continue
								pthread_cond_signal(&t->ready_cv);
								pthread_mutex_unlock(&carr[j].simlock);
						//		core_log(NULL, "B release lock of core %d \n", j);
								break;
							}
						}
						pthread_mutex_unlock(&carr[j].simlock);
						//core_log(NULL, "B release lock of core %d \n", j);

					}
				}

			}
			pthread_mutex_unlock(&carr[i].simlock);
//			core_log(NULL, "A release lock of core %d \n", i);
		}
	}
                return 0;
}

int more_frequent_work_stealing(core_data_t* c) {



	for (int i = 0; i < num_cores; i++) {
		if (pthread_mutex_trylock(&carr[i].simlock) == 0) {
			//core_log(NULL, "A Entering lock of core %d \n", i);
			if (get_list_count(carr[i].readyQ) == 0
					&& carr[i].run_sid < 0) {
				//a core is idling
				for (int j = 0; j < num_cores; j++) {
					if (pthread_mutex_trylock(&carr[j].simlock) == 0) {
				//		core_log(NULL, "B Entering lock of core %d \n", j);
						if (get_list_count(carr[j].readyQ) > 1 || (get_list_count(carr[j].readyQ) > 0 && carr[j].run_sid != -1)) {
							//do balance, shift a thread from core j to core i

							thread_data_t *t = remove_from_Q_front(
									&carr[j].readyQ);
                                                if(t->binded){
								core_log(&carr[j], "Balancer: Do noting, because the ready thread[%d] has already been binded to this core\n", t->sid, i);
								add_to_Q_back(&carr[j].readyQ, t); //add it back

							}else{
							core_log(&carr[j], "Balancer: A ready thread[%d] is moved to core:%d \n", t->sid, i);
							add_to_Q_back(&carr[i].readyQ, t);
							t->cid = i;
							core_log(&carr[i], "Balancer: A ready thread[%d] is added from core:%d \n",t->sid, j);
							//pthread_cond_signal(&carr[i].sched_cv); //notify core i to continue
							//pthread_cond_signal(&carr[j].sched_cv); //notify core j to continue
							pthread_cond_signal(&t->ready_cv);
							pthread_mutex_unlock(&carr[j].simlock);
					//		core_log(NULL, "B release lock of core %d \n", j);
							break;
                                                        }
						}
						pthread_mutex_unlock(&carr[j].simlock);
						//core_log(NULL, "B release lock of core %d \n", j);

					}
				}

			}
			pthread_mutex_unlock(&carr[i].simlock);
//			core_log(NULL, "A release lock of core %d \n", i);
		}
	}
                        return 0;
}

bal_name_func_t MY_BALANCE[NUM_BALANCE] = { { "noop", noop }, { "more_frequent_work_stealing",
		more_frequent_work_stealing }, { "less_frequent_work_stealing", less_frequent_work_stealing } };
