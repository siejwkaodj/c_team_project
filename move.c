#include "header.h"
extern detection(int*, int*, int);
extern printText(char*, int, int);  // printMap.c에 있음.
// 사용자 위치 배열에서 움직이는 함수
int move(int *x, int *y, int ch){
    char text[1000];
    int tx = *x, ty = *y;   // x, y좌표 임시로 저장하는 변수
    switch(detection(&tx, &ty, ch)){
        // 빈 칸
        case 0:
            *x = tx;
            *y = ty;
            break;
        // 장애물
        case 2:
            printText("                                                            ",107, 12);
            printText("너는 못 지나간다", 107, 12);
            break;
        // 교수
        case 3:
            printText("                                                            ",107, 12);
            printText("앗 교수님한테 걸렸습니다", 107, 12);
            printText("3초동안 움직이지 못합니다.", 107, 13);
            for(int i = 0; i < 3; i++){
                gotoxy(107, 14);
                sprintf(text, "%d...", 3-i);
                printf("%s", text);
                Sleep(1*1000);

                printText("     ", 107, 13);
            }
            // professor();
            break;
        // 깃발
        case 4:
            printText("                                                            ",107, 12);  // 지우기
            printText("꽝!",107, 12);
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

// 교수 때문에 못 움직이는거 구현해야함
void professor(){
    return;
}