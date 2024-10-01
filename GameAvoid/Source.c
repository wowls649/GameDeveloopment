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

// ���� ���� ȭ���� �����ִ� �Լ�
void startScreen()
{
    system("cls");  // ȭ���� �ʱ�ȭ
    printf("______________________________\n");
    printf("|    WELCOME TO THE GAME     |\n");
    printf("|                            |\n");
    printf("|    Press ENTER to start    |\n");
    printf("------------------------------\n");

    while (1)
    {
        if (_kbhit())   // Ű���� �Է� ���
        {
            if (_getch() == 13)  // Enter Ű �Է� �� ���� ����
            {
                break;
            }
        }
    }
}

// ���� ���� �ʱ�ȭ
void setup()
{
    player = 'O';  // �÷��̾� ����
    playerX = WIDTH / 2;
    playerY = HEIGHT - 1;

    // ��ֹ� ��ġ �ʱ�ȭ
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        obstacles[i][0] = rand() % WIDTH;
        obstacles[i][1] = rand() % (HEIGHT - 1);
    }
}

// ���� ȭ���� �׸��� �Լ�
void draw()
{
    system("cls");  // ȭ�� �ʱ�ȭ

    printf("Score: %d\n", score);

    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            if (i == playerY && j == playerX)
            {
                printf("%c", player);  // �÷��̾� ��ġ ���
            }
            else
            {
                int isObstacle = 0;  // ��ֹ� ���� Ȯ��
                for (int k = 0; k < MAX_OBSTACLES; k++)
                {
                    if (obstacles[k][0] == j && obstacles[k][1] == i)
                    {
                        printf("|");  // ��ֹ� ���
                        isObstacle = 1;
                        break;
                    }
                }
                if (!isObstacle)
                {
                    if (i == HEIGHT - 1)
                    {
                        printf("_");  // �ٴ� ���
                    }
                    else
                    {
                        printf(" ");  // �� ���� ���
                    }
                }
            }
        }
        printf("\n");
    }
}

// ����� �Է� ó�� �Լ�
void input()
{
    if (_kbhit())   // Ű���� �Է� ����
    {
        switch (_getch())
        {
        case 'a':
            if (playerX > 0) playerX--;  // ���� �̵�
            break;
        case 'd':
            if (playerX < WIDTH - 1) playerX++;  // ������ �̵�
            break;
        }
    }
}

// ���� ���� ó�� (��ֹ� �̵� �� �浹 üũ)
void logic()
{
    for (int i = 0; i < MAX_OBSTACLES; i++)
    {
        obstacles[i][1]++;  // ��ֹ� �Ʒ��� �̵�
        if (obstacles[i][1] >= HEIGHT)
        {
            obstacles[i][0] = rand() % WIDTH;  // ���ο� ��ġ���� ��ֹ� ����
            obstacles[i][1] = 0;  // y��ǥ �ʱ�ȭ
            score++;  // ���� ����
        }

        // �÷��̾�� ��ֹ� �浹 üũ
        if (obstacles[i][0] == playerX && obstacles[i][1] == playerY)
        {
            exitGame = 1;  // �浹 �� ���� ����
        }
    }
}

// ���� �Լ�
int main()
{
    startScreen();  // ���� ���� ȭ�� ȣ��
    setup();  // ���� �ʱ�ȭ
    while (!exitGame)  // ���� ���� ������ ������ ������ �ݺ�
    {
        draw();  // ȭ�� �׸���
        input();  // ����� �Է� ó��
        logic();  // ���� ���� ó��
        Sleep(200);  // ���� �ӵ� ����
    }

    printf("Game Over! Final Score: %d\n", score);  // ���� ���� �޽��� ���
    return 0;
}
