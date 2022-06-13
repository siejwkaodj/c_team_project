#include "header.h"
extern int detection(int*, int*, int);
extern void printText(char*, int, int);  // printMap.c에 있음. -> 기본위치 107, 12정도
extern void printBlank(int, int, int, int);

// 전역변수
int treasure_x = 0, treasure_y = 0;
extern int size;
extern int line;
extern const int HOR;
extern const int first_line;
extern int map[50][50];
extern int max_x, max_y, min_x, min_y;
extern int p_x_speed, p_y_speed;
extern int professor_location[20][2];
extern int event_endtime[10];
extern int event_length;
extern int user_movable;
extern time_t tm1, tm2;

// 사용자 위치 배열에서 움직이는 함수
void professor();
void flag_effect();
int find_treasure();
int effect(int);

int move(int *x, int *y, int ch){
    char text[1000];
    int tx = *x, ty = *y;   // tx, ty -> x, y좌표 임시로 저장하는 변수
    switch(detection(&tx, &ty, ch)){    // detection()에서 다음 칸에 뭐가 있는지 반환해줌, 빈 칸 = 0 / 장애물 = 2 / 교수 = 3 / 깃발 - 4 / 보물 - 5
        // 빈 칸
        case 0:
            *x = tx;
            *y = ty;
            // // 방향 반대로 설정
            // if(event_endtime[6]){
            //     *x = 2 * (*x) - tx;
            //     *y = 2 * (*y) - ty;
            // }
            // else{
            //     *x = tx;
            //     *y = ty;
            // }
            break;
        // 장애물, 칸 범위 넘어가도 장애물 판정.
        case 2:
            printBlank(107, first_line, 180, first_line);
            printText("너는 못 지나간다", 107, first_line);
            break;
        // 교수
        case 3:
            map[ty - min_y][tx / 2 - 1] = 0;    // 맵 이부분 초기화 해줘야함.
            *x = tx;
            *y = ty;
            // if(event_endtime[6]){
            //     *x = 2 * (*x) - tx;
            //     *y = 2 * (*y) - ty;
            // }
            // else{
            //     *x = tx;
            //     *y = ty;
            // }
            professor();
            break;
        // 깃발
        case 4:
            map[ty - min_y][tx / 2 - 1] = 0;
            *x = tx;
            *y = ty;
            // if(event_endtime[6]){
            //     *x = 2 * (*x) - tx;
            //     *y = 2 * (*y) - ty;
            // }
            // else{
            //     *x = tx;
            //     *y = ty;
            // }
            flag_effect();
            break;
        // 보물
        case 5:
            printBlank(HOR / 2 - 50, 20, HOR/2+50, 40);
            printSquare(HOR / 2 - 50, 20, HOR/2+50, 40);
            gotoxy((HOR-strlen("졸업 논문을 획득했습니다! 드디어 졸업할 수 있습니다!"))/2, 25);
            printf("졸업 논문을 획득했습니다! 드디어 졸업할 수 있습니다!");
            //printText("졸업 논문을 획득했습니다! 드디어 졸업할 수 있습니다!", 107, first_line);
            
            for(int i = 0; i < 3; i++){
                //gotoxy(107, first_line + 1);
                gotoxy((HOR-strlen("Ending in %d..."))/2, 30);
                sprintf(text, "Ending in %d...", 3-i);
                printf("%s", text);
                Sleep(1*1000);

                //printText("                    ", 107, first_line+1);
                
            }
            
            return 0;
            break;
    }
    return 1;
}
// 깃발 보물 아닌거 먹었을 때 랜덤 효과 나오는거 -> 추가 필요
void flag_effect(){
    int temp = rand() % 10;         // temp에 랜덤으로 나올 효과 지정.
    int st = time(NULL), event_running = 0, line = first_line + 11;
    printBlank(107, first_line+10, 180, first_line+30);   // 기존 효과 나오던거 지우기
    // 실행중인 효과 개수 셈
    for(int i = 0; i < event_length; i++){
        if(event_endtime[i])
            event_running++;
    }
    // 깃발 효과 -> 기존에 효과가 이미 실행되고 있으면 다른거로 실행, 다 실행되고 있으면 아무것도 추가 실행 안함
    if(event_running < 10){
        while(event_endtime[temp]){
            temp = rand() % 10;
        }
        // 이벤트 시작 설정 부분, 한번씩만 실행
        if(!event_endtime[temp]){
            // 긍정적 효과
            st = time(NULL);
            if (temp == 0){
                // 잠시동안 보물의 위치 보여줌, 1초
                event_endtime[temp] = st + 1;
                
                // 보물 위치 잠시 보여주기
                if(!find_treasure())
                    printText("ERROR : NO TREASURE", 0, 0);
                else
                    printText("📋\b\b", (treasure_x+1)*2, treasure_y+min_y);
            }
            else if(temp == 1){
                // 3초간 교수 안보이게 함 -> 멀티쓰레드시 사용
                event_endtime[temp] = st + 3;
                for(int i = 0; i < 50; i++){
                    for(int j = 0; j < 50; j++){
                        if(map[i][j] == 3){
                            printText("  ", (j+1)*2, i+min_y);
                        }
                    }
                }
            }
            else if(temp == 2){
                // 5초간 이동속도 두배 -> 멀티쓰레드...필요
                event_endtime[temp] = st + 5;
                p_x_speed *= 2;
                p_y_speed *= 2;
            }
            else if(temp == 3){
                // 긍정 효과 없음 1
                event_endtime[temp] = st + 4;
            }
            else if(temp == 4){
                // 긍정 효과 없음 2
                event_endtime[temp] = st + 4;
            }

            // 부정적 효과 부분
            else if(temp == 5){ // 아무 효과도 x
                event_endtime[temp] = st + 4;
            }
            else if(temp == 6){
                // 방향 좌우 / 상하 / 상하좌우 반전, 8초간
                event_endtime[temp] = st + 8;

            }
            else if(temp == 7){
                // 8초동안 모든 깃발, 교수 아이콘 사라지게 함.
                event_endtime[temp] = st + 8;
                for(int i = 0; i < size; i++){
                    for(int j = 0; j < size; j++){
                        if(map[i][j] == 3 || map[i][j] == 4 || map[i][j] == 5){
                            printText("  ", (j+1)*2, i+min_y);
                        }
                    }
                }
                
            }
            else if(temp == 8){
                // 깃발 개수 초기화
                event_endtime[temp] = st;

            }
            else if(temp == 9){
                // 플레이 시간 5초 늘리기
                event_endtime[temp] = st;
            }
        }
    }
    // 이벤트 문구 출력 부분 -> main에서 실행
    line = first_line + 11;
    for(int i = 0; i < event_length; i++){
        if(event_endtime[i]){
            switch(i){
                case 0:
                    // 보물 1초동안 보여주기
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("교수님의 서재에서 특별 정보를 얻었습니다! 졸업 논문의 끝이 희미하게 보입니다!", 107, line);
                    line += 3;
                break;
                case 1:
                    // 교수 5초동안 숨기기
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("교수님이 휴가에 가십니다! 3초동안 교수님이 사라집니다.", 107, line);
                    line += 3;
                break;
                case 2:
                    // 이동속도 두배 -> move.c 에서 바꿔줌
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("에너지 드링크를 획득했습니다! 5초 동안 이동속도가 빨라집니다.", 107, line);
                    line += 3;
                break;
                case 3:
                    // 긍정 효과 없음 1
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("교수님으로부터 칭찬을 받았습니다. 왠지 기분이 좋아집니다.", 107, line);
                    line += 3;
                break;
                case 4:
                    // 긍정 효과 없음 2
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("이번에 나간 미팅에서 상대의 반응이 좋습니다. 기분이 1 좋아집니다.", 107, line);
                    line += 3;
                break;
                case 5:
                    // 부정 효과 없음 1
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("찢어진 논문을 발견했습니다... 내 논문은 아니지만 왠지 가슴이 아픕니다.", 107, line);
                    line += 3;
                break;
                case 6:
                    // 이동 방향 바뀜
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("너무 오랬동안 밤을 샜습니다.",107, line);
                    printText("8초간 어지러워서 방향감각이 사라집니다.",107, line+1);
                    line += 3;
                break;
                case 7:
                    // 모든 깃발 사라짐
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("너무 오랬동안 밤을 샜습니다. 잠시동안 앞이 보이지 않습니다.",107, line);
                    printText("(8초간 모든 깃발, 교수 아이콘 사라짐)",107, line+1);
                    line += 3;
                break;
                case 8:
                    // 깃발 초기화 및 재배치
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    temp = rand() % 2;
                    if(temp % 2 == 0)
                        printText("졸업논문 주제가 바뀌었습니다...다시 준비해야 합니다. ", 107, line);
                    else
                        printText("졸업논문이 담긴 하드가 날아갔습니다...새로 작성해야 합니다.", 107, line);
                    printText("깃발 개수가 초기화되고 보물이 재배치됩니다.", 107, line + 1);
                    Sleep(3000);
                    tm1 + 3;
                    line += 3;
                break;
                case 9:
                    // 시간 5초 늘리기
                    printBlank(107, first_line + line, 187, first_line + line + 2);
                    printText("코로나 19로 인해 졸업 프로젝트 발표일이 늦어졌습니다.", 107, line);
                    printText("제한시간이 5초 줄어듭니다.", 107, line+1);
                    line += 3;
                break;
                default:
                    printText("ERROR : MENU FUNCTION\n", 0, 0);
                    break;
            }
        }
    }
    return;
}

// 교수 때문에 못 움직이는거 구현해야함
void professor(){
    int temp = rand() % 3;
    // 교수 안보이게 하는 효과 없을때만 효과실행
    if(!event_endtime[1]){
        char text[1000];
        printBlank(107, first_line, 180, first_line+3);   // 이전 메세지 지우기
    
        printText("앗 교수님의 눈에 띄었습니다", 107, first_line);
        if(temp == 0)
            printText("연구실 정리를 합니다. (3초 소모)", 107, first_line + 1);
        else if(temp == 1)
            printText("조교들과 함께 학부생들의 시험 채점을 합니다. (3초 소모)", 107, first_line + 1);
        else
            printText("교수님이 갑자기 내일까지 논문 아이디어를 가져오라고 합니다. (3초 소요)", 107, first_line + 1);

        for(int i = 0; i < 3; i++){
            printBlank(107, first_line + 2, 117, first_line + 2);
            gotoxy(107, first_line+2);
            sprintf(text, "%d...", 3 - i);    // 문자열에 변수 집어넣기 -> sprintf();
            printf("%s...", text);
            Sleep(1000);
            
        }
        printBlank(107, first_line, 180, first_line+3);
    }
    return;
}
// 보물 위치 찾는 함수 -> treasure_x, y에 저장
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
    return 1;
}