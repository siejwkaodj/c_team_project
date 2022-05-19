// 사각형, 장애물, 깃발 출력하는 함수.
#include "header.h"
void gotoxy(int x, int y);

void printMap() {
	extern max_x;
	extern min_x;
	extern max_y;
	extern min_y;
	extern map[50][50];
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