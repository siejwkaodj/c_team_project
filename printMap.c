#include "header.h"
extern gotoxy(int x, int y);
extern size;
extern map[50][50];

void printMap() {
	extern max_x;
	extern min_x;
	extern max_y;
	extern min_y;
	extern size;
	//char ch = '■';		// 변수에 저장하고 출력하면 이상하게 나옴

	int x = min_x - 2, y = min_y - 1;
	for (int i = 0; i <= size * 2 + 2; i++) {
		gotoxy(x + i, y);
		printf("─");						// 윗 가로 출력
		gotoxy(x + i, y + size + 1);
		printf("─");						// 아래 가로 출력
	}
	for (int i = 0; i <= size + 1; i++) {
		gotoxy(x, y + i);
		printf("│");						// 왼쪽 세로 출력
		gotoxy(x + size * 2 + 2, y + i);
		printf("│");						// 오른쪽 세로 출력
	}
	gotoxy(min_x - 2, min_y - 1);
	printf("┌");
	gotoxy(max_x + 2, min_y - 1);
	printf("┐");
	gotoxy(min_x - 2, max_y + 1);
	printf("└");
	gotoxy(max_x + 2, max_y + 1);
	printf("┘");

	// 부가정보 출력; 입력문구, 1줄띔, 경계까지 고려해 y = 3에 출력
	gotoxy(105, 3);
	printf("□ : 빈칸");
	gotoxy(105, 4);
	printf("◈ : 플레이어");
	gotoxy(105, 5);
	printf("▩ : 장애물");
	gotoxy(105, 6);
	printf("◎ : 교수");
	gotoxy(105, 7);
	printf("▶ : 깃발");

	for (int i = 0; i < size - 1; i++) {		// 출력시 경계 조심
		gotoxy(2, i + 2);						// 경계 고려해서 설정할 것.
		for (int j = 0; j < size - 1; j++) {	// size-2 만큼 출력; 깃발 생성시에도 맨 모서리 부분에는 생성 x
			switch (map[i][j]) {
			case 0:	// 빈칸
				//printf("%2d", map[i][j]);
				printf("  ");				// **또는 띄어쓰기 2칸(가로는 2배)
				break;
			case 1:		// 플레이어
				printf("◈");
				break;
			case 2:		// 장애물
				printf("▩");
				break;
			case 3:		// 교수, 임시로 설정
				printf("◎");
				break;
			case 4:		// 깃발 및 보물
			case 5:
				printf("▶");
				break;
			}
		}
	}
	gotoxy(102, 52);
	printf("\n\n");
	return;
}

void printSquare(int x1, int y1, int x2, int y2) {
	// x1 < x2, y1 < y2라고 가정.
	// 두 점을 잡고, 그 점을 이은 사각형을 그리는 함수. 왼쪽 위와 오른쪽 아래의 두 점이 필요.
	int px = x1, py = y1;

	while (px <= x2) {
		gotoxy(px, y1);
		printf("─");
		gotoxy(px, y2);
		printf("─");
		px++;
	}
	while (py <= y2) {
		gotoxy(x1, py);
		printf("│");
		gotoxy(x2, py);
		printf("│");
		py++;
	}
	gotoxy(x1, y1);
	printf("┌");
	gotoxy(x1, y2);
	printf("└");
	gotoxy(x2, y1);
	printf("┐");
	gotoxy(x2, y2);
	printf("┘");
	
	return;
}

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