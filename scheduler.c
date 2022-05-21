#include "scheduler.h"

int main(void) {
	// --------------------------------------기본 변수
	int processCount = 0; // 프로세스의 개수를 저장하는 변수입니다.
	Quantum q; // Time quantum을 저장하는 변수입니다.
	P *p;  // 프로세스 구조체입니다.

	// --------------------------------------메인 함수
	// ----------- 기본 정보 읽어오기
	FILE *file = fopen("processList.txt", "r"); // 파일 열기
	if (file == NULL) { // 파일 열기 실패했을 때
		printf("파일을 여는데 실패했습니다.\n");
		return 0;
	}

	fscanf(file, "%d %d", &processCount, &q); // 파일에서 숫자 두개를 읽어서 processCOunt와 Quantum에 저장합니다.
	
	p = (P *)malloc(sizeof(P)*processCount); // p 구조체에 메모리를 할당해줍니다.

	for(int i = 0; i < processCount; i ++) { // 프로세스 개수만큼 pid, arrivalTime, burstTime, priority를 읽어줍니다.
		fscanf(file, "%s %d %d %d", p[i].pid, &p[i].arrivalTime, &p[i].burstTime, &p[i].priority);
	}
	// ----------- 기본 정보 읽어오기 끝

	// ----------- 각 스케줄러 실행
	// ----- 범용OS 스케줄러
	//FCFS 실행
	// puts("Run FCFS Scheduling\n\n");
	// FCFS(p, processCount);
	//SJF 실행
	// puts("\n\t----------------------");
	// puts("\t| Run SJF Scheduling |");
	// puts("\t----------------------\n\n");
	puts("\n\n\tRun SJF Scheduling\n\n");
	SJF(p, processCount);
	//RR 실행
	// puts("\n\tRun RR Scheduling\n\n");
	// RR(p, processCount, q);

	// ----- RTOS 스케줄러
	//RM 실행
	// puts("Run RM Scheduling\n\n");
	// RM(p, processCount);
	
	//EDF 실행
	// puts("Run EDF Scheduling\n\n");
	//EDF(p, processCount);
	// ----------- 스케줄러 실행 끝

	// ----------- 마무리
	fclose(file); // 파일 닫아주기
	free(p); // 프로세스 malloc 해제
	
	return 0;
}

	



