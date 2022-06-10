//main 함수
#include "header.h"
#define CHAR_LENGTH 1000
#define BOX_HALF_12 12
#define BOX_HALF_36 36

// 내부정의 함수
void text_align_center(int columns, char* text);
void gotoxy(int x, int y);
void loading(int);
void menu(int);

// 외부정의 함수
extern void printMap();							// 맵 출력하는 함수
extern void flag(int level);					// 맵에 랜덤으로 깃발, 장애물 등을 배치하는 함수. 난이도 받아서 장애물 개수 등 설정.
extern int move(int*, int*, int);				// x, y, ch 인자를 전달, 사용자의 위치를 움직임. detection 사용됨.
extern int detection(int, int, int);			// x, y, ch 인자를 전달, 사용자의 다음 움직임이 어디로 움직일지를 판단.
extern void printSquare(int, int, int, int);	// x1, y1, x2, y2 인자를 전달, 두 점으로 그린 사각형을 출력해줌.
extern void printBlank(int, int, int, int);		// x1, y1, x2, y2 인자를 전달, 두 점으로 그린 사각형 내의 공간을 모두 지워줌.
extern void rank(int rank[], char player_name[]);

// 미니게임
extern int up_and_down_main();		// 미니게임 1
extern int rock_scissors_paper();	// 미니게임 2
extern void print_point();			// 미니게임 2 결과 출력 함수
extern int jumping_man_main();		// 미니게임 3

// 전역변수
int map[50][50] = { 0 };			// 장애물, 교수, 깃발 등 위치정보 저장하는 배열, 일단 전부 0으로 초기화
const int HOR = 190;
const int size = 50;				// 맵 크기 설정해주는 상수
const int max_x = 100;				// 플레이어 x, y 이동 범위 최대, 최소값
const int min_x = 2;
const int max_y = 51;
const int min_y = 3;
const int first_line = 13;			// 화면 안내문 출력하는 첫째줄
const int p_x_speed = 2;			// 사용자 x속도, y속도
const int p_y_speed = 1;
time_t tm1, tm2; 					// 게임 시간 받는 변수	
int level = 1;					// 난이도 - 1 (초급), 2 (중급), 3 (고급)
int player_select_1, player_select_2;	// 각각 menu 선택이랑 게임 설명 부분 담당.
int player_shape = 0; 			// 사용자 모양 바꿔주는 변수
int professor_location[20][2] = { 0 };	// 교수님 위치 저장하는 배열, 인원 크기보다 적을 시 나머지 공간엔 0 할당. 10 / 15 / 20명.
int ranking[4] = { 0 }; // ranking[0] = 학사 취득 학기 저장, ranking[1] = 석사 취득 학기 저장, ranking[2] = 박사 취득 학기 저장
char player_name[CHAR_LENGTH];		// { 0 }으로 저장하면 크기 1됨. -> 일단 크기만 설정.

// 0519 - 한성준, gotoxy와 맵출력, 플레이어 움직이게 하는 부분 등 추가.
int main(void) {
	int *p;							// 임시 포인터 변수
	int x = 40, y = 12;				// 플레이어 위치 저장하는 변수
	int game_start = 1;				// 메뉴부터 시작해서 전체 while문 반복 조절하는 변수
	int main_game_running = 1;		// 게임 끝났는지 확인해주는 변수
	int minigame_result=0;			// 미니게임 결과 반환값 저장해주는 변수
	int player_select_1 = 0; 		// **중요 메뉴, 게임시작, 미니게임 시작 등 while문 안에서 상태 저장하는 변수
	int player_select_2 = 0;		// 게임 설명 부분 사용자 선택.
	int ch = -1;	// 사용자 움직임, 입력 주로 받는 변수
	char letter;
	char text[CHAR_LENGTH];		// 문장 출력할때 임시저장하는 변수
	
	
	//cols 가로길이 lines 세로길이  값 넣어줘야함 -> 190 * 60으로 일단 설정
	// 변수 안들어감. 숫자로 직접 넣기.
	system("mode con cols=190 lines=60");	// cols= 190하면 오류남. 꼭 등호 뒤에 붙여서 하기.


	menu(1);	// GAME START 출력 부분
	
	do{
		letter = _getch();
	}
	while (letter == '\n');

	gotoxy(0, 20);
	text_align_center(HOR, "[ 다소 민감한 내용이 포함되어 있으니 학부생 및 대학원생은 플레이에 조심하세요. ]\n");
	loading(25);	// 이전 부분은 loading함수 안에 주석처리
	

	// 플레이어 이름 입력부분
	system("cls");
	gotoxy(0, 7);	// text_align_center 함수 쓸거면 x = 0 이어야함.
	text_align_center(HOR, "플레이어의 이름을");
	printf("\n");
	text_align_center(HOR, "입력하세요.");
	printSquare(HOR/2-BOX_HALF_36, 5, HOR/2+BOX_HALF_36, 11);
	
	// player name 입력하는 부분
	printSquare(HOR/2-BOX_HALF_36, 13, HOR/2+BOX_HALF_36, 15);
	gotoxy(HOR/2-BOX_HALF_36+2, 14);
	scanf("%s", player_name);


	// 메뉴 시작
	while (game_start) {
		// 메뉴 및 ** 출력하는 화면 결정하는 부분 - 0610 수정
		switch (player_select_1) {
			// 게임 끝나고 다음 난이도로 넘어가야 해서 menu부분에 if문 걸어줌 -> switch 문 안으로 이돋ㅇ
			case 0:
			system("cls");
			menu(3);	// 처음 메뉴 선택 부분
			gotoxy(HOR/2, 30);
			scanf("%d", &player_select_1);

			// 플레이어 메뉴 선택 입력 잘못되었을때 다시 받는 부분 -> ** 1~6 이외의 값은 입력 못하게 막음
			while (player_select_1 < 1 || player_select_1 > 6) {
				system("cls");	// clear screen후 문자출력해야지 안그러면 다 지워진 후에 출력함.
				gotoxy(0, 0);
				text_align_center(HOR, "\n\n다시 입력해주세요.");
				menu(3);	// 메뉴 출력
				scanf("%d", &player_select_1);
			}
			break;
		case 1:	// 게임 설명
			menu(4);				// menu case 4에 가서 게임 설명 추가할 것.
			player_select_2 = _getch();
			while (player_select_2 != 27) {
				player_select_2 = _getch();
			}
			player_select_1 = 0;
			break;
		case 2:	// 난이도 선택
			if(level != 1){
				player_select_1 = 7;	// 이어하기로 보냄
			}
			else{
				do {
					system("cls");
					gotoxy(0, 10);	// y좌표 이동시 사용
					text_align_center(HOR, "난이도를 선택해주세요 (1 - 초급, 2 - 중급, 3 - 고급) : \n");
					gotoxy(HOR / 2, 12);
					scanf(" %d", &level);

					while(level != 1 && level != 2 && level != 3){
						text_align_center(HOR, "잘못 입력하셨습니다.");
						text_align_center(HOR, "다시 입력해주세요 : ");
						scanf(" %d", &level);
					}
					menu(level + 4);
					text_align_center(HOR, "계속 진행하시겠습니까? (y - 게임시작 / n - 메뉴로 돌아가기/ r - 레벨 다시 고르기)\n");
					ch = _getch();
				} while (ch == 'r');

				if (ch == 'n') {
					player_select_1 = 0;	// 메뉴 복귀
					level = 1;
					system("cls");
					break;
				}
			}
			break;
		case 3:	// 플레이어 선택
			do{
				// 플레이어 선택 메뉴 출력
				system("cls");
				gotoxy(0, 4);
				text_align_center(HOR, "마음에 드는 모양을 선택하세요 (0~ 5 입력)");

				gotoxy(0, 7);
				menu(14);	// 모양 출력
				// 박스 출력
				printSquare(HOR/2-BOX_HALF_36, 2, HOR/2+BOX_HALF_36, 20);
				
				// 잘못 입력시 경고문구 출력부분
				gotoxy(HOR/2, 18);
				scanf("%d", &player_shape);
				while(player_shape < 0 || player_shape > 5){
					printf("\b\b\b   ");
					gotoxy(0, 30);
					text_align_center(HOR, "잘못 입력하셨습니다.");
					text_align_center(HOR, "다시 입력해주세요 : ");
					
					gotoxy(HOR/2, 18);
					scanf(" %d", &player_shape);
				}
				// 경고문구 삭제 및 선택 모양 알림 문구 출력
				printBlank(0, 30, 180, 30);
				printBlank(0, 31, 180, 31);
				gotoxy(0, 23);
				text_align_center(HOR, "선택한 모양은 다음과 같습니다.");
				
				// 선택 모양 출력 부분
				if(player_shape >= 0 || player_shape < 7)
					menu(player_shape + 15);
				// 메뉴 종료 알림문구 출력부분
				gotoxy(0, 27);
				text_align_center(HOR, "계속 진행하시겠습니까? (끝내려면 아무 키나 눌러주세요 / r - 모양 다시 고르기)\n");
				ch = _getch();
			}while(ch == 'r');
			player_select_1 = 0;
			break;
		case 4:	// 개발자 모드 - 본 게임 완성 전까지 보류
			
			player_select_1 = 0;
			break;
		case 5:	// 졸업기록 열람 - 0609 구현 완료 - 실행되는지 확인요망
			rank(ranking, player_name);
			player_select_2 = _getch();
			while (player_select_2 != 27) {
				player_select_2 = _getch();
			}
			player_select_1 = 0;
			break;
		case 6:	// 게임 종료
			game_start = 0;
			system("cls");
			gotoxy(0, 5);
			menu(2);
			break;

		case 7:
			// 다음 난이도 시작
			player_select_1 = 2;
			ch = 'y';
			break;
		default:
			printText("ERROR : player_select_1\n", 0, 0);
			printf("player_select_1 : %d\n", player_select_1);
			break;
		}

		
		// main 게임 실행 부분
		if(player_select_1 == 2 && ch == 'y') {	// 난이도 선택 + 플레이어 선택값 y일때만 실행
			// 게임 시작 전 한번만 실행
			system("cls");
			loading(25);

			flag(level);
			printMap();
			tm1 = time(NULL); // 시작 시간 체크 - 이후에 게임 끝날 때  tm2 = time(NULL) 추가해야함. -> 완료
			while (main_game_running) {
				// 주인공 문자 출력 부분
				gotoxy(x, y);
				if(player_shape >= 0 || player_shape < 7)
					menu(player_shape + 8);	
				else
					printText("ERROR : PLAYER_SHAPE\n", 0, 0);
				
				// 좌표 출력
				sprintf(text, "좌표 : %d, %d ", x/2, y);
				gotoxy(107, 14);
				printf("%s", text);
				//printText("좌표 : ", 107, 14);

				// 다음 문자 부분
				ch = _getch();
				gotoxy(x, y);
				printf("  \b\b");			// 이동 시 주인공 문자 지우는 부분
				main_game_running = move(&x, &y, ch);	// x, y, ch 받아 사용자 위치 움직이는 부분
			}
		}
		// 메인게임 종료 및 미니게임 시작
		if (main_game_running == 0){
			// 게임 종료시 부분(whlie문 끝) + 0609 난이도 별로 시간에 따른 학기 수 & 일정 시간을 넘기면 학위 취득 실패 출력 후 메인메뉴로 돌아가야 함.
			tm2 = time(NULL);
			system("cls");
			for(int i = 0; i < size; i++){
				for(int j = 0; j < size; j++){
					map[i][j] = 0;
				}
			}
			printText("SYSTEM | map 초기화 완료", 0, 0);
			// p = &map[0][0];
			// while ((int)(&map[size-1][size-1] - p) < size * size){
			// 	*p = 0;
			// 	p++;
			// }
			// 미니게임 시작멘트
			menu(21);
			loading(25);
			system("cls");
			// TODO - 미니게임 점수계산부분 추가
			if (level == 1){
				// 초급 - 업다운
				minigame_result = up_and_down_main();

			}
			else if(level == 2){
				// 중급 - 가위바위보
				// minigame_result = 
				minigame_result = rock_scissors_paper();
				print_point(minigame_result);
			}	
			else if(level == 3){
				// 고급 - 공룡
				minigame_result = jumping_man_main();
			}
			
			// 점수 현황 출력 및 다음 게임 난이도 선택 부분
			system("cls");
			menu(22);
			level++;
			ch = _getch();
			if(ch == 'n'){
				// 메뉴로 이동
				player_select_1 = 0;
			}
			else{
				// 다음 게임 바로 시작
				system("cls");
				loading(25);
				player_select_1 = 7;
			}
			// 다시 main_game_running 초기화해줌
			main_game_running = 1;
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
	return;
}

void gotoxy(int x, int y) {
	COORD Cur = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Cur);
	return;
}

void loading(int line){
	for (int i = 0; i < 11; i++) {
		gotoxy(0, line);
		text_align_center(HOR, "            ");
		gotoxy(0, line+2);
		text_align_center(HOR, "                    ");
		//printBlank(HOR-5, line, HOR+5, line);
		//printBlank(HOR-10, line+2, HOR+10, line+2);

		gotoxy(0, line);
		text_align_center(HOR, "Loading");
		gotoxy(HOR/2+4, line);
		printf("...");

		gotoxy(0, line+2);
		switch(i){
			case 0:
			text_align_center(HOR, "□□□□□□□□□□");
			break;
			case 1:
			text_align_center(HOR, "■□□□□□□□□□");
			break;
			case 2:
			text_align_center(HOR, "■■□□□□□□□□");
			break;
			case 3:
			text_align_center(HOR, "■■■□□□□□□□");
			break;
			case 4:
			text_align_center(HOR, "■■■■□□□□□□");
			break;
			case 5:
			text_align_center(HOR, "■■■■■□□□□□");
			break;
			case 6:
			text_align_center(HOR, "■■■■■■□□□□");
			break;
			case 7:
			text_align_center(HOR, "■■■■■■■□□□");
			break;
			case 8:
			text_align_center(HOR, "■■■■■■■■□□");
			break;
			case 9:
			text_align_center(HOR, "■■■■■■■■■□");
			break;
			case 10:
			text_align_center(HOR, "■■■■■■■■■■");
			break;
		}
		Sleep(70);		
	}
	// for (int i = 0; i < 3; i++) {
	// 	gotoxy(0, 25);
	// 	text_align_center(HOR, "                    ");	// 이전 글자 지워주는 부분
	// 	gotoxy(0, 25);
	// 	text_align_center(HOR, "starting in");
	// 	gotoxy(HOR / 2 + 12 / 2, 25);	// starting in 글자길이 대충 12로 계산.
	// 	printf("%d...", 3 - i);
	// 	Sleep(1 * 1000);
	// }
	return;
}

// 그냥 메뉴 출력해주는 것들 모아놓은 함수, 안에 system("cls") 넣지 말기 (헷갈림)
void menu(int n){
	switch(n){
		case 1:
			//GAME START 혹은 게임이름으로 변경 필요...0530 완료
			gotoxy(0, 10);
			text_align_center(HOR, " #####      ##    ##   ##  #######                #####   ########    ##      ######  ########");
			text_align_center(HOR, "##   ##    ####   ### ###   ##  ##               ##   ##  #  ##  #   ####     ##  ##  #  ##  #");
			text_align_center(HOR, "##        ##  ##  #######   ##                   ##          ##     ##  ##    ##  ##     ##   ");
			text_align_center(HOR, "##        ######  ## # ##   ####                 #######     ##     ######    #####      ##   ");
			text_align_center(HOR, "##  ###   ##  ##  ##   ##   ##                        ##     ##     ##  ##    ####       ##   ");
			text_align_center(HOR, "##   ##   ##  ##  ##   ##   ##  ##               ##   ##     ##     ##  ##    ## ##      ##   ");
			text_align_center(HOR, " #####    ##  ##  ##   ##  #######                #####     ####    ##  ##    ###  ##   ####  ");
			break;
		case 2:
			text_align_center(HOR, " #####      ##    ##   ##  #######                #####    ##  ##  #######   ###### ");
			text_align_center(HOR, "##   ##    ####   ### ###   ##  ##               ##   ##   ##  ##   ##  ##   ##  ## ");
			text_align_center(HOR, "##        ##  ##  #######   ##                   ##   ##   ##  ##   ##       ##  ## ");
			text_align_center(HOR, "##        ######  ## # ##   ####                 ##   ##   ##  ##   ####     #####  ");
			text_align_center(HOR, "##  ###   ##  ##  ##   ##   ##                   ##   ##   ##  ##   ##       ####   ");
			text_align_center(HOR, "##   ##   ##  ##  ##   ##   ##  ##               ##   ##    ####    ##  ##   ## ##  ");
			text_align_center(HOR, " #####    ##  ##  ##   ##  #######                #####      ##    #######   ###  ##");
			break;
		case 3:
			gotoxy(0, 12);
			text_align_center(HOR, "1. 게임설명");
			gotoxy(0, 16);
			if(level == 1)
				text_align_center(HOR, "2. 난이도 선택");
			else
				text_align_center(HOR, "2. 이어 하기");
			gotoxy(0, 20);
			text_align_center(HOR, "3. 캐릭터 선택");
			gotoxy(0, 24);
			text_align_center(HOR, "4. 개발자 모드");
			gotoxy(0, 28);
			text_align_center(HOR, "5. 졸업기록 열람");
			gotoxy(0, 32);
			text_align_center(HOR, "6. 게임 종료");
			printSquare(HOR/2-15, 10, HOR/2+15, 35);
			
			break;
		case 4:
			// player_select_1 -> case 1 게임 설명 부분
			system("cls");
			text_align_center(HOR, "게임 설명\n\n");	// 이름 오류 수정
			// 0609 게임 설명 추가 완료  + 한글자씩 출력되도록 변경 가능 but, 복잡해짐.
			
			text_align_center(HOR, "\n\n 아주 오래전 한 대학생이 살고 있었다..... \n");
			text_align_center(HOR, "그 학생은 박사 학위를 취득해 교수가 되고자 하는 원대한 꿈을 지니고 있었다.\n");
			text_align_center(HOR, "학사, 석사, 박사를 거쳐 교수가 되기 위해서는 졸업논문을 작성해야 한다...\n");
			text_align_center(HOR, "하지만 졸업논문을 작성할 때마다 뜻밖의 위기가 찾아오는데...\n");
			text_align_center(HOR, "위기를 극복하고 무사히 박사 학위를 취득하도록 도와주자!\n");
			text_align_center(HOR, "\n\n뒤로 가기 - ESC");
			break;
		case 5:
			// case 2 -> 난이도 선택 부분
			// level == 1
			text_align_center(HOR, "[ 초급 ] 난이도를 선택하셨습니다.\n");
			break;
		case 6:
			// level == 2
			text_align_center(HOR, "[ 중급 ] 난이도를 선택하셨습니다.\n");
			break;
		case 7:
			// level == 3
			text_align_center(HOR, "[ 고급 ] 난이도를 선택하셨습니다.\n");
			break;
		case 8:
			// 주인공 문자 출력 부분
			printf("◈\b\b");			
			break;
		case 9:
			printf("◇\b\b");
			break;
		case 10:
			printf("◆\b\b");
			break;
		case 11:
			printf("엄\b\b");
			break;
		case 12:
			printf("준\b\b");
			break;
		case 13:
			printf("식\b\b");
			break;
		case 14:
			// 메뉴 - 3 : 플레이어 모양 선택 부분
			text_align_center(HOR, "0 - ◈");
			text_align_center(HOR, "1 - ◇");
			text_align_center(HOR, "2 - ◆");
			text_align_center(HOR, "3 - 엄");
			text_align_center(HOR, "4 - 준");
			text_align_center(HOR, "5 - 식");
			break;
		case 15:
			// 메뉴 - 3 플레이어 모양 선택 확인 부분
			printText("◈", HOR/2, 25);
			break;
		case 16:
			printText("◇", HOR/2, 25);
			break;
		case 17:
			printText("◆", HOR/2, 25);
			break;
		case 18:
			printText("엄", HOR/2, 25);
			break;
		case 19:
			printText("준", HOR/2, 25);
			break;
		case 20:
			printText("식", HOR/2, 25);
			break;
		case 21:
			// 메인 게임 종료시 미니게임 시작멘트
			
			gotoxy(0, 15);
			text_align_center(HOR, "미니게임을 시작합니다.");
			Sleep(100);
			text_align_center(HOR, "이곳에서 승리한다면 바로 다음 단계로 넘어갈 수 있지만, ");
			Sleep(100);
			text_align_center(HOR, "그러지 못한다면 추가 학점을 이수해야 합니다.");
			Sleep(100);
			gotoxy(0, 20);
			text_align_center(HOR, "Good Luck");
			
			Sleep(1000);
			// Sleep(200);-> sleep 뒤에 gotoxy 있으면 오류나는듯.
			// 대기시간
			//loading(25);
			// for(int i = 0; i < 3; i++){
			// 	printBlank(0, 25, 180, 25);
			// 	gotoxy(0, 25);
			// 	text_align_center(HOR, "Starting in ");
			// 	printf("%d...", 3-i);
			// 	Sleep(1000);
			// }
			break;
		case 22:
			// 미니게임 종료시 다음 난이도 넘어가는 부분 -> 점수현황 보여주고 넘어가야 함.
			rank(ranking, player_name);
			gotoxy(0, 15);
			text_align_center(HOR, "다음 난이도로 넘어가시겠습니까? (예 - 아무 키나 누르세요 / 메뉴(난이도는 저장됩니다) - n)");
			break;
		default:
			printText("ERROR : MENU FUNCTION\n", 0, 0);
			break;
	}
	return;
}