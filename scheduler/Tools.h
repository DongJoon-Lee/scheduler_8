#ifndef __TOOLS_H__
#define __TOOLS_H__


void makeProcess(int N) {
	srand(time(NULL));
	FILE *fp = fopen("processList.txt", "w");
	int arrTime[100] = {0};
	int burTime[100] = {0};
	int priority[100] = {0};
	int min = 11;

	// make new Processes
	for(int i = 0; i < N, i ++) { 
		arrTime[i] = rand()%11;
		burTime[i] = rand()%11;
		priority[i] = rand()%5 + 1;
		if (min > arrTime[i]) {
			min = arrTime[i];
		}
	}
	fprintf(fp, "%d\n", N);
	for(int i = 0; i < N; i ++) {
		fprintf(fp, "P%d %d %d %d\n", i, arrTime[i] - min, burTime[i], priority[i]);
	}
	fclose(fp);
}
#endif
