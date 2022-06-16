//main 함수
// Copyright 2022. 송현준, 한성준, 차민우, 조성호, 정하린 all rights reserved.
#include "header.h"
#define CHAR_LENGTH 1000
#define BOX_HALF_12 12
#define BOX_HALF_36 36

// 내부정의 함수
void text_align_center(int columns, char* text);
void gotoxy(int x, int y);
void loading(int);
void menu(int);
void event_check();
void printText_mid(char *text, int y);

// 멀티쓰레드 함수
int WINAPI user_input(LPVOID param);

// 외부정의 함수, 변수
extern int treasure_x, treasure_y;

extern void printMap();							// 맵 출력하는 함수
extern void flag(int level);					// 맵에 랜덤으로 깃발, 장애물 등을 배치하는 함수. 난이도 받아서 장애물 개수 등 설정.
extern int move(int*, int*, int);				// x, y, ch 인자를 전달, 사용자의 위치를 움직임. detection 사용됨.
extern int detection(int, int, int);			// x, y, ch 인자를 전달, 사용자의 다음 움직임이 어디로 움직일지를 판단.
extern void printSquare(int, int, int, int);	// x1, y1, x2, y2 인자를 전달, 두 점으로 그린 사각형을 출력해줌.
extern void printBlank(int, int, int, int);		// x1, y1, x2, y2 인자를 전달, 두 점으로 그린 사각형 내의 공간을 모두 지워줌.
extern void rank(int rank[], char player_name[]);
extern void printText(char *, int, int);

// 미니게임
extern int up_and_down_main();		// 미니게임 1
extern int rock_scissors_paper();	// 미니게임 2
extern void print_point();			// 미니게임 2 결과 출력 함수
extern int jumping_man_main();		// 미니게임 3

// 전역변수
int map[50][50] = { 0 };			// 장애물, 교수, 깃발 등 위치정보 저장하는 배열, 일단 전부 0으로 초기화
int p_x_speed = 2;			// 사용자 x속도, y속도
int p_y_speed = 1;
const int HOR = 190;
const int size = 50;				// 맵 크기 설정해주는 상수
const int max_x = 100;				// 플레이어 x, y 이동 범위 최대, 최소값
const int min_x = 2;
const int max_y = 51;
const int min_y = 3;
const int first_line = 13;			// 화면 안내문 출력하는 첫째줄
int line = 24;

const int test_mode = 0;

time_t tm1, tm2; 					// 게임 시간 받는 변수
int time_limit[3] = {40, 50, 60};
int level = 1;						// 난이도 - 1 (초급), 2 (중급), 3 (고급)
int ch = -1;	// 사용자 움직임, 입력 주로 받는 변수
int user = -1;
int user_movable = 0;	// 사용자 움직임 제어하는 변수
const int event_length = 10;
int event_endtime[10] = {0, };
int player_select_1 = 0, player_select_2 = 0;	// 각각 menu 선택이랑 게임 설명 부분 담당.
int player_shape = 0; 				// 사용자 모양 바꿔주는 변수, 0~5
int professor_location[20][2] = { 0 };	// 교수님 위치 저장하는 배열, 인원 크기보다 적을 시 나머지 공간엔 0 할당. 10 / 15 / 20명.
int ranking[6] = { 0 }; 			// ranking[0] = 학사 취득 학기 저장, ranking[1] = 석사 취득 학기 저장, ranking[2] = 박사 취득 학기 저장, 
// ranking[3] => 학사 초과학기, 4는 석사초과, 5는 박사 초과학위
int main_game_running = 0;		// 게임 끝났는지 확인해주는 변수
char player_name[CHAR_LENGTH];		// { 0 }으로 저장하면 크기 1됨. -> 일단 크기만 설정.

// 0519 - 한성준, gotoxy와 맵출력, 플레이어 움직이게 하는 부분 등 추가.
int main(void) {
	int *p;							// 임시 포인터 변수
	int age = 0;
	int x = 40, y = 12;				// 플레이어 위치 저장하는 변수
	int game_start = 1;				// 메뉴부터 시작해서 전체 while문 반복 조절하는 변수
	int minigame_result=0;			// 미니게임 결과 반환값 저장해주는 변수
	int semester_limit = 10;
	// int player_select_1 = 0; 		// **중요 메뉴, 게임시작, 미니게임 시작 등 while문 안에서 상태 저장하는 변수
	// int player_select_2 = 0;		// 게임 설명 부분 사용자 선택.
	char letter;					// ch -> int형, letter -> char형 입력 처리
	char text[CHAR_LENGTH];		// 문장 출력할때 임시저장하는 변수
	
	// 테스트 모드 기능 -> 
	// 제한시간 줄이고 
	// 초과학기시 1학기 초과만으로도 탈락 가능하게 함.
	// 인트로 없앰 
	if(test_mode){
		for(int i = 0; i < 3; i++){
			time_limit[i] = i+4;
		}
		semester_limit = 1;
	}

	// 멀티쓰레드 부분
	int threadId1;
	int param = 0;
	HANDLE threadHandle1;
	threadHandle1 = CreateThread(NULL, 0, user_input, &param, 0, &threadId1);
	
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
	do{
		gotoxy(0, 7);	// text_align_center 함수 쓸거면 x = 0 이어야함.
		text_align_center(HOR, "플레이어의 이름을");
		printf("\n");
		text_align_center(HOR, "입력하세요.");
		printSquare(HOR/2-BOX_HALF_36, 5, HOR/2+BOX_HALF_36, 11);
		
		// player name 입력하는 부분
		printSquare(HOR/2-BOX_HALF_36, 13, HOR/2+BOX_HALF_36, 15);
		gotoxy(HOR/2-BOX_HALF_36+2, 14);
		scanf("%s", player_name);
		system("cls");
		if(!strcmp(player_name, "엄준식")){
			gotoxy(0, 17);
			text_align_center(HOR, "플레이어의 이름은 \"엄준식\" 일 수 없습니다.");
		}
	}
	while(!strcmp(player_name, "엄준식"));
	if(!test_mode){
		// 게임 인트로 부분
		system("cls");
		printSquare(HOR/2-70, 10, HOR/2+70, 35);

		gotoxy((HOR - strlen("<게임 스토리>")) / 2, 12);
		printf("<게임 스토리>");
		

		gotoxy((HOR - strlen("COVID-19가 슬슬 끝나갈 때쯤 \"진짜\"인줄 알았던 대학 생활을 즐기며 평화로운 나날을 보내고 있었는데...이때까지만 해도 몰랐다.")) / 2, 15);
		printf("COVID-19가 슬슬 끝나갈 때쯤 \"진짜\"인줄 알았던 대학 생활을 즐기며 평화로운 나날을 보내고 있었는데...이때까지만 해도 몰랐다.");
		Sleep(1000);
		
		gotoxy((HOR - strlen("지겨운 술 냄새와, 완화상평의 혜택이 무너지고, 슬슬 취업이 우리에게 다가오고 있다는 것을...!")) / 2, 17);
		printf("지겨운 술 냄새와, 완화상평의 혜택이 무너지고, 슬슬 취업이 우리에게 다가오고 있다는 것을...!");
		Sleep(1000);
		
		gotoxy((HOR - strlen("과연 우리는 졸업을 무사히 8학기만으로 끝낼 수 있을까?")) / 2, 19);
		printf("과연 우리는 졸업을 무사히 8학기만으로 끝낼 수 있을까?");
		Sleep(1000);
		
		gotoxy((HOR - strlen("그리고, 너무 무리한 나머지 교수님의 눈에 들어와버린 나...!")) / 2, 21);
		printf("그리고, 너무 무리한 나머지 교수님의 눈에 들어와버린 나...!");
		Sleep(1000);
		
		gotoxy((HOR - strlen("어쩔 수 없이 교수님의 설득에 대학원에 진학하게 되는데...")) / 2, 23);
		printf("어쩔 수 없이 교수님의 설득에 대학원에 진학하게 되는데...");
		Sleep(1000);
		
		gotoxy((HOR - strlen("대학원도 과연 무사히 졸업할 수 있을까?")) / 2, 25);
		printf("대학원도 과연 무사히 졸업할 수 있을까?");
		Sleep(1000);
		
		gotoxy((HOR - strlen("미처 알지 못했던 진짜 \"캠퍼스 라이프\"가 지금부터 시작됩니다! ")) / 2, 27);
		printf("미처 알지 못했던 진짜 \"캠퍼스 라이프\"가 지금부터 시작됩니다!");
		Sleep(1000);
		
		gotoxy((HOR - strlen("< press Enter to Start Game >")) / 2, 30);
		printf("< press Enter to Start Game >");
		
		gotoxy(HOR/2, 33);
		ch = _getch();
	}
	// 메뉴 시작
	while (game_start) {
		// 메뉴 및 ** 출력하는 화면 결정하는 부분 - 0610 수정
		switch (player_select_1) {
			// 게임 끝나고 다음 난이도로 넘어가야 해서 menu부분에 if문 걸어줌 -> switch 문 안으로 이돋ㅇ
			case 0:
			system("cls");
			menu(3);	// 처음 메뉴 선택 부분
			gotoxy(HOR/2, 30);
			scanf(" %d", &player_select_1);

			// 플레이어 메뉴 선택 입력 잘못되었을때 다시 받는 부분 -> ** 1~6 이외의 값은 입력 못하게 막음
			while (player_select_1 < 1 || player_select_1 > 6) {
				system("cls");	// clear screen후 문자출력해야지 안그러면 다 지워진 후에 출력함.
				gotoxy(0, 0);
				text_align_center(HOR, "\n\n다시 입력해주세요.");
				menu(3);	// 메뉴 출력
				scanf(" %d", &player_select_1);
			}
			break;
		case 1:	// 게임 설명
			menu(4);				// menu case 4에 가서 게임 설명 추가할 것.
			player_select_2 = _getch();
			while (player_select_2 != 27) {
				player_select_2 = _getch();
			}
			player_select_1 = 0;	// 다시 메뉴로
			break;
		case 2:	// 난이도 선택
			if(level != 1){
				player_select_1 = 7;	// 이어하기로 보냄
			}
			else{
				do {
					system("cls");
					gotoxy(0, 10);	// y좌표 이동시 사용
					//Sleep(1000);
					text_align_center(HOR, "난이도를 선택해주세요 (1 - 초급, 2 - 중급, 3 - 고급) : \n");
					gotoxy(HOR / 2, 12);
					scanf(" %d", &level);
					
					while(level != 1 && level != 2 && level != 3){
						text_align_center(HOR, "잘못 입력하셨습니다.");
						text_align_center(HOR, "다시 입력해주세요 : ");
						gotoxy(HOR / 2, 16);
						scanf(" %d", &level);
					}
					menu(level + 4);
					
					text_align_center(HOR, "계속 진행하시겠습니까? (y - 게임시작 / n - 메뉴로 돌아가기 / r - 레벨 다시 고르기)\n");
					gotoxy(HOR/2, 20);
					scanf(" %c", &letter);
					while(letter != 'y' && letter != 'n' && letter != 'r'){
						text_align_center(HOR, "잘못 입력하셨습니다.");
						text_align_center(HOR, "다시 입력해주세요 : ");
						scanf(" %c", &letter);
					}
					//ch = _getch();
				} while (letter == 'r');

				if (letter == 'n') {
					player_select_1 = 0;	// 메뉴 복귀
					level = 1;
					system("cls");
					break;
				}
				// main 게임 들어가기 전 ranking 초기화...필요?

				//else if(ch == 'y')
					//main_game_running = 1;
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
		// case 4:	// 개발자 모드 - 본 게임 완성 전까지 보류
			
		// 	player_select_1 = 0;
		// 	break;
		case 4:	// 졸업기록 열람 - case 5였는데 개발자 모드 없애면서 4로 올려줌.
			system("cls");
			rank(ranking, player_name);
			player_select_2 = _getch();
			while (player_select_2 != 27) {
				player_select_2 = _getch();
			}
			player_select_1 = 0;
			break;
		case 5:	// 게임 종료
			game_start = 0;
			system("cls");
			gotoxy(0, 5);
			menu(2);
			break;

		case 7:
			// 다음 난이도 시작
			player_select_1 = 2;
			ch = 'y';
			//main_game_running = 1;
			break;
		case 8:
			system("cls");
			gotoxy(0, 15);
			menu(2);
			// 시간초과 -> 학위 취득 실패 메세지
			printText_mid("논문을 완성했지만 시간초과로 학위 취득에 실패하셨습니다...", 28);
			printText_mid("Enter - 다시 시작하기", 30);
			ch = _getch();
			// 초기화
			player_select_1 = 0;
			letter = 'a';
			// level = 1;
			for(int i = 0; i < 6; i++)
				ranking[i] = 0;
			
			break;
		default:
			printText("ERROR : player_select_1\n", 0, 0);
			printf("player_select_1 : %d\n", player_select_1);
			break;
		}
		
		// main 게임 실행 부분
		if(player_select_1 == 2 && letter == 'y') {	// 난이도 선택 + 플레이어 선택값 y일때만 실행
			// 게임 시작 전 한번만 실행
			system("cls");
			loading(25);

			flag(level);
			printMap();
			tm1 = time(NULL); // 시작 시간 체크 - 이후에 게임 끝날 때  tm2 = time(NULL) 추가해야함. -> 완료
			
			main_game_running = 1;
			while (main_game_running) {
				// 주인공 문자 출력 부분 -> x, y는 출력기준 좌표
				gotoxy(x, y);
				if(player_shape >= 0 || player_shape < 7)
					menu(player_shape + 8);	
				else
					printText("ERROR : PLAYER_SHAPE\n", 0, 0);
				
				// 좌표 출력
				sprintf(text, "좌표 : %d, %d ", x/2, y);
				gotoxy(129, 4);
				printf("%s", text);
				
				// event_endtime 출력 -> 나중에 주석처리, 디버깅용
				// gotoxy(1, 2);
				// for(int i = 0; i < event_length; i++)
				// 	printf("%d : %d, ", i, event_endtime[i]);

				// 남은 시간 및 초과 시간 출력
				gotoxy(166, 4);
				
				if(time(NULL) - tm1 <= time_limit[level-1]){
					printf("남은 시간 : ");
					printf("%3d", time_limit[level-1] - (time(NULL) - tm1));
				}
				else{
					printf("초과 시간 : ");
					printf("%3d", (time(NULL) - tm1) - time_limit[level-1]);
				}	

				// 다음 방향 이동 부분
				if(user_movable){
					gotoxy(x, y);
					printf("  \b\b");			// 이동 시 주인공 문자 지우는 부분
					main_game_running = move(&x, &y, user);	// x, y, ch 받아 사용자 위치 움직이는 부분
					user_movable--;
				}
				// 이벤트 실행 확인 부분
				event_check();
			}
		}
		// 메인게임 종료 및 미니게임 시작
		if (main_game_running == 0 && letter == 'y'){
			// 게임 종료시 부분(whlie문 끝) + 0609 난이도 별로 시간에 따른 학기 수 & 일정 시간을 넘기면 학위 취득 실패 출력 후 메인메뉴로 돌아가야 함.
			// 메인게임에서 취득한 학기 저장.
			tm2 = time(NULL);
			if(tm2 - tm1 > time_limit[level-1])
				ranking[level-1] = 2 + (tm2 - tm1 - time_limit[level-1]) / 10;
			else
				ranking[level-1] = 2;
			// 한 번에 10학기 넘으면 게임오버시킴
			if(ranking[level-1] > semester_limit){
				// 게임 오버
				player_select_1 = 8;
				continue;
			}
			system("cls");
			for(int i = 0; i < size; i++){
				for(int j = 0; j < size; j++){
					map[i][j] = 0;
				}
			}
			// printText("SYSTEM | map 초기화 완료", 0, 0);
			// p = &map[0][0];
			// while ((int)(&map[size-1][size-1] - p) < size * size){
			// 	*p = 0;
			// 	p++;
			// }
			// 미니게임 시작멘트
			menu(21);
			loading(25);
			system("cls");

			// 변수 초기화, 미니게임 학기 저장해줌.
			minigame_result = 0;
			if (level == 1){
				// 초급 - 업다운
				minigame_result = up_and_down_main();
				ranking[level + 2] = minigame_result;
			}
			else if(level == 2){
				// 중급 - 가위바위보
				// minigame_result = 
				minigame_result = rock_scissors_paper();
				print_point(minigame_result);
				ranking[level + 2] = minigame_result;
			}	
			else if(level == 3){
				// 고급 - 공룡
				minigame_result = jumping_man_main();
				ranking[level + 2] = minigame_result;
			}
			// 원래 배열에 초과학기 더해줌
			ranking[level-1] += minigame_result;

			// 점수 현황 출력 및 다음 게임 난이도 선택 부분
			system("cls");
			if(level < 3){
				menu(22);	// 랭킹 및 다음 난이도 이동 질문 출력
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
			else if (level == 3){
				// 게임 엔딩 부분
				system("cls");
				printSquare(HOR/2-50, 15, HOR/2+50, 45);
				printText_mid("학력정보 열람", 18);
				gotoxy(HOR/2-48, 20);
				printf("%s 님의 학력 정보는 다음과 같습니다.", player_name);

				line = 25;
				if(ranking[0]){
					printText_mid("학사 : ", line);
					printf("%d 학기", ranking[0]);
					line += 2;
				}
				if(ranking[1]){
					printText_mid("석사 : ", line);
					printf("%d 학기", ranking[1]);
					line += 2;
				}
				if(ranking[2]){
					printText_mid("박사 : ", line);
					printf("%d 학기", ranking[2]);
					line += 2;
				}

				printText("총 학기수 : ", HOR/2-18, 35);
				printf("%d 학기 입니다.", ranking[0] + ranking[1] + ranking[2]);
				
				printText("당신의 현재 나이는 ", HOR/2-20, 37);
				age = (ranking[0] + ranking[1] + ranking[2]) / 2 + 20;
				printf("%d 살입니다.", age);
				
				if(age < 26)
					printText_mid("대단하군요! 대한민국의 미래는 당신에게 달려 있습니다!", 39);
				else if(age < 31)
					printText_mid("게임 클리어! 수고하셨습니다. 이제 취업만이 남아 있네요.", 39);
				else
					printText_mid("조금 걸리긴 했지만... 그래도 수고하셨습니다!", 39);
				
				printText_mid("Press Enter To Restart", 43);
				printText_mid("< The End >", 48);

				ch = _getch();
				// rank(ranking, player_name);
				level = 1;	// 다시 레벨 초기화 -> 처음부터 할 수 있게
				player_select_1 = 0;
				ch = 0;
			}
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

int WINAPI user_input(LPVOID param){
	int p = *(int*)param;
	while(1){
		if(main_game_running){
			user = _getch();
			// 두번 가는 부분 구현
			if(event_endtime[2])
				user_movable = 2;
			else
				user_movable = 1;
			//printText("user_input 실행중", HOR/2, 30);
		}
		Sleep(10);
	}
	return 1;
}

void printText_mid(char *text, int y){
	gotoxy((HOR-strlen(text))/2, y);
	printf("%s", text);
	return;
}

void event_check(){
	int current_time = 0, cnt = 0, temp = 0;
	
	int event_end_arr[10] = { 0 };
	// 이벤트 문구 출력 부분 -> main에서 실행
	

	// 아무 이벤트나 종료할 것이 있다면 event_end_arr 에 저장 후 cnt+=1
	current_time = time(NULL);
	for(int i = 0; i < event_length; i++){
		if(event_endtime[i] && event_endtime[i] < current_time){
			event_end_arr[cnt] = i;	// 인덱스 번호를 배열에 저장
			cnt += 1;
		}
	}
	// 이벤트 종료
	// -> 시간 0으로 설정, 변수들 원래대로 초기화
	// 끝내야 할 것들만 배열에 담아 그것들만 초기화함.
	for(int i = 0; i < cnt; i++){
		switch(event_end_arr[i]){
			case 0:
				// 보물 위치 보이게 -> 다시 숨김
				event_endtime[0] = 0;
				printText("▶\b\b", (treasure_x+1)*2, treasure_y+min_y);
			break;
			case 1:
				// 교수 안보이게 함 -> 다시 보이게
				event_endtime[1] = 0;
				for(int i = 0; i < 50; i++){
					for(int j = 0; j < 50; j++){
						if(map[i][j] == 3){
							printText("교", (j+1)*2, i+min_y);
						}
					}
				}
			break;
			case 2:
				// 이동속도 두배 -> 원래 이동속도로 복귀
				event_endtime[2] = 0;
				p_x_speed = 2;
				p_y_speed = 1;
			break;
			case 3:
				event_endtime[3] = 0;
			break;
			case 4:
				event_endtime[4] = 0;
			break;
			case 5:
				// 아무 효과도 x
				event_endtime[5] = 0;
			break;
			case 6:
				// 방향 반전 -> 원래대로 설정
				event_endtime[6] = 0;
			break;
			case 7:
				// 모든 깃발, 교수 아이콘 사라지게 -> 다시 보이게
				event_endtime[7] = 0;
				for(int i = 0; i < size; i++){
					for(int j = 0; j < size; j++){
						if(map[i][j] == 3){
							printText("교", (j+1)*2, i+min_y);
						}
						else if(map[i][j] == 4 || map[i][j] == 5){
							printText("▶", (j+1)*2, i+min_y);
						}
					}
				}
			break;
			case 8:
				// 8번 깃발 개수 초기화 및 재설정.
				event_endtime[8] = 0;
				flag(level);
				printMap();
			break;
			case 9:
				// 플레이시간 5초 늘리기, 바로 실행해야해서 등호 추가함.
				event_endtime[9] = 0;
				tm1 -= 5;
			break;
			deault:
				printText("ERROR : event_end_checking", 0, 0);
			break;
		}
	}
	
	// 이벤트 출력문구 다시 고쳐줌
	if(cnt){
		line = first_line + 11;
		printBlank(107, line, 187, 50);
		for(int i = 0; i < event_length; i++){
			if(event_endtime[i]){
				menu(i + 23);
			}
		}
	}
	return;
}


void loading(int p_line){
	for (int i = 0; i < 11; i++) {
		gotoxy(0, p_line);
		text_align_center(HOR, "            ");
		gotoxy(0, p_line+2);
		text_align_center(HOR, "                    ");
		//printBlank(HOR-5, p_line, HOR+5, p_line);
		//printBlank(HOR-10, p_line+2, HOR+10, p_line+2);

		gotoxy(0, p_line);
		text_align_center(HOR, "Loading");
		gotoxy(HOR/2+4, p_line);
		printf("...");

		gotoxy(0, p_line+2);
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
	// int line = first_line + 11;
	line = first_line + 11;
	int temp = 0;
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
			// text_align_center(HOR, "4. 개발자 모드");
			// gotoxy(0, 28);
			// text_align_center(HOR, "5. 졸업기록 열람");
			text_align_center(HOR, "4. 졸업기록 열람");
			// gotoxy(0, 32);
			gotoxy(0, 28);
			// text_align_center(HOR, "6. 게임 종료");
			text_align_center(HOR, "5. 게임 종료");
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
		case 23:
            // 보물 1초동안 보여주기
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("교수님의 서재에서 특별 정보를 얻었습니다! 졸업 논문의 끝이 희미하게 보입니다!", 107, line);
            line += 3;
        break;
        case 24:
            // 교수 5초동안 숨기기
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("교수님이 휴가에 가십니다! 3초동안 교수님이 사라집니다.", 107, line);
            line += 3;
        break;
        case 25:
            // 이동속도 두배 -> move.c 에서 바꿔줌
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("에너지 드링크를 획득했습니다! 5초 동안 이동속도가 빨라집니다.", 107, line);
            line += 3;
        break;
        case 26:
            // 긍정 효과 없음 1
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("교수님으로부터 칭찬을 받았습니다. 왠지 기분이 좋아집니다.", 107, line);
            line += 3;
        break;
        case 27:
            // 긍정 효과 없음 2
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("이번에 나간 미팅에서 상대의 반응이 좋습니다. 기분이 1 좋아집니다.", 107, line);
            line += 3;
        break;
        case 28:
            // 부정 효과 없음 1
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("찢어진 논문을 발견했습니다... 내 논문은 아니지만 왠지 가슴이 아픕니다.", 107, line);
            line += 3;
        break;
        case 29:
            // 이동 방향 바뀜
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("너무 오랬동안 밤을 샜습니다.",107, line);
            printText("8초간 어지러워서 방향감각이 사라집니다.",107, line+1);
            line += 3;
        break;
        case 30:
            // 모든 깃발 사라짐
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("너무 오랬동안 밤을 샜습니다. 잠시동안 앞이 보이지 않습니다.",107, line);
            printText("(8초간 모든 깃발, 교수 아이콘 사라짐)",107, line+1);
            line += 3;
        break;
        case 31:
            // 깃발 초기화 및 재배치
            printBlank(107, first_line + line, 187, first_line + line + 2);
            temp = rand() % 2;
            if(temp % 2 == 0)
                printText("졸업논문 주제가 바뀌었습니다...다시 준비해야 합니다. ", 107, line);
            else
                printText("졸업논문이 담긴 하드가 날아갔습니다...새로 작성해야 합니다.", 107, line);
            printText("깃발 개수가 초기화되고 보물이 재배치됩니다.", 107, line + 1);
            Sleep(2000);
            tm1 + 3;
            line += 3;
        break;
        case 32:
            // 시간 5초 늘리기
            printBlank(107, first_line + line, 187, first_line + line + 2);
            printText("코로나 19로 인해 졸업 프로젝트 발표일이 늦어졌습니다.", 107, line);
            printText("제한시간이 5초 줄어듭니다.", 107, line+1);
            line += 3;
        break;
		default:
			printText("ERROR : MENU FUNCTION\n", 0, 0);
			break;
	}
	return;
}
