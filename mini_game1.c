#include "header.h"
#define SET 5
// �ʱް��� - ����������
// �� 5ȸ ����, 8�� �̸� --> �г�Ƽ �ο�. (1�� �� 1�б� ����)
// ���̵��� �°� printf�� �����ؾ���...(���� ������ �ٸ��Ƿ�)

int set_random() // ������ ���������� ���� ����
{
	int x;
	srand(time(NULL));
	x = rand() % 3;
	return x;
}

int decision(int x, int y) // ���� �ǵ�
{
	int result;

	if (x == 0 && y == 0 || x == 1 && y == 1 || x == 2 && y == 2)
		result = 0;
	else if (x == 0 && y == 1 || x == 1 && y == 2 || x == 2 && y == 0)
		result = 1;
	else
		result = 2;

	return result;
}

int print_result(int z) // ���п� ���� ���� ȹ��
{
	int point = 0;
	switch (z)
	{
	case 0:
		printf("���º��Դϴ�.\n2���� �߰��˴ϴ�.\n");
		point += 2;
		break;
	case 1:
		printf("�������� �̰���ϴ�!\n3���� �߰��˴ϴ�.\n");
		point += 3;
		break;
	case 2:
		printf("�������� �̰���ϴ�...\n1���� �߰��˴ϴ�.\n");
		point += 1;
		break;
	}
	return point;
}

int get_input() // ���������� �� �Է� 
{
	int x;
	printf("���������� ������ �����ϰڽ��ϴ�!\n�ּ��� ���� �������� �̰ܺ�����!\n");
	printf("�¸� �� 3��, ���º� �� 2��, �й� �� 1���� �����˴ϴ�!\n\n");
	printf("�� 5���� ��ȸ�� �־�����, 8���� ���� ���� �� 1�� �� �� �б� ������ �ʰ� �մϴ�...\n");
	do
	{
		printf("\n������ ����� ? (���� : 0, ���� : 1, �� : 2) : ");
		scanf("%d", &x);
		if (x != 0 && x != 1 && x != 2)
			printf("�߸��� ���� �Է��Ͽ����ϴ�. �ٽ� �Է����ּ���!");
	} while (x != 0 && x != 1 && x != 2);

	return x;
}

int rock_scissors_paper() // ���� �ݺ� (�� 5ȸ), main.c�� point�� ��ȯ����� ��!
{
	int professor, user, result;
	int point = 0;
	int i = 0;
	do
	{
		professor = set_random(); // 0 ~ 2 ������ ������ ��ȯ
		user = get_input(); // ����� �Է� ������ ��ȯ
		printf("\n������ : %d, �� : %d\n", professor, user);
		result = decision(professor, user); // ���º� (0), ����� �¸�(1), ������ �¸�(2) ��ȯ
		point += print_result(result); // ���п� ���� �ش� ���ڿ� ���, switch�� Ȱ��
		i++;
		Sleep(1500);
		system("cls");
	} while (i < SET);
	return point;
}

void print_point() //���� ��� (�̴ϰ��� ȭ�鿡�� ����� ���, ���� ������ rock_scissors_paper()�� ���ؼ� main.c�� ��ȯ)
{
	int point = 0;

	point = rock_scissors_paper();

	printf("���� : %d\n", point);

	if (point > 8)
		printf("������ 8�� �̻��̹Ƿ� ������ �������� �ʽ��ϴ�! �����մϴ�~\n");
	else
		printf("������ 8�� �̸��̹Ƿ� %d�б⸸ŭ ������ �����˴ϴ�...\n", 8 - point);
}