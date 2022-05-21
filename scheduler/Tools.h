#ifndef __TOOLS_H__
#define __TOOLS_H__

#include "./Process.h"
// 정렬하는 파일입니다.

//returnTime을 기준으로 비교합니다. 프로세스 a의 returnTime이 더 작으면 -1, b가 더 작으면 1, 같으면 0입니다.
int compareReturnTime(const void *a, const void *b) {
	//a와 b를 process구조체로 바꿉니다. 
	P *A = (P *)a;
	P *B = (P *)b;

	//A가 작음
	if (A->returnTime < B->returnTime) {
		return -1;
	}
	//B가 작음
	else if (A->returnTime > B->returnTime) {
		return 1;
	}
	//같음
	else {
		return 0;
	}
}

//쪼개진 배열을 다시 합치는 함수입니다.
//arr은 프로세스 배열, left, mid, right는 위와 같습니다.
void merge(P *arr, int left, int mid, int right) {
	int idx1=left; // 1번 배열의 인덱스를 가리키는 변수입니다.
	int idx2=mid+1; // 2번 배열의 인덱스를 가리키는 변수입니다.
	int idx; // 최종 배열의 인덱스를 가리키는 변수입니다.
	P *retArr = (P *)malloc(sizeof(P)*(right+1)); // 최종 배열을 저장할 배열입니다.
	idx = left; // 최종 배열의 인덱스를 가장 왼쪽으로 옮깁니다.

	//1번 배열과 2번 배열의 idx위치의 값을 비교해서 작은 수를 최종 배열에 옮겨주는 친구입니다.
	while(idx1<=mid && idx2<=right) {
		//1번 배열의 값이 2번 배열보다 작거나 같은 경우
		if (arr[idx1].arrivalTime <= arr[idx2].arrivalTime) {
			retArr[idx] = arr[idx1];
			idx1++; // 이미 넣어줬으니 하나 밀어줍니다.
		}
		// 1번 배열의 값이 2번 배열보다 큰 경우
		else {
			retArr[idx] = arr[idx2];
			idx2++; // 하나 밀어줍니다.
		}
		idx++; // 어떤 경우이던지 idx는 채워졌으니 밀어줍니다.
	}
	// 1번 배열 혹은 2번 배열 둘 중 하나가 끝까지 간 경우입니다.
	// 하나는 아직 남아있을겁니다.

	// 1번 배열이 남았습니다.
	if (right < idx2) { // idx2의 값이 right를 넘어갔으면, 2번 배열은 다 사용한 겁니다.
		for(int i = idx1; i <= mid; i ++) {
			retArr[idx] = arr[i];
			idx++;
		} // 1번 배열의 idx가 mid를 넘어갈 때까지 채워줍니다.
	}
	else { // 1번 배열을 다 사용한 경우입니다.
		for(int i = idx2; i <= right; i ++) {
			retArr[idx] = arr[i];
			idx++;
		}
	}
	for(int i = left; i <= right; i ++) {
		arr[i] = retArr[i]; // 원래 배열에 정렬한 배열을 넣어줍니다.
	}
	
	free(retArr); // 메모리 할당을 해제해줍니다.
}

// arrivalTime을 기준으로 mergeSort합니다.
//p arr은 프로세스 배열, left는 가장 왼쪽 idx, right는 가장 오른쪽 idx입니다.
void mergeSort_arrivalTime(P *arr, int left, int right) {
	int mid; // merge sort를 하기 위해 자르는 중간 idx입니다.
	//이 경우가 아니면 이미 최소 단위이므로 더 할 필요 없습니다.
	if (left < right) {
		mid = (left+right)/2; // mid를 계산해줍니다.

		//재귀부분입니다.
		mergeSort_arrivalTime(arr, left, mid);
		mergeSort_arrivalTime(arr, mid+1, right);
		
		//다시 합칩니다.
		merge(arr, left, mid, right);
	}
}

//returnTime을 기준으로 quickSort를 수행합니다.
void quickSort_returnTime(P *p, int len) {
    qsort(p, len, sizeof(P), compareReturnTime);
}

//프로세스 시뮬레이션이 종료된 후 정리해주는 표를 출력합니다.
void printTable(P *p, int len) {
	//열 설정
	puts("\t+-----+------------+--------------+----------+-------------+-----------------+--------------+-----------------+");
	puts("\t| PID | Burst Time | Arrival Time | Priority | Return Time |  Response Time  | Waiting Time | Turnaround Time |");
	puts("\t+-----+------------+--------------+----------+-------------+-----------------+--------------+-----------------+");
	
	//프로세스 개수만큼 출력해줍니다.(당연)
	for(int i = 0;i <len; i ++) {
		printf("\t| %3s |     %3d    |      %3d     |    %3d   |     %3d     |      %3d        |      %3d     |        %3d      |\n",
			p[i].pid, p[i].burstTime, p[i].arrivalTime, p[i].priority, p[i].returnTime, p[i].responseTime, p[i].waitingTime, p[i].turnAroundTime);
			puts("\t+-----+------------+--------------+----------+-------------+-----------------+--------------+-----------------+");
	}
	printf("\n");
}

#endif
