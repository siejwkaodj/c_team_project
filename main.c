//main 함수
// #define _CRT_SECURE_NO_WARNINGS
#include "header.h"
#define HOR 190	// define으로 정의해 주는것은 파일 안에서 해줘야 오류가 안 남

void text_align_center(int columns, char* text);
void gotoxy(int x, int y);

// 외부정의 함수
void printMap();
void flag(int level);
extern printSquare(int, int, int, int);

// 전역변수
int map[50][50] = { 0 };	// 일단 전부 0으로 초기화
const int size = 50;	// 맵 크기 설정
const int max_x = 100;	// 플레이어 x, y 이동 범위 최대, 최소값
const int min_x = 2;
const int max_y = 51;
const int min_y = 2;

// 0519 - 한성준, gotoxy와 맵출력, 플레이어 움직이게 하는 부분 등 추가.
int main(void) {
	int x = 40, y = 12, ch;	// 플레이어 위치
	int tx, ty;				// 플레이어 이동 임시 x, y좌표
	int level = 0;			// 난이도 - 1 (초급), 2 (중급), 3 (고급)
	int game_start = 1;		// 게임 끝났는지 확인해주는 변수
	char player_name[] = { 0 };
	
	time_t tm1, tm2; // 게임 시간 받는 변수
	
	int rank[4] = { 0 }; // rank[0] = 학사 취득 학기 저장, rank[1] = 석사 취득 학기 저장, rank[2] = 박사 취득 학기 저장
	
	//cols 가로길이 lines 세로길이  값 넣어줘야함 -> 190 * 60으로 일단 설정
	// 변수 안들어감. 숫자로 직접 넣기.
	system("mode con cols=190 lines=60");	// cols= 190하면 오류남. 꼭 등호 뒤에 붙여서 하기.
	//GAME START 혹은 게임이름으로 변경 필요...0530 완료

	gotoxy(0, 10);
	text_align_center(HOR, " #####      ##    ##   ##  #######                #####   ########    ##      ######  ########");
	text_align_center(HOR, "##   ##    ####   ### ###   ##  ##               ##   ##  #  ##  #   ####     ##  ##  #  ##  #");
	text_align_center(HOR, "##        ##  ##  #######   ##                   ##          ##     ##  ##    ##  ##     ##   ");
	text_align_center(HOR, "##        ######  ## # ##   ####                 #######     ##     ######    #####      ##   ");
	text_align_center(HOR, "##  ###   ##  ##  ##   ##   ##                        ##     ##     ##  ##    ####       ##   ");
	text_align_center(HOR, "##   ##   ##  ##  ##   ##   ##  ##               ##   ##     ##     ##  ##    ## ##      ##   ");
	text_align_center(HOR, " #####    ##  ##  ##   ##  #######                #####     ####    ##  ##    ###  ##   ####  ");

	char letter;
	letter = _getch();

	while (letter == '\n') {
		letter = _getch();
	}


	gotoxy(0, 20);
	text_align_center(HOR, "[ 다소 민감한 내용이 포함되어 있으니 학부생 및 대학원생은 플레이에 조심하세요. ]\n");
	for (int i = 0; i < 3; i++) {
		gotoxy(0, 25);
		text_align_center(HOR, "                    ");	// 이전 글자 지워주는 부분
		gotoxy(0, 25);
		text_align_center(HOR, "starting in");
		gotoxy(HOR / 2 + 12 / 2, 25);	// starting in 글자길이 대충 12로 계산.
		printf("%d...", 3 - i);
		Sleep(1 * 1000);
	}
	system("cls");	// 주석추가


	// 여기서 text_align_center 에 \n\n\n.. 담아놓으면 엔터키 출력 후 다음 줄 첫 번째 열로 이동함.
	// TODO : 우리가 원하는 출력을 얻기 위해서는 앞에 이걸 붙여주면 됨.
	
	// TODO : 그리고 밑에 1. 게임설명 부분도 똑같이 처리 필요.
	// 가장 좋은 방법은 gotoxy()로 좌표를 직접 입력해 주는것임.
	
	gotoxy(0, 7);	// text_align_center 함수 쓸거면 x = 0 이어야함.
	text_align_center(HOR, "플레이어의 이름을\n");
	text_align_center(HOR, "입력하세요.");

	//Scanf 출력되는 지점 변경 필요 -> 해결
	gotoxy(HOR/2, 10);
	scanf("%s", player_name);


	// 메뉴 시작
	while (1) {
		int player_select_1, player_select_2;
		system("cls");
		gotoxy(0, 7);
		printSquare(80, 10, 110, 35);
		gotoxy(0, 12);
		text_align_center(HOR, "1. 게임설명\n\n");
		text_align_center(HOR, "2. 난이도 선택\n\n");
		text_align_center(HOR, "3. 캐릭터 선택\n\n");
		text_align_center(HOR, "4. 개발자 모드\n\n");
		text_align_center(HOR, "5. 졸업기록 열람\n\n");
		gotoxy(HOR/2, 30);
		scanf("%d", &player_select_1);

		// 플레이어 메뉴 선택 입력 잘못되었을때 다시 받는 부분
		while (player_select_1 < 1 || player_select_1 > 5) {
			system("cls");	// clear screen후 문자출력해야지 안그러면 다 지워진 후에 출력함.
			text_align_center(HOR, "\n\n다시 입력해주세요.");
			
			text_align_center(HOR, "1. 게임설명\n\n");
			text_align_center(HOR, "2. 난이도 선택\n\n");
			text_align_center(HOR, "3. 캐릭터 선택\n\n");
			text_align_center(HOR, "4. 개발자 모드\n\n");
			text_align_center(HOR, "5. 졸업기록 열람\n\n\n");

			gotoxy(HOR/2, 21);
			scanf("%d", &player_select_1);


		}

		// 메뉴 선택별 케이스.
		switch (player_select_1) {
		case 1:	// 게임 설명
			text_align_center(HOR, "게임 설명\n");	// 이름 오류 수정
			//게임 설명 추가 요망
			text_align_center(HOR, "\n\n뒤로 가기 - ESC");
			player_select_2 = _getch();
			while (player_select_2 != 27) {
				player_select_2 = _getch();
			}
			break;
		case 2:	// 난이도 선택
			do {
				system("cls");
				gotoxy(0, 10);	// y좌표 이동시 사용
				text_align_center(HOR, "난이도를 선택해주세요 (1 - 초급, 2 - 중급, 3 - 고급) : \n");
				gotoxy(HOR / 2, 12);
				scanf(" %d", &level);


				switch (level) {
				case 1:
					text_align_center(HOR, "[ 초급 ] 난이도를 선택하셨습니다.\n");
					break;
				case 2:
					text_align_center(HOR, "[ 중급 ] 난이도를 선택하셨습니다.");
					break;
				case 3:
					text_align_center(HOR, "[ 고급 ] 난이도를 선택하셨습니다.");
					break;
				default:
					text_align_center(HOR, "잘못 입력하셨습니다.");
					text_align_center(HOR, "다시 입력해주세요 : ");
					scanf(" %d", &level);

				}
				text_align_center(HOR, "계속 진행하시겠습니까? (y - 게임시작 / n - 메뉴로 돌아가기/ r - 레벨 다시 고르기)\n");
				ch = _getch();
			} while (ch == 'r');
			if (ch == 'n') {
				system("cls");
				continue;
			}
		case 3:

		case 4:

		case 5:

			// 오류나서 일단 default문 추가
		default:
			break;
		}


		// 게임 실행 부분, 실행하려면 나머지부분 주석처리하고 실행
		
		if(player_select_1 == 2 && ch == 'y') {	// 난이도 선택 이후에만 게임 실행
			flag(level);
			system("cls");
			printMap();
			tm1 = time(NULL); // 시작 시간 체크 - 이후에 게임 끝날 때  tm2 = time(NULL) 추가해야함.
			while (game_start) {
				gotoxy(x, y);
				printf("▷\b\b");			// 주인공 문자 출력 부분
				ch = _getch();
				printf("  \b\b");			// 이동 시 주인공 문자 지우는 부분
				if (ch == 224) {		// 방향키 이동 부분
					ch = _getch();
					switch (ch) {
					case 72:
						ty = y - 1;
						break;
					case 80:
						ty = y + 1;
						break;
					case 75:
						tx = x - 2;
						break;
					case 77:
						tx = x + 2;
						break;
					}
					switch(detection(tx, ty, ch)){
						// 빈 칸
						case 0:
							x = tx;
							y = ty;
							break;
						// 장애물
						case 2:
							break;
						// 교수
						case 3:

							break;
						// 깃발
						case 4:
							break;
						// 보물
						case 5:
							game_start = 0;
							break;
					}
				}
			}
			// 게임 종료시 부분(whlie문 끝)
		}
		
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
