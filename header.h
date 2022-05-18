// 0512 완성본 -> flag.c, main.c, header.h
// header.h -> 새로 함수 몇개 정의함.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#define HOR 80

// 함수들 여기서 미리 선언하면 main 윗부분에서 선언 안 해도 됨.
void flag(int level);		// level은 난이도 변수
void printSquare();
void gotoxy(int x, int y);
void printMap();
void printCoord();

int move();