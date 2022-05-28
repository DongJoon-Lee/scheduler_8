#ifndef __PROCESS_H__
#define __PROCESS_H__

#define MAX 20

typedef struct process_param { // parameter struct
	char pName[MAX];
	long pid;
	__u64 arrivalTime;
	__u64 burstTime;
	int priority;
} process_param;

#endif
