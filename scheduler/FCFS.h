#ifndef __FCFS_H__
#define __FCFS_H__


#include "./Process.h"


pthread_mutex_t mutex; // declare mutex to run 1 process at a time.

void *FCFS_Run(void *);
int compare_by_arrivalTime(const void *, const void *);
void qsort_arrivalTime(process_param *, int);

void FCFS(pthread_t *Test, process_param *Process, int N) { // FCFS main function
	puts("FCFS Scheduling Test.\n");
	
	qsort_arrivalTime(Process, N);
	printf("main thread [%ld]\n", gettid()); // main thread's id

    pthread_mutex_init(&mutex, NULL);

	for(int i = 0; i < N; i ++) {
		pthread_create(&Test[i], NULL, FCFS_Run, &Process[i]); // create thread
	    pthread_join(Test[i], NULL); // wait until thread end its own work
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

int compare_by_arrivalTime(const void *a, const void *b) {
	process_param *p1 = (process_param *)a;
	process_param *p2 = (process_param *)b;
	if (p1->arrivalTime < p2->arrivalTime) {
		return -1;
	}
	else if (p1->arrivalTime > p2->arrivalTime) {
		return 1;
	}
	return 0;
}

void qsort_arrivalTime(process_param *arr, int N) {
	qsort(arr, N, sizeof(process_param), compare_by_arrivalTime);
}


#endif

