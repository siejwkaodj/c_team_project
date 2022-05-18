//���� ���� ����
// �Լ� �̸�, ������� ���� �ʿ�
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#define MAN_X 0
#define MAN_Y 15
#define TREE_X 94
#define TREE_Y 25

void setting();
void gotoxy(int x, int y);
void start();
int game(int);
void score(int);
int crashing();
void end(int);

//��� ���� �Լ�
void draw_man(int);
void earase_man();
void earase_foot();

//���� ���� �Լ�
void tree();
void draw_tree();
void erase_tree();


int treeX = TREE_X;
int manX = MAN_X;
int manY = MAN_Y;

int key = 0; //Ű���� �Է� �ޱ�

int main()
{
	int tic = 0; //���� �� �ð� �������� ���� ���� ���
	int crash = 0; //�浹 üũ

	setting();
	start();

	while (1) {

		tic = game(tic);

		//'�����̽� ��' ������ ����
		if (_kbhit()) {
			key = _getch();
			if (key == 32 && manY - 15 == 0) { //'�����̽� ��'�� ������ ����� �ٴڿ� ���� ��

				int h = 0; //���� ���� �ʱ�ȭ

				while (h < 8) { //y������ 8ĭ ���
					earase_man();
					manY--;
					tic = game(tic);
					crash = crashing();
					if (crash == -1)
						break;
					h++;
				}

				while (h > 0) { //y������ 8ĭ �ϰ�
					tic = game(tic);
					crash = crashing();
					if (crash == -1)
						break;
					manY++;
					earase_man();
					h--;
				}
			}
		}
		crash = crashing();
		if (crash == -1) //�浹 �� Ż��
			break;

	}

	end(tic);

	system("pause>>null");
	return 0;
}
int game(int tic) { //����ȭ�� ���� ���
	score(tic);
	tree();
	draw_man(tic);

	Sleep(20); //0.02��		//������ ����
	tic++;

	return tic;
}

int crashing() { //�浹 ����	//���̵� '��'
	// (����1 && ����2) && ����
	// ����1: ������ ���� 11ĭ���� �ڿ� ����
	// ����2: ������ ���� 15ĭ���� �տ� ����
	// ����1 && ����2: ������ ���� 11ĭ�� 15ĭ ���̿� ����
	// ����: ��� �� 3ĭ�� ���� 5ĭ ���� ���̰� ���ų� ���� ��
	if ((manX + 6 <= treeX + 2 && manX + 10 >= treeX + 2) && manY + 12 >= TREE_Y + 2)
		return -1;
	else
		return 0;
}

void draw_man(int tic) { //��� �׸���

	int toc = tic % 8;

	//��
	gotoxy(manX, manY);			printf("                     \n");
	gotoxy(manX, manY + 1);		printf("            @___@   \n");
	gotoxy(manX, manY + 2);		printf("           @*   *@  \n");
	gotoxy(manX, manY + 3);		printf("           @@___@@ \n");
	gotoxy(manX, manY + 4);		printf("            @   @    \n");
	gotoxy(manX, manY + 5);		printf("          @@@@@@@@@    *   \n");
	gotoxy(manX, manY + 6);		printf("        @@  @@@@  @@  @   \n");
	gotoxy(manX, manY + 7);		printf("       @    @@@@   @@ \n");
	gotoxy(manX, manY + 8);		printf("       @*   @@@@    \n");
	gotoxy(manX, manY + 9);		printf("            @@@@\n");
	gotoxy(manX, manY + 10);	printf("            @@@@\n");
	gotoxy(manX, manY + 11);	printf("            @  @ \n");
	gotoxy(manX, manY + 12);	printf("            @  @  \n");


	//�� ������ ����
	if (toc >= 0 && toc <= 3) //4tic ���� ����
	{
		earase_foot();
		gotoxy(manX, manY + 13); //�� �׸���
		printf("           @   @  \n");
		printf("          @@   @@");
	}
	else
	{
		earase_foot();
		gotoxy(manX, manY + 13); //�� �׸���
		printf("           @   @\n");
		printf("         @@   @@");
	}
}

void earase_foot() { //�� �����
	gotoxy(manX, manY + 13);
	printf("                 \n");
	printf("                 ");
}

void earase_man() { //��� �����
	for (int i = 0; i < 24; i++) {
		gotoxy(manX, 6 + i);
		printf("                              ");
	}
	earase_foot();
}


void draw_tree() { //���� �׸���
	
	gotoxy(treeX, TREE_Y + 1);		  printf("  #  \n");
	gotoxy(treeX, TREE_Y + 2);		  printf("# # #\n");
	gotoxy(treeX + 2, TREE_Y + 3);		printf("#\n");
	gotoxy(treeX + 2, TREE_Y + 4);		printf("#");
}

void erase_tree() { //���� �����
	gotoxy(treeX + 3, TREE_Y);		  printf("  \n");
	gotoxy(treeX + 1, TREE_Y + 1);	printf("      \n");
	gotoxy(treeX + 1, TREE_Y + 2);	printf("      \n");
	gotoxy(treeX + 3, TREE_Y + 3);	  printf("  \n");
	gotoxy(treeX + 3, TREE_Y + 4); 	  printf("  ");
}

void tree() { //���� �����ʿ��� �������� �̵�
	treeX--; //�������� �� ĭ �̵�
	erase_tree(); //�����
	draw_tree(); //�׸���

	if (treeX == 0)
		treeX = TREE_X; //������ ���� ������ �̵��ϸ� �ʱ�ȭ
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void setting() {
	//�ܼ�â ����
	system("title Jumping Man ");
	system("mode con:cols=100 lines=30");

	//Ŀ�� ����
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.dwSize = 1;
	ConsoleCursor.bVisible = 0; //Ŀ�� ����
	SetConsoleCursorInfo(consoleHandle, &ConsoleCursor);
}

void start() { //���� ȭ��
	while (1) {
		gotoxy(30, 10);
		printf("Press 'Space bar' to start the game");
		draw_man(0);

		if (_kbhit()) {
			key = _getch();
			if (key == 32) { //'�����̽� ��' �Է� Ȯ��
				system("cls");
				break;
			}
		}
	}
}

void score(int tic) { //���� ���
	gotoxy(45, 1);
	printf("score : %4d", tic / 5 * 10); // tic/5 �� 10��		//�ʵ� �� 4ĭ Ȯ�� (nõ������)
}

void end(int tic) { //���� ȭ��
	system("cls");
	int a = 10;
	gotoxy(a, a);		printf(" #####      ##    ##   ##  #######            #####    ##  ##  #######   ######  \n");
	gotoxy(a, a + 1);	printf("##   ##    ####   ### ###   ##  ##           ##   ##   ##  ##   ##  ##   ##  ##  \n");
	gotoxy(a, a + 2);	printf("##        ##  ##  #######   ##               ##   ##   ##  ##   ##       ##  ##  \n");
	gotoxy(a, a + 3);	printf("##        ######  ## # ##   ####             ##   ##   ##  ##   ####     #####   \n");
	gotoxy(a, a + 4);	printf("##  ###   ##  ##  ##   ##   ##               ##   ##   ##  ##   ##       ####    \n");
	gotoxy(a, a + 5);	printf("##   ##   ##  ##  ##   ##   ##  ##           ##   ##    ####    ##  ##   ## ##   \n");
	gotoxy(a, a + 6);	printf(" #####    ##  ##  ##   ##  #######            #####      ##    #######   ###  ## \n");

	gotoxy(40, 20);
	printf("final score : %4d", tic / 5 * 10); //���� ����
}
