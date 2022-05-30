#include "header.h"
extern gotoxy();

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