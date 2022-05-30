//main 함수
#define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#define HOR 190	// define으로 정의해 주는것은 파일 안에서 해줘야 오류가 안 남

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
	//cols 가로길이 lines 세로길이  값 넣어줘야함 -> 190 * 60으로 일단 설정
	// 변수 안들어감. 숫자로 직접 넣기.
	system("mode con cols=190 lines=60");	// cols= 190하면 오류남. 꼭 등호 뒤에 붙여서 하기.
	//GAME START 혹은 게임이름으로 변경 필요...0530 완료
	text_align_center(HOR, " #####      ##    ##   ##  #######                #####   ########    ##      ######  ########\n");
	text_align_center(HOR, "##   ##    ####   ### ###   ##  ##               ##   ##  #  ##  #   ####     ##  ##  #  ##  #\n");
	text_align_center(HOR, "##        ##  ##  #######   ##                   ##          ##     ##  ##    ##  ##     ##   \n");
	text_align_center(HOR, "##        ######  ## # ##   ####                 #######     ##     ######    #####      ##   \n");
	text_align_center(HOR, "##  ###   ##  ##  ##   ##   ##                        ##     ##     ##  ##    ####       ##   \n");
	text_align_center(HOR, "##   ##   ##  ##  ##   ##   ##  ##               ##   ##     ##     ##  ##    ## ##      ##   \n");
	text_align_center(HOR, " #####    ##  ##  ##   ##  #######                #####     ####    ##  ##    ###  ##   ####  \n");

	char letter;
	letter = _getch();

	while (letter == '\n') {
		letter = _getch();
	}



	text_align_center(HOR, "다소 민감한 내용이 포함되어 있으니 대학생 이상은 플레이에 조심하세요.");
	system("cls");	// 주석추가


	// 여기서 text_align_center 에 \n\n\n.. 담아놓으면 엔터키 출력 후 다음 줄 첫 번째 열로 이동함.
	// TODO : 우리가 원하는 출력을 얻기 위해서는 앞에 이걸 붙여주면 됨.
	// printf("\n\n\n\n\n\n\n");	// 이거 주석해제하고 밑에 엔터키 여러개 지워줄 것.
	// TODO : 그리고 밑에 1. 게임설명 부분도 똑같이 처리 필요.
	// 가장 좋은 방법은 gotoxy()로 좌표를 직접 입력해 주는것임.
	text_align_center(HOR, "\n\n\n\n\n\n\n플레이어의 이름을\n");
	text_align_center(HOR, "입력하세요.");

	//Scanf 출력되는 지점 변경 필요
	// gotoxy(HOR/2, 15);
	scanf("%s", player_name);











	while (1) {
		int player_select_1, player_select_2;
		// printf("\n\n\n\n\n\n\n");	// 밑에 엔터키 앞부분만 지워줄 것.
		text_align_center(HOR, "\n\n\n\n\n\n\n1. 게임설명\n\n");
		text_align_center(HOR, "2. 난이도 선택\n\n");
		text_align_center(HOR, "3. 캐릭터 선택\n\n");
		text_align_center(HOR, "4. 개발자 모드\n\n");
		text_align_center(HOR, "5. 졸업기록 열람\n\n\n");
		// gotoxy(HOR/2, 38);
		scanf("%d", &player_select_1);

		while (player_select_1 < 1 || player_select_1 > 5) {
			system("cls");	// clear screen후 문자출력해야지 안그러면 다 지워진 후에 출력함.
			text_align_center(HOR, "\n\n다시 입력해주세요.");
			// printf("\n\n\n\n\n\n\n"); 	// 밑에 엔터키 앞부분만 지워줄 것.
			text_align_center(HOR, "\n\n\n\n\n\n\n1. 게임설명\n\n");
			text_align_center(HOR, "2. 난이도 선택\n\n");
			text_align_center(HOR, "3. 캐릭터 선택\n\n");
			text_align_center(HOR, "4. 개발자 모드\n\n");
			text_align_center(HOR, "5. 졸업기록 열람\n\n\n");

			// gotoxy(HOR/2, 38);
			scanf("%d", &player_select_1);


		}
		
		
		switch (player_select_1) {
		case 1:
			text_align_center(HOR, "게임 설명\n");	// 이름 오류 수정
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

// 이부분도 gotoxy() 이용해서 gotoxy((HOR - strlen(text))/2, y); 로 해주는 것이 가장 깔끔함.
// 이방식은 왼쪽에 문자가 있을 시 그것까지 포함해서 정렬을 시켜버림.
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

/* GAME OVER
text_align_center(HOR, " #####      ##    ##   ##  #######                #####    ##  ##  #######   ######  \n");
text_align_center(HOR, "##   ##    ####   ### ###   ##  ##               ##   ##   ##  ##   ##  ##   ##  ##  \n");
text_align_center(HOR, "##        ##  ##  #######   ##                   ##   ##   ##  ##   ##       ##  ##  \n");
text_align_center(HOR, "##        ######  ## # ##   ####                 ##   ##   ##  ##   ####     #####   \n");
text_align_center(HOR, "##  ###   ##  ##  ##   ##   ##                   ##   ##   ##  ##   ##       ####    \n");
text_align_center(HOR, "##   ##   ##  ##  ##   ##   ##  ##           ##  ##   ##    ####    ##  ##   ## ##   \n");
text_align_center(HOR, " #####    ##  ##  ##   ##  #######                #####      ##    #######   ###  ## \n");
*/