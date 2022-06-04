#ifndef __RR_H__ 
#define __RR_H__ 

//RR 기법
#include "./Process.h"
#include<stdbool.h>  

int quantum = 1;   //RR quantum

pthread_mutex_t mutex; // declare mutex to run 1 process at a time.

void *RR_Run(void *);
// void *merge(process_param *, int, int, int);
// void *mergeSort_bursttime(process_param *, int, int);

void RR(pthread_t *Test, process_param *Process, int N) { // RR main function
	puts("RR Scheduling Test.\n");
	
	printf("main thread [%ld]\n", gettid()); // main thread's id
	
	mergeSort_bursttime(Process, 0, (N-1));
	
	int rem_bt[N]; // remaining time

	for(int j = 0; j<N; j++){
		rem_bt[j] = Process[j].burstTime;
	}
	
	//quantum calculate 
	quantum = Process[N*8/10-1].burstTime;

	int t = 0; // execution time

	while(1){
		bool done = true;

		for(int i = 0; i<N; i++){

			if(Process[i].arrivalTime >t ) {
				done = false;
				continue;
			}

			if(rem_bt[i]>0){
				printf("%s|", Process[i].pName);
				printf("rem_bt  : %d\n",rem_bt[i]);
				done = false;

				if(rem_bt[i]>quantum){
					t+=quantum;
					rem_bt[i] -=quantum;
				}else{
					t = t+rem_bt[i];
					rem_bt[i] = 0;
				}
				pthread_create(&Test[i], NULL, RR_Run, (&Process[i])); // create thread
				pthread_join(Test[i], NULL);
			}
		}

	if(done == true) break;

	}
	pthread_mutex_destroy(&mutex); // destroy mutex
	printf("main dies [%ld]\n", gettid()); // main thread die
}

void *RR_Run(void *data) {
	// struct process_param *param = (struct process_param*) data; // convert to param
	pthread_mutex_lock(&mutex); // mutex lock to run

	printf("thread started [%ld]\n", gettid());
	
	__u64 burstTime = quantum *sec; // convert to second
	clock_t t = clock(); // save time;
	while(clock() - t < burstTime) { // loop during burstTime
	}
	pthread_mutex_unlock(&mutex); // mutex unlock 
	pthread_exit(0);
}

void merge(process_param *arr, int left, int mid, int right) {
	int idx1=left; 
	int idx2=mid+1; 
	int idx; 
	process_param *retArr = (process_param *)malloc(sizeof(process_param)*(right+1));
	idx = left; 
	while(idx1<=mid && idx2<=right) {
		if (arr[idx1].burstTime <= arr[idx2].burstTime) {
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

void mergeSort_bursttime(process_param *arr, int left, int right) {
	int mid; 
	if (left < right) {
		mid = (left+right)/2; 

		mergeSort_bursttime(arr, left, mid);
		mergeSort_bursttime(arr, mid+1, right);
		
		merge(arr, left, mid, right);
	}
}

#endif
