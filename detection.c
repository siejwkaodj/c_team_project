void detect() {
	if (map[x][y] == "��")
		return 0;
	else if (map[x][y] == "��")
		return 1;
	else if (map[x][y] == "��")
		return 2;
	else
		return 3;
}
// ��ֹ� = 0 / ���� = 1 / ��� �� ���� = 2 / �ƹ��͵� ����ĭ = 3
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
	// �̵��� ĭ�� ������ �ִ��� ������ ��ǥ�� �ٽ� ���ڸ��� �̵���.