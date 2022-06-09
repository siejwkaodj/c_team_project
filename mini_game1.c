#include "header.h"
#define SET 5
// 초급게임 - 가위바위보
// 총 5회 시행, 8점 미만 --> 패널티 부여. (1점 당 1학기 유예)
// 난이도에 맞게 printf를 수정해야함...(점수 단위가 다르므로)

int set_random() // 교수님 가위바위보 랜덤 생성
{
	int x;
	srand(time(NULL));
	x = rand() % 3;
	return x;
}

int decision(int x, int y) // 승패 판독
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

int print_result(int z) // 승패에 따른 점수 획득
{
	int point = 0;
	switch (z)
	{
	case 0:
		printf("무승부입니다.\n2점이 추가됩니다.\n");
		point += 2;
		break;
	case 1:
		printf("교수님을 이겼습니다!\n3점이 추가됩니다.\n");
		point += 3;
		break;
	case 2:
		printf("교수님이 이겼습니다...\n1점이 추가됩니다.\n");
		point += 1;
		break;
	}
	return point;
}

int get_input() // 가위바위보 값 입력 
{
	int x;
	printf("가위바위보 게임을 시작하겠습니다!\n최선을 다해 교수님을 이겨보세요!\n");
	printf("승리 시 3점, 무승부 시 2점, 패배 시 1점이 적립됩니다!\n\n");
	printf("총 5번의 기회가 주어지며, 8점을 넘지 못할 시 1점 당 한 학기 졸업을 늦게 합니다...\n");
	do
	{
		printf("\n무엇을 낼까요 ? (가위 : 0, 바위 : 1, 보 : 2) : ");
		scanf("%d", &x);
		if (x != 0 && x != 1 && x != 2)
			printf("잘못된 값을 입력하였습니다. 다시 입력해주세요!");
	} while (x != 0 && x != 1 && x != 2);

	return x;
}

int rock_scissors_paper() // 게임 반복 (총 5회), main.c에 point값 반환해줘야 함!
{
	int professor, user, result;
	int point = 0;
	int i = 0;
	do
	{
		professor = set_random(); // 0 ~ 2 사이의 랜덤값 반환
		user = get_input(); // 사용자 입력 정수값 반환
		printf("\n교수님 : %d, 나 : %d\n", professor, user);
		result = decision(professor, user); // 무승부 (0), 사용자 승리(1), 교수님 승리(2) 반환
		point += print_result(result); // 승패에 따라서 해당 문자열 출력, switch문 활용
		i++;
		Sleep(1500);
		system("cls");
	} while (i < SET);
	return point;
}

void print_point() //총점 출력 (미니게임 화면에서 결과를 출력, 실제 점수는 rock_scissors_paper()를 통해서 main.c에 반환)
{
	int point = 0;

	point = rock_scissors_paper();

	printf("총점 : %d\n", point);

	if (point > 8)
		printf("총점이 8점 이상이므로 졸업이 유예되지 않습니다! 축하합니다~\n");
	else
		printf("총점이 8점 미만이므로 %d학기만큼 졸업이 유예됩니다...\n", 8 - point);
}