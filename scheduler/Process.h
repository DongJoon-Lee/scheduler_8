#ifndef __PROCESS_H__
#define __PROCESS_H__

//프로세스 구조체와 관련된 헤더파일입니다.
#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 20
#define TRUE 1
#define FALSE 0

// ----------- 프로세스 구조체 정의
typedef struct {
	char pid[MAX_LEN]; // pid
	int arrivalTime; // 도착시간 (task가 도착한 시간)
	int burstTime; // 실행해야되는 시간 
	int priority; // 우선순위 (작을수록 높음)
	int waitingTime; // 대기시간 (프로세스가 CPU를 얻기 위해 기다린 시간의 총 합, 시작부터 종료시까지 중 대기한 시간)
	int returnTime; // 반환시간
	int turnAroundTime; // turnaround 시간 (처음 들어와서 마지막에 나갈때까지의 시간)
	int responseTime; // 응답시간 (최초로 응답이 들어올 때까지 걸린 시간)
	int complete; // 완료 여부
} P; // 이 구조체를 사용하기 위한 이름 P

void pInit(P p[], int len) { // 프로세스 초기화 하는 부분입니다.
	for(int i = 0; i < len; i ++) {
		p[i].waitingTime = 0; // 대기시간 0으로 초기화
		p[i].returnTime = 0; // 반환시간 0
		p[i].responseTime = 0; // 응답시간 0
		p[i].complete = FALSE; // 완료 여부 FALSE
	}
}

typedef int Quantum;


#endif
