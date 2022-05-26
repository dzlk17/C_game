#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <winuser.h>


#define M 30
#define N 40 
#define PLAYER 8
#define KEY_LEFT 75
#define KEY_RIGHT 77

int player_left, player_right;
int Game  = 0;

int random()
{
    return rand() % (N-PLAYER-2);
}

void game_over()
{
    system("Cls");
    printf("\n\n\nGame over!");
    Sleep(1500);
    Game = 1;
}

void bar(int field[M][N])
{
    int left = random(), right = random();
    while(N - 2 - (left + right) < 10)
    {
        right = random();
    }
    for (int i = 0; i < N; i++)
    {
        if (i < left || i > N-right)
            field[1][i] = 2;   
    }
}

void check(int field[M][N], int c)
{
    for (int i = 1; i < N-1; i++)
    {
        if(c+2 == M-2)
        {
            if(field[c+2][i] == 1 && field[c+1][i] == 2)
            {
                game_over();
                return;
            }
            if(field[c+2][i] == 0 && field[c+1][i] == 2)
            {
                field[c+2][i] = field[c+1][i];
                field[c+1][i] = 0;
            }
        }
        else if(c+2 < M-2)
        {
            field[c+2][i] = field[c+1][i];
            field[c+1][i] = 0;
        }
        else if(field[c][i] == 2 )
            field[c][i] = 0;
        else if(field[c+1][i] == 2 )
            field[c+1][i] = 0;
    }
    for (int i = 1; i < N-1; i++)
    {
        field[M-1][i] = 2;
    }

}


void play_round(int field[M][N])
{   
    static int c = 0, c2 = 15;
    int tab[N];
    if(!c || !c2)
        bar(field);
    check(field, c);
    check(field, c2);
    c++;
    c2++;
    c = c%(M-2);
    c2 = c2%(M-2);
}

void move(int field[M][N])
{   
    int c = 0;
    if(_kbhit()){
        switch((c = _getch())) 
        {
            case KEY_LEFT:
                if(player_left > 1)
                {
                    field[M-2][player_right] = 0;
                    player_left--;
                    player_right--;
                    field[M-2][player_left] = 1;
                }
                break;
            case KEY_RIGHT:
                if(player_right < N-2)
                {
                    field[M-2][player_left] = 0;
                    player_left++;
                    player_right++;
                    field[M-2][player_right] = 1;
                }
                break;
        }
    }
}

void initialize(int field[M][N])
{
    player_left = (N - PLAYER-1) / 2;
    player_right = (N + PLAYER) / 2;
    for(int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {   
            if( i == M-2 && j > player_left && j < (N + PLAYER) / 2)
                field[i][j] = 1; 
            else if (i == 0 || j == 0 || i == M-1 || j == N-1)
                field[i][j] = 2;
            else
                field[i][j] = 0;
        }
    }
}

void restart_screen()
{
    HANDLE h_output = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    position.X = 0;
    position.Y = 0;
    SetConsoleCursorPosition(h_output,position);
}

void print(int field[M][N])
{
    for (int i = 0; i < M; i++)
    {
        for(int j = 0; j < N; j++)
        {
            if (field[i][j] == 2)
                printf("X");
            else if (field[i][j] == 0)
                printf(" ");
            else if (field[i][j] == 1)
                printf("-");
        }
        printf("\n");
    }

}


int main()
{
    int field[M][N];
    srand(time(0));
    initialize(field);
    Sleep(20);
    int counter = 100;
    while(Game == 0)
    {
        if(!counter)
        {
            play_round(field);
            print(field);
            restart_screen();
            counter = 150;
            Sleep(40);
        }
        move(field);
        counter--;
    }
    return 0;
}
