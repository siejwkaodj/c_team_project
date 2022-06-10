#include "header.h"
extern int detection(int*, int*, int);
extern void printText(char*, int, int);  // printMap.c에 있음. -> 기본위치 107, 12정도
extern void printBlank(int, int, int, int);

// 전역변수
int treasure_x = 0, treasure_y = 0;
extern int size;
extern int first_line;
extern int map[50][50];
extern int p_x_speed, p_y_speed;
extern int professor_location[20][2];
extern time_t tm1, tm2;

// 사용자 위치 배열에서 움직이는 함수
void professor();
void flag_effect();
int find_treasure();

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
            printBlank(107, first_line, 180, first_line);
            printText("너는 못 지나간다", 107, first_line);
            break;
        // 교수
        case 3:
            map[ty][tx] = 0;    // 맵 이부분 초기화 해줘야함.
            *x = tx;
            *y = ty;
            professor();
            break;
        // 깃발
        case 4:
            map[ty][tx] = 0;
            flag_effect();
            *x = tx;
            *y = ty;
            break;
        // 보물
        case 5:
            printText("게임 승리!", 107, first_line);
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
    int temp = rand() % 10;         // temp에 랜덤으로 나올 효과 지정.
    int st = time(NULL);
    printBlank(107, first_line, 180, first_line);   // 첫줄 지우기
    // 긍정적 효과
    
    if (temp == 0){
        // 잠시동안 보물의 위치 보여줌
        printText("잠시동안 보물의 위치가 드러납니다", 107, first_line);
        if(find_treasure()){
            printText("📋\b\b", treasure_x, treasure_y);
            while(time(NULL) - st < 1); // sleep 써도 상관없을듯?
            printText("▶\b\b", treasure_x, treasure_y);
        }
        else
            printText("ERROR : NO TREASURE", 0, 0);
    }
    else if(temp == 1)
        // 잠시동안 교수 안보이게 함 -> 멀티쓰레드시 사용
        printText("교수님이 휴가를 갑니다. 잠시동안 교수님이 보이지 않습니다.", 107, first_line);
    else if(temp == 2){
        // 이동속도 두배 -> 멀티쓰레드...필요
        printText("에너지드링크를 마셨습니다. 잠시동안 이동 속도가 두배가 됩니다.", 107, first_line);
        p_x_speed *= 2;
        p_y_speed *= 2;
    }
    else if(temp == 3)
        printText("", );
    else if(temp == 4)
        printText("", );
    
    // 부정적 효과
    else if(temp == 5)
        printText("찢어진 논문을 발견했습니다... 가슴이 아픕니다.",107, first_line);
    else if(temp == 6)
        
    else if(temp == 7)
        
    else if(temp == 8)
        
    else if(temp == 9)
        
    return;
}

// 교수 때문에 못 움직이는거 구현해야함
void professor(){
    
    char text[1000];
    unsigned int st = time(NULL), endt;
    printBlank(107, first_line, 180, first_line+3);   // 이전 메세지 지우기
    
    printText("앗 교수님한테 걸렸습니다", 107, first_line);
    printText("3초동안 움직이지 못합니다.", 107, first_line + 1);
    endt = time(NULL);
    
    while(endt - st < 3){
        printBlank(107, first_line + 2, 117, first_line + 2);
        gotoxy(107, first_line+2);
        sprintf(text, "%d...", 3 - (endt - st));    // 문자열에 변수 집어넣기 -> sprintf();
        printf("%s...", text);

        endt = time(NULL);
    }
    printBlank(107, first_line, 180, first_line+3);
    return;
}
// 보물 위치 찾는 함수
int find_treasure(){
    int cnt = 0;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if (map[i][j] == 5){
                cnt = 1;
                treasure_x = j;
                treasure_y = i;
                return 1;
            }
        }
    }
    // 보물을 찾지 못했을 경우 -> ERROR
    if(!cnt)
        return 0;
}