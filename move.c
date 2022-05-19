// move.c -> 화면에 사각형 출력하고 사용자 움직일 수 있게 하는 파일
// ver 0.2
// 단일파일로도 실행가능, 일단 임시로 맵 만들고 움직임 테스트 해 보기 위해 만듦.
#include "header.h"
int size = 50;
const int max_x = 100;
const int min_x = 2;
const int max_y = 51;
const int min_y = 2;
int map[50][50] = { 0 };
void gotoxy(int x, int y) {
	COORD Cur = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}

void printMap();
void flag(int level);
extern map[50][50];


int main() {
	//SetConsoleOutputCP(437);		// 확장아스키 사용법
	int x = 40, y = 12, ch;
	printf("\n");


	flag(1);
	printMap();
	//ch = '▷';
	while (1) {
		gotoxy(x, y);
		printf("▷\b\b");			// 주인공 문자 출력 부분
		ch = _getch();
		printf("  \b\b");			// 이동 시 주인공 문자 지우는 부분
		if (ch == 224) {		// 방향키 이동 부분
			ch = _getch();
			switch (ch) {
			case 72:
				if (y > min_y)		//x=0, 70, y = 0, 70부분이 경계이므로 그부분만 안닿게 설정
					y--;
				break;
			case 80:
				if (y < max_y)
					y++;
				break;
			case 75:
				if (x > min_x)
					x -= 2;
				break;
			case 77:
				if (x < max_x)
					x += 2;
				break;
			}
		}
		// 방향키 이동 후 기능들

	}
}



void printMap() {
	//char ch = '■';		// 변수에 저장하고 출력하면 이상하게 나옴
	int size = 50;
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
	printf("\n");
	return;
}

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