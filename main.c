//main 함수
#include "header.h"

void text_align_center(int columns, char* text);


// 
int main(void) {
	char player_name[] = {0};
	
	//GAME START 혹은 게임이름으로 변경 필요
	text_align_center(HOR, " #####      ##    ##   ##  #######                #####    ##  ##  #######   ######  \n");
	text_align_center(HOR, "##   ##    ####   ### ###   ##  ##               ##   ##   ##  ##   ##  ##   ##  ##  \n");
	text_align_center(HOR, "##        ##  ##  #######   ##                   ##   ##   ##  ##   ##       ##  ##  \n");
	text_align_center(HOR, "##        ######  ## # ##   ####                 ##   ##   ##  ##   ####     #####   \n");
	text_align_center(HOR, "##  ###   ##  ##  ##   ##   ##                   ##   ##   ##  ##   ##       ####    \n");
	text_align_center(HOR, "##   ##   ##  ##  ##   ##   ##  ##           ##  ##   ##    ####    ##  ##   ## ##   \n");
	text_align_center(HOR, " #####    ##  ##  ##   ##  #######                #####      ##    #######   ###  ## \n");

	text_align_center(HOR, "PRESS ALT ENTER");
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

		while (player_select_1 == 1 && player_select_1 == 2 && player_select_1 == 3 && player_select_1 == 4 && player_select_1 == 5) {
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


		
		
		
		}


	}





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