#ifndef __RR_H__ 
#define __RR_H__ 

//RR 기법
#include "./Process.h"
#include<stdbool.h>  
#include <string.h>

typedef struct process_param_RR { // parameter struct
	char pName[MAX];
	long pid;
	__u64 arrivalTime;
	__u64 burstTime;
	int priority;
    __u64 remainTime;
} process_param_RR;

int quantum = 1;   //RR quantum    <- It's temporary value now. I should fix this in main.c, so Please wait.

pthread_mutex_t mutex; // declare mutex to run 1 process at a time.

void *RR_Run(void *);
void RR_init(process_param *, process_param_RR *, int);

// void *merge(process_param *, int, int, int);
void mergeSort_arrivalTime(process_param *, int, int);

void RR(pthread_t *Test, process_param *Process, int N) { // RR main function
        pthread_mutex_init(&mutex, NULL);
	puts("RR Scheduling Test.\n");
	
	printf("main thread [%ld]\n", gettid()); // main thread's id
	
	mergeSort_arrivalTime(Process, 0, (N-1));
        struct process_param_RR Process_RR[N];
        RR_init(Process, Process_RR, N);
        for(int i = 0; i < N; i ++) {
            printf("%s %ld %lld %lld %d %lld\n", Process_RR[i].pName, Process_RR[i].pid, Process_RR[i].arrivalTime, Process_RR[i].burstTime, Process_RR[i].priority, Process_RR[i].remainTime);
        }
        clock_t t = clock(); // save time;
        for(int i = 0; i < N; i ++) {
            __u64 arrivalTime = Process_RR[i].arrivalTime*sec;
            while(1) {
                if (clock() - t >= arrivalTime) {
                    pthread_create(&Test[i], NULL, RR_Run, &Process_RR[i]); // create threa
                    break;
                }
            }
        }
        for(int i = 0;i < N; i ++) {
		pthread_join(Test[i], NULL); // wait until threads end their own work
	}
	
	pthread_mutex_destroy(&mutex); // destroy mutex
	printf("main dies [%ld]\n", gettid()); // main thread die
}

void *RR_Run(void *data) {
	struct process_param_RR *param = (struct process_param_RR*) data; // convert to param
	while(1) {
		pthread_mutex_lock(&mutex);
		printf("thread started [%ld]\n", gettid());
		__u64 runTime = quantum*sec;
		if (param->remainTime == param->burstTime) {
			if (quantum > param->remainTime) {
				clock_t t = clock();
			    while(clock() - t < param->remainTime*sec) {
			    }
			    param->remainTime =0;
			}
			else {
				clock_t t = clock();
				while(clock() - t < runTime) {
				}
				param->remainTime -= quantum;
			}
		}
		else if (quantum >= param->remainTime) {
			clock_t t = clock();
			while(clock() - t < param->remainTime*sec) {
			}
			param->remainTime =0;
		}
		else{
			clock_t t = clock();
			while(clock() - t < runTime) {
			}
			param->remainTime -= quantum;
		}
		printf("%ld %lld\n", gettid(), param->remainTime);
		pthread_mutex_unlock(&mutex);
		if(param->remainTime <= 0) {
			break;
		}
	}
	pthread_exit(0);
}

void merge(process_param *arr, int left, int mid, int right) {
	int idx1=left; 
	int idx2=mid+1; 
	int idx; 
	process_param *retArr = (process_param *)malloc(sizeof(process_param)*(right+1));
	idx = left; 
	while(idx1<=mid && idx2<=right) {
		if (arr[idx1].arrivalTime <= arr[idx2].arrivalTime) {
			retArr[idx] = arr[idx1];
			idx1++; 
		}
		else {
			retArr[idx] = arr[idx2];
			idx2++; 
		}
		idx++; 
	}
	
	if (right < idx2) {
		for(int i = idx1; i <= mid; i ++) {
			retArr[idx] = arr[i];
			idx++;
		}
	}
	else { 
		for(int i = idx2; i <= right; i ++) {
			retArr[idx] = arr[i];
			idx++;
		}
	}
	for(int i = left; i <= right; i ++) {
		arr[i] = retArr[i]; 
	}
	
	free(retArr); 
}

void mergeSort_arrivalTime(process_param *arr, int left, int right) {
	int mid; 
	if (left < right) {
		mid = (left+right)/2; 

		mergeSort_arrivalTime(arr, left, mid);
		mergeSort_arrivalTime(arr, mid+1, right);
		
		merge(arr, left, mid, right);
	}
}

void RR_init(process_param *P1, process_param_RR *P2, int N) {
    for(int i = 0; i < N; i ++) {
        strcpy(P2[i].pName, P1[i].pName);
        P2[i].pid = P1[i].pid;
        P2[i].arrivalTime = P1[i].arrivalTime;
        P2[i].burstTime = P1[i].burstTime;
        P2[i].priority = P1[i].priority;
        P2[i].remainTime = P2[i].burstTime;
    }
}
#endif
