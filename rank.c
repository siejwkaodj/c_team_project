#include "header.h"



void rank(int rank[], char player_name[]) {
	text_align_center(HOR, "������� ����\n\n\n");
	if (rank[0] == 0) {
		printf("�л� ��� ����� �������� �ʽ��ϴ�");
	}
	else {
		text_align_center(HOR, "%s���� �л� ��� ��� : %d �б�\n", player_name, rank[0]);
	}
	if (rank[1] == 0) {
		printf("���� ��� ����� �������� �ʽ��ϴ�");
	}
	else {
		text_align_center(HOR, "%s���� ���� ��� ��� : %d �б�\n", player_name, rank[1]);
	}
	if (rank[2] == 0) {
		printf("�ڻ� ��� ����� �������� �ʽ��ϴ�");
	}
	else {
		text_align_center(HOR, "%s���� �ڻ� ��� ��� : %d �б�\n", player_name, rank[2]);
	}



}
