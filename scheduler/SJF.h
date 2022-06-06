#ifndef __SJF_H__
#define __SJF_H__


#include "./Process.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


typedef struct new_process_param {	// a new process parameter struct
	char pName[MAX];
	long pid;
	__u64 arrivalTime;
	__u64 burstTime;
	int priority;

	// scheduled process information
	int waitingTime;
	int returnTime;
	int turnaroundTime;
	int responseTime;
	bool completed;
} new_process_param;

pthread_mutex_t mutex;	//declare mutex to run 1 process at a time
int currTime;	// a time value for caculating scheduled process information

void *SJF_Run(void *);
void newParam_init(process_param *, new_process_param *, int);
// void compare_by_arrivalTime(const void *, const void *);
void quickSort_by_arrivalTime(process_param *, int);


// SJF main function
void SJF(pthread_t *Test, process_param *Process, int N) {
	int i, j;	// variables for loop
	int min;	// the index number of the process having the shortest burst time

	new_process_param newProcess[N];

	pthread_mutex_init(&mutex, NULL);

	// sort processes by arrival time
	quickSort_by_arrivalTime(Process, N);
	// initialize new process parameter
	newParam_init(Process, newProcess, N);

	puts("\nSJF Scheduling Test.\n");

	printf("main thread [%ld]\n", gettid());

	// find the process having the shortest burst time and execute it
	for(i = 0; i < N; i++) {
		// if currTime == 0, then execute the process arrived at first
		if(currTime == 0){
			pthread_create(&Test[0], NULL, SJF_Run, &newProcess[0]);
			pthread_join(Test[0], NULL);
			continue;
		} else {
		// find the process having the shortest burst time
		for(j = 0; j < N; j++) {
			if(newProcess[j].completed == true)
				continue;
			else {
				min = j;
				break;
			}
		}

		for(j = 0; j < N; j++) {
			if ((newProcess[j].completed == false) && (newProcess[j].arrivalTime <= currTime) && (newProcess[j].burstTime < newProcess[min].burstTime)) {
				min = j;
			}
		}
		
		// execute the process having the shortest burst time
		pthread_create(&Test[min], NULL, SJF_Run, &newProcess[min]);	// create thread
		pthread_join(Test[min], NULL);
		}
	}

	pthread_mutex_destroy(&mutex);	// destroy mutex
	printf("main dies [%ld]\n", gettid());	// main thread die
}

void *SJF_Run(void *data) {
	struct new_process_param *param = (struct new_process_param*)data;	

	pthread_mutex_lock(&mutex);	// mutex lock to run
	printf("thread started [%ld]\n", gettid());
	printf("burstTime: %lld\n", param->burstTime);

	__u64 burstTime = param->burstTime *sec;	// convert to second
	clock_t t = clock();	// save time
	while(clock() - t < burstTime) {	// loop during burstTime
	}
	
	// calculate scheduled process information
	if(currTime == 0){
		// the process executed at first
		param->completed = true;
		currTime = param->burstTime;
		param->returnTime = param->burstTime;
		param->waitingTime = 0;
		param->turnaroundTime = param->burstTime - param->arrivalTime;
	} else {
		param->waitingTime = currTime - param->arrivalTime;
		param->completed = true;
		currTime += param->burstTime;
		param->returnTime = currTime;
		param->turnaroundTime = param->returnTime - param->arrivalTime;
	}

	pthread_mutex_unlock(&mutex);	// mutex unlock
	pthread_exit(0);
}
/*
// compare function used for quickSort_by_arrivalTime
int compare_by_arrivalTime(const void *a, const void *b) {
	process_param *pA = (process_param *)a;
	process_param *pB = (process_param *)b;

	if (pA->arrivalTime < pB->arrivalTime)
		return -1;
	else if (pA->arrivalTime > pB->arrivalTime)
		return 1;
	else {
		// if arrival time is equal, sort by burst time
		if (pA->burstTime < pB->burstTime)
			return -1;
		else
			return 1;
	}
}
*/

// a function executing quicksort by arrival time
void quickSort_by_arrivalTime(process_param *p, int len) {
	qsort(p, len, sizeof(process_param), compare_by_arrivalTime);
}

// a function initiating new process parameter
void newParam_init(process_param *op, new_process_param *np, int N) {
	for(int i = 0; i < N; i++) {
		strcpy(np[i].pName, op[i].pName);
		np[i].pid = op[i].pid;
		np[i].arrivalTime = op[i].arrivalTime;
		np[i].burstTime = op[i].burstTime;
		np[i].priority = op[i].priority;

		np[i].waitingTime = 0;
		np[i].returnTime = 0;
		np[i].turnaroundTime = 0;
		np[i].responseTime = 0;
		np[i].completed = false;
	}
}

#endif
