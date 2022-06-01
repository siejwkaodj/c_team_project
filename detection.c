#include "header.h"
extern map[50][50];
extern min_x, min_y, max_x, max_y;
// 빈 칸 = 0 / 장애물 = 2 / 교수 = 3 / 깃발 - 4 / 보물 - 5
// 움직일 다음 칸에 뭐가 있는지 반환해줌.
int detection(int x, int y, int ch) {
	switch (ch)
	{
	case 72:
		y--;
		break;
	case 80:
		y++;
		break;
	case 75:
		x -= 2;
		break;
	case 77:
		x += 2;
		break;
	}
	// 칸 넘어가면 장애물로 판단.
	if (x < min_x || x > max_x || y < min_y || y > max_y)
		return 2;
	return map[y][x];
}
