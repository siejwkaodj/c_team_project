#include "header.h"

extern HOR;

void rank(int rank[], char player_name[]) {
	text_align_center(HOR, "졸업기록 열람\n\n\n");
	if (rank[0] == 0) {
		printf("학사 취득 기록이 존재하지 않습니다\n");
	}
	else {
		printf("%s님의 학사 취득 기록 : %d 학기\n", player_name, rank[0]);
	}
	if (rank[1] == 0) {
		printf("석사 취득 기록이 존재하지 않습니다\n");
	}
	else {
		printf("%s님의 석사 취득 기록 : %d 학기\n", player_name, rank[1]);
	}
	if (rank[2] == 0) {
		printf("박사 취득 기록이 존재하지 않습니다\n");
	}
	else {
		printf("%s님의 박사 취득 기록 : %d 학기\n", player_name, rank[2]);
	}
	text_align_center(HOR, "\n\n뒤로 가기 - ESC");
return;
}
