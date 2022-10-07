#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

#define height 25
#define width 80

char snowArray[height][width + 1];

void initSnowArray()
{   
    for(int i = 0; i < width; i++)
        snowArray[0][i] = ' ';
    snowArray[0][width] = '\0';
    for(int i = 1; i < height; i++)
        sprintf(snowArray[i], snowArray[0]);
}

void showSnowArray()
{   
    for(int i = 0; i < height; i++)
        printf("%s\n", snowArray[i]);   
}

void newSnow()
{
    srand(time(NULL));
    for(int i = 0; i < width; i++)
        if(rand()%12 == 1)
            snowArray[0][i] = '*';     
}

void moveSnow()
{
    int dx;
    for(int j = height - 1; j >= 0; j--)
        for(int i = 0; i < width; i++)
            if(snowArray[j][i] == '*')
            {
                snowArray[j][i] = ' ';
                dx = 0;
                if(rand()%10 < 1) dx++;
                if(rand()%10 < 1) dx--;
                dx = dx + i;
                if((dx >= 0) && (dx < width) && (j + 1 < height))
                    snowArray[j + 1][dx] = '*';
            }   
}

void setCursor(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int main(int argc, char const *argv[])
{
    initSnowArray();
    do
    {
        setCursor(0,0);
        
        moveSnow();
        newSnow();
        showSnowArray();

        Sleep(100);
    }
    while (GetKeyState(VK_ESCAPE) >= 0);
    
    system("cls");

    return 0;
}

