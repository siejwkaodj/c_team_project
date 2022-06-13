/* 업다운 게임 (초급 게임)
- 랜덤으로 1 - 20 사이 숫자 결정
- 5번 안에 맞추면 통과
- Try 1번 늘어날수록 5일 추가(try 6번→ 5일 졸업유예)

#include "header.h"
#define DEFAULT 5 // 감점 당하지 않는 최대 횟수
#define RANGE 20 // 난수 생성 범위

extern loading(int);

int up_and_down_main()
{
	int k, number, answer;
	int i = 1;
	srand(time(NULL));
	number = (rand() % RANGE) + 1;
	

	do
	{
		printf("1부터 20 사이의 수를 맞춰보세요!\n");
		printf("기회는 총 5번입니다. 5회 초과시 1회당 1학기가 추가됩니다!\n");
		printf("%d번째 시도입니다!\n", i);
		printf("제시된 수는 과연 무엇일까요? : ");
		scanf("%d", &answer);

		if (answer > RANGE)
			printf("입력하신 값이 20보다 큽니다! 다시 입력해주세요!\n");

		else if (answer <= RANGE)
		{
			i++;
			if (answer != number)
			{
				printf("\n땡~");
				if (answer < number)
					printf("답보다 작습니다!\n");
				else if (answer > number)
					printf("답보다 큽니다!\n");
				printf("다시 한번 해보세요!\n");
				
			}
		}
		Sleep(1500);
		system("cls");
	} while (answer != number);

	printf("정답입니다!\n");
	printf("총 %d번만에 게임을 클리어했습니다!\n", i);

	if (i > DEFAULT){
		printf("총 %d번 시도하였으므로 졸업 학기가 %d(학사 난이도에 맞게 단위 수정)만큼 추가됩니다...\n", i, i - DEFAULT);
		loading(25);
		return (i - 5);
	
	}
	else {
		printf("총 %d번만에 게임을 클리어했으므로 졸업 학기가 추가되지 않습니다.\n", i);
		loading(25);
		return 0; // if문 때문에 일단은 i문으로 값을 반환시킴. 이후 main에서 추가학기를 따로 계산해주면 됨! 
				  //0609 -> return값을 조건에 따라 다르게 넣어서 따로 main에서 계산할 필요 없음.
	}
}
