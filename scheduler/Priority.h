#ifndef __PRIORITY_H__
#define __PRIORITY_H__


#include "./Process.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

pthread_mutex_t mutex; // declare mutex to run 1 process at a time.

int compare_by_priority(const void *a, const void *b)
{
	process_param *p1 = (process_param *)a;
    process_param *p2 = (process_param *)b;

    if (p1->priority < p2->priority)
        return -1;

    else if (p1->priority > p2->priority)
        return 1;
	else
		return 0;
}
void quick_sort_by_priority(process_param *arr, int len)
{
	 qsort(arr, len, sizeof(process_param), compare_by_priority);
}

void *PRIORITY_Run(void *);

void PRIORITY(pthread_t *Test, process_param *Process, int N) {

    __u64 time = 0;
    int completed[100];
	int i;
    puts("PRIORITY Scheduling Test.\n");
    printf("main thread [%ld]\n", gettid()); // main thread's id

    quick_sort_by_priority(Process,N);
		
	/* 배열 잘 되었나 확인하는 코드
	for (i=0; i<N; i++){
		printf("%lld\n",Process[i].burstTime);
	}*/


    while (1)
    {

    	for (i = 0; i < N; i++) {
    		/* 실행X, 도착한 프로세스인 경우 */
    		if ((completed[i] == 0) && (Process[i].arrivalTime <= time))
    		{
						pthread_create(&Test[i], NULL, PRIORITY_Run, (&Process[i]));
						pthread_join(Test[i], NULL);
						completed[i] = 1;
						time += Process[i].burstTime;
						break;
    		}
    	}
			if (i == N)
				break;
    }


	pthread_mutex_destroy(&mutex); // destroy mutex
	printf("main dies [%ld]\n", gettid()); // main thread die
}

void *PRIORITY_Run(void *data) {
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
