#include "header.h"
// flag.c -> 플레이어, 장애물, 깃발 위치 생성하는 함수
// 외부 전역변수들
extern size;
extern map[50][50];

// 플레이어 위치, 장애물, 깃발 생성 함수
void flag(int level) {
	srand((unsigned)time(NULL));
	int x1, y1;         // 좌표 임시 변수
	int wallNum = 0;    // 장애물 개수 지정
	int num = 0;        // 깃발 개수 세는것
	// 장애물 생성
	switch (level) {
	case 1:
		wallNum = 10;       // 장애물 개수
		num = 10;           // 깃발 개수
		break;
	case 2:
		wallNum = 20;
		num = 15;
		break;
	case 3:
		wallNum = 25;
		num = 20;
		break;
	}
	// 장애물 생성	-> 범위는 0~49 까지
	while (wallNum > 0) {
		x1 = rand() % (size - 1);
		y1 = rand() % (size - 1);
		if (map[y1][x1] == 0) {
			map[y1][x1] = 2;                // 장애물 - 2로 표시
			wallNum--;
		}
	}
	// 깃발 생성 
	while (num > 1) {                       // 한 개는 보물 생성해야함 -> 뒤에서 while문 돌려줌, 이미 있는 곳에 생기면 안 되서 while로 돌려줌.
		x1 = rand() % (size - 1);
		y1 = rand() % (size - 1);
		if (map[y1][x1] == 0) {
			map[y1][x1] = 4;                // 깃발 - 4로 표시
			num--;
		}
	}
	// 보물 생성
	while (num > 0) {
		x1 = rand() % (size - 1);
		y1 = rand() % (size - 1);
		if (map[y1][x1] == 0) {
			map[y1][x1] = 5;                // 보물 - 5로 표시
			num--;
		}
	}
	return;
}