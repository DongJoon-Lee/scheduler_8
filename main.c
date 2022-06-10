#include "main.h"

int processNum; // Number of Processes

int main(void) {
	makeProcess(5);
	FILE *file = fopen("processList.txt", "r"); // open Process List file.
	if (file == NULL) { // if fail
		printf("Fail to open file.\n");
		return 0;
	}

	fscanf(file, "%d", &processNum); // save first number as Number of Processes

	pthread_t test[processNum]; // make threads 
	process_param param[processNum]; // paramerter of each thread
	
	for(int i = 0; i < processNum; i ++) {		
		fscanf(file, "%s %llu %llu %d", param[i].pName, &param[i].arrivalTime, &param[i].burstTime, &param[i].priority); // save parameters
	}

	puts("Scheduling test start.\n"); // just notification

	FCFS(test, param, processNum); // Run FCFS Scheduling
	SJF(test, param, processNum);	// Run SJF Scheduling	
	RR(test, param, processNum); // Run RR Scheduling
	PRIORITY(test, param, processNum); // Run Priority Scheduling

	return 0;
}
