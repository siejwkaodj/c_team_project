# C 프로그래밍 6조 팀플
송현준
한성준
차민우
조성호
정하린

# 게임 하는 법
1. 파일들을 다운받는다(기타c파일들 폴더에 있는 파일들은 사용할 필요 x).
2. visual studio에서 빈 프로젝트를 만들고, "헤더파일" 칸에 header.h 파일을, "소스파일"칸에 나머지 c파일들을 넣어준다.
3. '디버깅하지 않고 실행' 또는 '디버깅'을 눌러 파일을 실행한다.

# 게임 이름
대학원 탈출

# 게임 설명
난이도 
- 학부생(초급)
- 석사학위(중급)
- 박사학위(고급)

# 미니게임 목록
- 가위바위보
- 업/다운 게임
- 공룡 게임

# 프로그램, 함수 설명
## header.h
- 필요한 헤더 파일들 미리 선언함.
- define으로 상수 설정하면 반영 안됨.
- 함수 선언하면 빌드시 여러 곳에서 정의되었다고 오류남.

## main.c - int main() 
- main함수. 게임 시작 시 메뉴 출력함.
- gotoxy()함수 정의되어 있음.

## main.c - void gotoxy(int x, int y)
- x, y로 커서를 옮겨주는 함수
- main함수에 선언되어 있음.
- printMap함수에서 extern으로 참조함.

## flag.c - void flag.c(int level)
- 깃발, 장애물, 보물, 교수(추가예정) 위치를 map(전역변수)에 만들고 종료함.

## printMap.c - void printMap()
- 사각형 틀, map에 있는 깃발, 장애물, 교수(추가예정)를 위치에 맞게 출력함.

## move.c -> int main()
- 위에 있는 flag(), printMap()등을 다 합쳐서 출력된 맵 위에서 사용자가 움직일 수 있게 함.


# 참고 자료
- 멀티쓰레드 : 
- https://m.blog.naver.com/PostView.naver?isHttpsRedirect=true&blogId=ratmsma&logNo=40023762818
- https://velog.io/@ruthetum/C-Multi-Thread-%EA%B5%AC%ED%98%84-1
