/* ���ٿ� ����
- �������� 1 - 20 ���� ���� ����
- 5�� �ȿ� ���߸� ���
- Try 1�� �þ���� 1�б� �߰�(try 6����1�б� �߰�) 
- ������ ���� �ݿ��� ���� ������� (�� �κ��� ����...) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int k, answer, number;
	int i = 0;
	srand(time(NULL));
	number = (rand() % 20) + 1;
	printf("1���� 20 ������ ���� ���纸����!\n");
	printf("��ȸ�� �� 5���Դϴ�. 5ȸ �ʰ��� 1ȸ�� 1�бⰡ �߰��˴ϴ�!\n");
	
	do 
	{
		printf("���õ� ���� ���� �����ϱ��? : ");
		scanf("%d", &answer);

		if (answer > 20)
			printf("�Է��Ͻ� ���� 20���� Ů�ϴ�! �ٽ� �Է����ּ���!\n");

		else if (answer <= 20)
		{
			i++;
			if (answer != number)
			{
				printf("\n��~");
				if (answer < number)
					printf("�亸�� �۽��ϴ�!\n");
				else if (answer > number)
					printf("�亸�� Ů�ϴ�!\n");
				printf("�ٽ� �ѹ� �غ�����!\n");
				printf("������� �õ��� Ƚ���� %d���Դϴ�.\n", i);
			}
		}
	} while (answer != number);

	printf("�����Դϴ�!\n");
	printf("�� %d������ ������ Ŭ�����߽��ϴ�!\n", i);

	if (i >= 6)
		printf("�� %d�� �õ��Ͽ����Ƿ� %d�б⸸ŭ �߰��˴ϴ�...\n", i, i - 5);
}