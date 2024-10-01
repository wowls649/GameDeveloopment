#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

#define WIDTH 20
#define HEIGHT 10
#define MAX_OBSTACLES 5

char player;
int playerX, playerY;
int obstacles[MAX_OBSTACLES][2];
int exitGame = 0;
int score = 0;

// 게임 시작 화면을 보여주는 함수
void startScreen()
{
    system("cls");  // 화면을 초기화
    printf("______________________________\n");
    printf("|    WELCOME TO THE GAME     |\n");
    printf("|                            |\n");
    printf("|    Press ENTER to start    |\n");
    printf("------------------------------\n");

    while (1)
    {
        if (_kbhit())   // 키보드 입력 대기
        {
            if (_getch() == 13)  // Enter 키 입력 시 게임 시작
            {
                break;
            }
        }
    }
}

// 게임 설정 초기화
void setup()
{
    player = 'O';  // 플레이어 설정
    playerX = WIDTH / 2;
    playerY = HEIGHT - 1;

    // 장애물 위치 초기화
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        obstacles[i][0] = rand() % WIDTH;
        obstacles[i][1] = rand() % (HEIGHT - 1);
    }
}

// 게임 화면을 그리는 함수
void draw()
{
    system("cls");  // 화면 초기화

    printf("Score: %d\n", score);

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == playerY && j == playerX)
            {
                printf("%c", player);  // 플레이어 위치 출력
            }
            else
            {
                int isObstacle = 0;  // 장애물 여부 확인
                for (int k = 0; k < MAX_OBSTACLES; k++)
                {
                    if (obstacles[k][0] == j && obstacles[k][1] == i)
                    {
                        printf("|");  // 장애물 출력
                        isObstacle = 1;
                        break;
                    }
                }
                if (!isObstacle)
                {
                    if (i == HEIGHT - 1)
                    {
                        printf("_");  // 바닥 출력
                    }
                    else
                    {
                        printf(" ");  // 빈 공간 출력
                    }
                }
            }
        }
        printf("\n");
    }
}

// 사용자 입력 처리 함수
void input()
{
    if (_kbhit())   // 키보드 입력 감지
    {
        switch (_getch())
        {
        case 'a':
            if (playerX > 0) playerX--;  // 왼쪽 이동
            break;
        case 'd':
            if (playerX < WIDTH - 1) playerX++;  // 오른쪽 이동
            break;
        }
    }
}

// 게임 로직 처리 (장애물 이동 및 충돌 체크)
void logic()
{
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        obstacles[i][1]++;  // 장애물 아래로 이동
        if (obstacles[i][1] >= HEIGHT)
        {
            obstacles[i][0] = rand() % WIDTH;  // 새로운 위치에서 장애물 생성
            obstacles[i][1] = 0;  // y좌표 초기화
            score++;  // 점수 증가
        }

        // 플레이어와 장애물 충돌 체크
        if (obstacles[i][0] == playerX && obstacles[i][1] == playerY)
        {
            exitGame = 1;  // 충돌 시 게임 종료
        }
    }
}

// 메인 함수
int main()
{
    startScreen();  // 게임 시작 화면 호출
    setup();  // 게임 초기화
    while (!exitGame)  // 게임 종료 조건이 만족될 때까지 반복
    {
        draw();  // 화면 그리기
        input();  // 사용자 입력 처리
        logic();  // 게임 로직 처리
        Sleep(200);  // 게임 속도 조절
    }

    printf("Game Over! Final Score: %d\n", score);  // 게임 종료 메시지 출력
    return 0;
}
