#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <sys/syscall.h>
#include <pthread.h>

#define gettid() syscall(__NR_gettid)


#ifdef __x86_64__
#define __NR_sched_setattr 314
#define __NR_sched_getattr 315
#endif

#ifdef __i386__
#define __NR_sched_setattr 351
#define __NR_sched_getattr 352
#endif

#ifdef __arm__
#define __NR_sched_setattr 380
#define __NR_sched_getattr 381
#endif

#define N 3

struct test_param {
	__u64 arrivalTime;
	__u64 burstTime;
	int priority;
};

pthread_mutex_t mutex;

void *test2(void *);

int main(void) {
	pthread_t test[N];
	struct test_param param[N];

	printf("main thread [%ld]\n", gettid());

	//pthread test
	pthread_mutex_init(&mutex, NULL);

	param[0].arrivalTime = 0;
	param[0].burstTime = 4*1000*1000;
	param[0].priority = 3;

	param[1].arrivalTime = 1*1000*1000;
	param[1].burstTime = 2*1000*1000;
	param[1].priority = 2;

	param[2].arrivalTime = 5*1000*1000;
	param[2].burstTime = 3*1000*1000;
	param[2].priority = 4;
	
	for(int i = 0; i < N; i ++) {
		pthread_create(&test[i], NULL, test2, &param[i]);
	}
	sleep(7);
	for(int i = 0; i < N; i ++) {
		pthread_join(test[i], NULL);
	}

	pthread_mutex_destroy(&mutex);
	printf("main dies [%ld]\n", gettid());

	return 0;
}

void *test2(void *data) {
	struct test_param *param = (struct test_param*) data;
	//pthread_mutex_lock(&mutex);
	printf("thread started [%ld]\n", gettid());
	printf("bursttime: %lld\n", param->burstTime);
	clock_t t = clock();
	while(clock() - t < param->burstTime) {
		
	}
	//pthread_mutex_unlock(&mutex);
	pthread_exit(0);
}
