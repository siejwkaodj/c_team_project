void detect() {
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
void detection(int x,int y) {
	
	switch (_getch())
	{
	case 72:
		
			y--;
			detect();
			y++;
		break;
	case 80:
			
			y++;
			detect();
			y--;
		break;
	case 75:
	
			x -= 2;
			detect();
			x += 2;
		break;
	case 77:
	
			x += 2;
			detect();
			x += 2;
		break;
	}
}
	// 이동할 칸에 무엇이 있는지 판정후 좌표를 다시 제자리로 이동함.