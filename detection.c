#include "header.h"
extern map[50][50];
<<<<<<< HEAD
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
=======

int detect(int x, int y) {
	if (map[x][y] == "▩")
		return 0;
	else if (map[x][y] == "◎")
		return 1;
	else if (map[x][y] == "▶")
		return 2;
	else
		return 3;
}
// 장애물 = 0 / 교수 = 1 / 깃발 및 보물 = 2 / 아무것도 없는칸 = 3
void detection(int x,int y, int ch) {
	int detectional;
	switch (ch)
	{
	case 72:
		
			y--;
			detectional = detect(x, y);
			y++;
		break;
	case 80:
			
			y++;
			detectional = detect(x, y);
			y--;
		break;
	case 75:
	
			x -= 2;
			detectional = detect(x, y);
			x += 2;
		break;
	case 77:
	
			x += 2;
			detectional = detect(x, y);
			x += 2;
		break;
	}
	return detectional;
}
	// 이동할 칸에 무엇이 있는지 판정후 좌표를 다시 제자리로 이동함.
>>>>>>> 4146fafbd2405d9d33cc4af72bfd43ac7f03a668
