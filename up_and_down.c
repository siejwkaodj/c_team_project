/* 업다운 게임
- 랜덤으로 1 - 20 사이 숫자 결정
- 5번 안에 맞추면 통과
- Try 1번 늘어날수록 1학기 추가(try 6번→1학기 추가) 
- 점수에 대한 반영을 따로 해줘야함 (이 부분은 아직...) */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	int k, answer, number;
	int i = 0;
	srand(time(NULL));
	number = (rand() % 20) + 1;
	printf("1부터 20 사이의 수를 맞춰보세요!\n");
	printf("기회는 총 5번입니다. 5회 초과시 1회당 1학기가 추가됩니다!\n");
	
	do 
	{
		printf("제시된 수는 과연 무엇일까요? : ");
		scanf("%d", &answer);

		if (answer > 20)
			printf("입력하신 값이 20보다 큽니다! 다시 입력해주세요!\n");

		else if (answer <= 20)
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
				printf("현재까지 시도한 횟수는 %d번입니다.\n", i);
			}
		}
	} while (answer != number);

	printf("정답입니다!\n");
	printf("총 %d번만에 게임을 클리어했습니다!\n", i);

	if (i >= 6)
		printf("총 %d번 시도하였으므로 %d학기만큼 추가됩니다...\n", i, i - 5);
}