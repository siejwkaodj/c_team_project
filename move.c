﻿#include "header.h"
extern detection(int*, int*, int);
extern printText(char*, int, int);  // printMap.c에 있음. -> 기본위치 107, 12정도
// 사용자 위치 배열에서 움직이는 함수
void professor();
void flag_effect();

int move(int *x, int *y, int ch){
    char text[1000];
    int tx = *x, ty = *y;   // tx, ty -> x, y좌표 임시로 저장하는 변수
    switch(detection(&tx, &ty, ch)){    // detection()에서 다음 칸에 뭐가 있는지 반환해줌, 빈 칸 = 0 / 장애물 = 2 / 교수 = 3 / 깃발 - 4 / 보물 - 5
        // 빈 칸
        case 0:
            *x = tx;
            *y = ty;
            break;
        // 장애물, 칸 범위 넘어가도 장애물 판정.
        case 2:
            printText("                                                            ",107, 12);
            printText("너는 못 지나간다", 107, 12);
            break;
        // 교수
        case 3:
            professor();
            break;
        // 깃발
        case 4:
            flag_effect();
            *x = tx;
            *y = ty;
            break;
        // 보물
        case 5:
            printText("게임 승리!", 107, 12);
            for(int i = 0; i < 3; i++){
                gotoxy(107, 13);
                sprintf(text, "Ending in %d...", 3-i);
                printf("%s", text);
                Sleep(1*1000);

                printText("                    ", 107, 13);
            }
            
            return 0;
            break;
    }
    return 1;
}
// 깃발 보물 아닌거 먹었을 때 랜덤 효과 나오는거 -> 추가 필요
void flag_effect(){
    int temp = rand() % 10;
    printText("                                                            ",107, 12);  // 지우기
    if (temp == 0){
        printText("꽝!",107, 12);
    }
    else if(temp == 1){

    }
    return;
}

// 교수 때문에 못 움직이는거 구현해야함
void professor(){
    char text[1000];
    unsigned int st = time(NULL), endt;
    printText("                                                            ",107, 12);
    printText("앗 교수님한테 걸렸습니다", 107, 12);
    printText("3초동안 움직이지 못합니다.", 107, 13);
    endt = time(NULL);
    while(endt - st < 3){
        gotoxy(107, 14);
        sprintf(text, "%d...", endt - st);    // 문자열에 변수 집어넣기 -> sprintf();
        printf("%s", text);
        printText("     ", 107, 13);
    }
    return;
}

