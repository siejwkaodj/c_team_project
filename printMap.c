#include "header.h"
extern void gotoxy(int x, int y);
extern const int size;
extern int level;
extern int map[50][50];
extern int player_shape;
extern const int first_line;
extern void menu(int);

void printSquare(int, int, int, int);
void printBlank(int x1, int y1, int x2, int y2);
void printText(char *, int, int);

void printMap() {
	extern max_x;
	extern min_x;
	extern max_y;
	extern min_y;
	//char ch = '■';		// 변수에 저장하고 출력하면 이상하게 나옴
	system("cls");
	// 맵 전체 사각형 출력
	printSquare(min_x-2, min_y-1, max_x+2, max_y+1);
	
	// 부가정보 출력; 입력문구, 1줄띔, 경계까지 고려해 y = 3에 출력
	printSquare(105, 2, 188, 10);

	printText("level(난이도) : ", 107, 4);
	printf("%d  /  ", level);
	gotoxy(142, 4);
	printf("  /  ");
	printf("플레이어 : ");
	switch(player_shape){
		case 0:
			printf("◈");
		break;
		case 1:
			printf("◇");
		break;
		case 2:
			printf("◆");
		break;
		case 3:
			printf("엄");
		break;
		case 4:
			printf("준");
		break;
		case 5:
			printf("식");
		break;
		default:
			printText("ERROR : error in printMap.c - cant print player_shape", 0, 0);
		break;
	}
	printf("  /  ");
	
	printText("▩ : 장애물 - 지나가지 못합니다.", 107, 6);
	printText("교 : 교수   - 만나면 3초간 움직이지 못합니다.", 107, 7);
	printText("▶ : 깃발   - 획득하면 보물 혹은 랜덤한 이벤트가 발생합니다. ", 107, 8);
	
	printText("-------------------------- 적용중인 버프 / 디버프 효과 --------------------------", 107, first_line+9);
	// 부가정보 감싸는 사각형 출력
	printSquare(105, 12, 188, 52);

	for (int i = 0; i < size - 1; i++) {		// 출력시 경계 조심
		for (int j = 0; j < size - 1; j++) {	// size-2 만큼 출력; 깃발 생성시에도 맨 모서리 부분에는 생성 x
			gotoxy(min_x+j*2, min_y+i);
			switch (map[i][j]) {
			case 0:	// 빈칸
				//printf("%2d", map[i][j]);
				printf("  ");				// **또는 띄어쓰기 2칸(가로는 2배)
				break;
			// case 1:		// 플레이어
			// 	printf("◈");
			// 	break;
			case 2:		// 장애물
				printf("▩");
				break;
			case 3:		// 교수
				printf("교");
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

// 두 점을 잡고, 그 점을 이은 사각형을 그리는 함수. 왼쪽 위와 오른쪽 아래의 두 점이 필요.
void printSquare(int x1, int y1, int x2, int y2) {
	// x1 < x2, y1 < y2라고 가정.
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

// x1, y1, x2, y2 인자를 전달, 두 점으로 그린 사각형 내의 공간을 모두 지워줌.
void printBlank(int x1, int y1, int x2, int y2) {
	int px = x1, py = y1;
	
	while (py <= y2) {
		px = x1;
		while (px <= x2) {
			gotoxy(px, py);
			printf(" ");
			px++;
		}
		py++;
	}	
	return;
}

// 플레이어 위치, 장애물, 깃발 생성 함수
void flag(int level) {
	srand((unsigned)time(NULL));
	int x1, y1;         // 좌표 임시 변수
	int wallNum = 0;    // 장애물 개수 지정
	int num = 0;        // 깃발 개수 세는것
	int i = 0;

	// map 초기화
	for(int i = 0; i < size; i++){
		for(int j = 0; j < size; j++){
			map[i][j] = 0;
		}
	}
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
	// 교수 생성
	i = 0;
	while (i++ < num) {
		x1 = rand() % (size - 1);
		y1 = rand() % (size - 1);
		if (map[y1][x1] == 0) {
			map[y1][x1] = 3;                // 장애물 - 2로 표시
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

// 기본 위치 107, 12 정도
void printText(char * text, int x, int y){
	gotoxy(x, y);
	printf("%s", text);
	return;
}