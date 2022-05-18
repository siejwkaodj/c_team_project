// move.c -> 화면에 사각형 출력하고 사용자 움직일 수 있게 하는 파일
// ver 0.2
#include "header.h"
int size = 50;

void gotoxy(int x, int y) {
	COORD Cur = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
void printSquare();

int move() {
	//SetConsoleOutputCP(437);		// 확장아스키 사용법
	int x = 40, y = 12, ch;
	printf("\n");
	printSquare();

	ch = '▷';
	while (1) {
		gotoxy(x, y);
		printf("▷\b\b");			// 주인공 문자 출력 부분
		ch = _getch();
		printf("  \b\b");			// 이동 시 주인공 문자 지우는 부분
		if (ch == 224) {		// 방향키 이동 부분
			ch = _getch();
			switch (ch) {
			case 72:
				if (y > 1)		//x=0, 70, y = 0, 70부분이 경계이므로 그부분만 안닿게 설정
					y--;
				break;
			case 80:
				if (y < size - 1)
					y++;
				break;
			case 75:
				if (x > 2)
					x -= 2;
				break;
			case 77:
				if (x < 2 * size - 2)
					x += 2;
				break;
			}
		}
		// 방향키 이동 후 기능들

	}
}

void printSquare() {	// 사각형 틀 출력하는 함수, 이동가능범위보다 1자리 더 커야함.
	//char ch = '■';		// 변수에 저장하고 출력하면 이상하게 나옴
	int size_1 = 50;
	int x = 0, y = 1;
	for (int i = 0; i <= size_1 * 2; i++) {
		gotoxy(x + i, y);
		printf("─");						// 윗 가로 출력
		gotoxy(x + i, y + size_1);
		printf("─");						// 아래 가로 출력
	}
	for (int i = 0; i <= size_1; i++) {
		gotoxy(x, y + i);
		printf("│");						// 왼쪽 세로 출력
		gotoxy(x + size_1 * 2, y + i);
		printf("│");						// 오른쪽 세로 출력
	}
	gotoxy(0, 1);
	printf("┌");
	gotoxy(size * 2, 1);
	printf("┐");
	gotoxy(0, size + 1);
	printf("└");
	gotoxy(size * 2, size + 1);
	printf("┘");
	return;
}