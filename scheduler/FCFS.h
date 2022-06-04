#ifndef __FCFS_H__
#define __FCFS_H__


#include "./Process.h"


pthread_mutex_t mutex; // declare mutex to run 1 process at a time.

void *FCFS_Run(void *);

void FCFS(pthread_t *Test, process_param *Process, int N) { // FCFS main function
	puts("FCFS Scheduling Test.\n");
	
	printf("main thread [%ld]\n", gettid()); // main thread's id

        pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < N; i ++) {
		pthread_create(&Test[i], NULL, FCFS_Run, &Process[i]); // create thread
	}
	for(int i = 0;i < N; i ++) {
		pthread_join(Test[i], NULL); // wait until threads end their own work
	}
	pthread_mutex_destroy(&mutex); // destroy mutex
	printf("main dies [%ld]\n", gettid()); // main thread die
}

void *FCFS_Run(void *data) {
	struct process_param *param = (struct process_param*) data; // convert to param
	pthread_mutex_lock(&mutex); // mutex lock to run
	printf("thread started [%ld]\n", gettid());
        printf("burstTime: %lld\n", param->burstTime);
	__u64 burstTime = param->burstTime *sec; // convert to second
	clock_t t = clock(); // save time;
	while(clock() - t < burstTime) { // loop during burstTime
	}
	pthread_mutex_unlock(&mutex); // mutex unlock
	pthread_exit(0);
}

#endif

