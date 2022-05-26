//main 함수
#include "header.h"
#define HOR 80	// define으로 정의해 주는것은 파일 안에서 해줘야 오류가 안 남

void text_align_center(int columns, char* text);
void gotoxy(int x, int y);

// 외부정의 함수
void printMap();
void flag(int level);

// 전역변수
int map[50][50] = {0};	// 일단 전부 0으로 초기화
const int size = 50;	// 맵 크기 설정
const int max_x = 100;	// 플레이어 x, y 이동 범위 최대, 최소값
const int min_x = 2;
const int max_y = 51;
const int min_y = 2;

// 0519 - 한성준, gotoxy와 맵출력, 플레이어 움직이게 하는 부분 등 추가.
int main(void) {
	int x = 40, y = 12, ch;	// 플레이어 위치
	char player_name[] = {0};
	//cols 가로길이 lines 세로길이  값 넣어줘야함
	system("mode con cols= lines=")
	//GAME START 혹은 게임이름으로 변경 필요
	text_align_center(HOR, " #####      ##    ##   ##  #######                #####    ##  ##  #######   ######  \n");
	text_align_center(HOR, "##   ##    ####   ### ###   ##  ##               ##   ##   ##  ##   ##  ##   ##  ##  \n");
	text_align_center(HOR, "##        ##  ##  #######   ##                   ##   ##   ##  ##   ##       ##  ##  \n");
	text_align_center(HOR, "##        ######  ## # ##   ####                 ##   ##   ##  ##   ####     #####   \n");
	text_align_center(HOR, "##  ###   ##  ##  ##   ##   ##                   ##   ##   ##  ##   ##       ####    \n");
	text_align_center(HOR, "##   ##   ##  ##  ##   ##   ##  ##           ##  ##   ##    ####    ##  ##   ## ##   \n");
	text_align_center(HOR, " #####    ##  ##  ##   ##  #######                #####      ##    #######   ###  ## \n");

	char letter;
	letter = _getch();

	while (letter == '\n') {
		letter = _getch();
	}



	text_align_center(HOR, "다소 민감한 내용이 포함되어 있으니 대학생 이상은 플레이에 조심하세요.");
	//텍스트 클리어



	text_align_center(HOR, "\n\n\n\n\n\n\n플레이어의 이름을\n");
	text_align_center(HOR, "입력하세요.");

	//Scanf 출력되는 지점 변경 필요
	scanf("%s", player_name);











	while (1) {
		int player_select_1, player_select_2;

		text_align_center(HOR, "\n\n\n\n\n\n\n1. 게임설명\n\n");
		text_align_center(HOR, "2. 난이도 선택\n\n");
		text_align_center(HOR, "3. 캐릭터 선택\n\n");
		text_align_center(HOR, "4. 개발자 모드\n\n");
		text_align_center(HOR, "5. 졸업기록 열람\n\n\n");
		
		scanf("%d", &player_select_1);

		while (player_select_1 < 1 || player_select_1 > 5) {
			text_align_center(HOR, "\n\n다시 입력해주세요.");
			//텍스트 클리어
			text_align_center(HOR, "\n\n\n\n\n\n\n1. 게임설명\n\n");
			text_align_center(HOR, "2. 난이도 선택\n\n");
			text_align_center(HOR, "3. 캐릭터 선택\n\n");
			text_align_center(HOR, "4. 개발자 모드\n\n");
			text_align_center(HOR, "5. 졸업기록 열람\n\n\n");
			scanf("%d", &player_select_1);


		}
		
		
		switch (player_select_1) {
		case 1:
			text_aliign_center(HOR, "게임 설명\n");
			//게임 설명 추가 요망
			text_align_center(HOR, "\n\n뒤로 가기 - ESC");
			player_select_2 = _getch();
			while (player_select_2 != 27) {
				player_select_2 = _getch();
			}
			break;


		case 2:

		case 3:

		case 4:

		case 5:

		// 오류나서 일단 default문 추가
		default:
		break;
		
		
		
		}
		// 게임 실행 부분, 실행하려면 나머지부분 주석처리하고 실행
		/*
		flag(1);
		system("cls");
		printMap();
		while (1) {
			gotoxy(x, y);
			printf("▷\b\b");			// 주인공 문자 출력 부분
			ch = _getch();
			printf("  \b\b");			// 이동 시 주인공 문자 지우는 부분
			if (ch == 224) {		// 방향키 이동 부분
				ch = _getch();
				switch (ch) {
				
				// 판정 함수 추가 부분
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
		}
		*/
	}
	return 0;
}


void text_align_center(int columns, char* text)
{
	int indent = (columns - strlen(text)) / 2; // 왼쪽 여백 구하기 
	for (int i = 0; i < indent; i++)
	{
		putchar(' '); // 왼쪽 여백 채우기 
	}
	printf("%s\n", text);
}

void gotoxy(int x, int y) {
	COORD Cur = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
}
