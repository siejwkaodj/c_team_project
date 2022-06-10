#include "header.h"
extern map[50][50];
extern min_x, min_y, max_x, max_y;
extern int p_x_speed, p_y_speed;
// 빈 칸 = 0 / 장애물 = 2 / 교수 = 3 / 깃발 - 4 / 보물 - 5
// 움직일 다음 칸에 뭐가 있는지 반환해줌.
int detection(int *tx, int *ty, int ch) {
	switch (ch)
	{
	case 72:
		*ty -= p_y_speed;
		break;
	case 80:
		*ty += p_y_speed;
		break;
	case 75:
		*tx -= p_x_speed;
		break;
	case 77:
		*tx += p_x_speed;
		break;
	}
	// 칸 넘어가면 장애물로 판단.
	if (*tx < min_x || *tx > max_x || *ty < min_y || *ty > max_y)
		return 2;
	return map[*ty-min_y][*tx/2-1];
}