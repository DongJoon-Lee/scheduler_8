#ifndef __OOO_H__    //******스케줄링 명
#define __OOO_H__    //******스케줄링 명

//OOO 기법

#include "./Process.h"
#include "./Tools.h"


void OOO_Run(P *, int);   //******스케줄링 명
void Chart(P *, int);

// OOO 스케줄링 실행
// 프로세스 목록, 길이
void OOO(P *p, int len) {   //******스케줄링 명
    int totalWaitingTime = 0; // 총 대기시간
    int totalTurnAroundTime = 0; // 총 turnaround시간
    int totalResponseTime = 0; // 총 응답시간

    pInit(p, len); // 프로세스 배열을 초기화해줍니다.
    mergeSort_arrivalTime(p, 0, len); //arrivalTime을 기준으로 정렬해줍니다.
    //******스케줄링 명
    OOO_Run(p, len); // OOO를 실행시키는 함수입니다. 길이가 길어서 따로 뺐습니다.

    //시간 정리
    for(int i = 0; i < len; i ++) {
        p[i].returnTime = p[i].turnAroundTime + p[i].arrivalTime; // 프로세스 returnTime 정리
        p[i].responseTime = p[i].waitingTime; // 프로세스 응답시간 정리
        totalWaitingTime += p[i].waitingTime; // 총 대기시간 정리
        totalTurnAroundTime += p[i].turnAroundTime; // 총 turnaround시간 정리
        totalResponseTime += p[i].responseTime; // 총 응답시간 정리
    }
    //콘솔창에 출력해줍니다.
    //나중에 필요한 부분만 빼고 제거할 예정입니다.
    Chart(p, len);
    printf("\n\tAverage Waiting Time     : %-2.2lf\n", (double)totalWaitingTime / (double)len);
    printf("\tAverage Turnaround Time  : %-2.2lf\n", (double)totalTurnAroundTime / (double)len);
    printf("\tAverage Response Time    : %-2.2lf\n\n", (double)totalResponseTime / (double)len);
    printTable(p, len);
}

void OOO_Run(P *p, int len) {    //******스케줄링 명
    int curTime = 0; // 현재 시간 저장 변수
    int min = 0; // 최소시간 idx 저장 변수
    //첫 번째 들어오는 친구는 그냥 계산합니다.
    p[0].complete = TRUE;
    p[0].returnTime = p[0].burstTime;
    p[0].turnAroundTime = p[0].burstTime - p[0].arrivalTime;
    p[0].waitingTime = 0;
    
    curTime = p[0].burstTime; // 현재 시간은 들어오자마자 실행한 프로세스 시간입니다.

    //이미 하나가 끝났으므로 idx는 1부터 시작합니다.
    for(int i = 1; i < len; i ++) {
        
        // maybe fill here
    
        p[min].waitingTime = curTime - p[min].arrivalTime; // 실행 예정 프로세스 대기 시간
        p[min].complete = TRUE; // 이제 실행 예정입니다.
        curTime += p[min].burstTime; // 프로세스 실행시간만큼 현재 시간이 늘어납니다.
        p[min].returnTime = curTime; // 이때 끝나는거니까 넣어줍니다.
        p[min].turnAroundTime = p[min].returnTime - p[min].arrivalTime; // 프로세스 turnArountTime을 정리해줍니다.
    }
}

//간트차트를 그립니다.
void Chart(P *p, int len) {
    //들여쓰기
    printf("\t-");

    for(int i = 0; i < len; i ++) {
        for(int j = 0; j < p[i].burstTime; j ++) { // 한 프로세스가 돌아간 시간만큼 --를 출력해줍니다.
            printf("--"); 
        }
        printf("-");
    }
    printf("\n\t|"); // 들여쓰기 후 벽을 그려줍니다.

    //차트에서 pid를 써주는 부분입니다.
    for(int i = 0; i < len; i ++) {
        for(int j = 0; j < p[i].burstTime-1; j ++) {
            printf(" ");
        }
        printf("%s", p[i].pid);
        for(int j = 0; j < p[i].burstTime-1; j ++) {
            printf(" ");
        }
        printf("|");
    }

    //차트 아랫부분 선을 그려줍니다.
    printf("\n\t-");
    for(int i = 0; i < len; i ++) {
        for(int j = 0; j < p[i].burstTime; j ++) {
            printf("--");
        }
        printf("-");
    }
    printf("\n\t");

    //프로세스가 교체되는 시간을 입력해줍니다.
    printf("0");
    for(int i = 0; i < len; i ++) {
        for(int j = 0; j < p[i].burstTime; j ++) {
            printf("  ");
        }
        printf("\b%2d", p[i].returnTime);
    }
    printf("\n");
}

#endif
        
