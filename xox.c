#include <stdio.h>
#include <stdlib.h>

struct Vector2{int x,y;};

struct Vector2 winConditions[8][3] = {
    {{0,0},{1,0},{2,0}},
    {{0,1},{1,1},{2,1}},
    {{0,2},{1,2},{2,2}},
    {{0,0},{0,1},{0,2}},
    {{1,0},{1,1},{1,2}},
    {{2,0},{2,1},{2,2}},
    {{0,0},{1,1},{2,2}},
    {{2,0},{1,1},{0,2}}
};

char area[3][3];

char players[] = {'X','O'};
int currentPlayer;
int* pCurrentPlayer = &currentPlayer;

void clearTerminal()
{
    system("@cls||clear");
}

void init()
{
    clearTerminal();
    area[0][0] = ' ';
    area[0][1] = ' ';
    area[0][2] = ' ';
    area[1][0] = ' ';
    area[1][1] = ' ';
    area[1][2] = ' ';
    area[2][0] = ' ';
    area[2][1] = ' ';
    area[2][2] = ' ';
    *pCurrentPlayer = 0;
}

int printArea(struct Vector2* wins)
{   
    int flag = 0;
    int* pFlag = &flag;
    printf("\033[0;34m  0 1 2\033[0m\n");
    for (int y = 0; y < 3; y++)
    {
        printf("\033[0;33m%d\033[0m", y);
        for (int x = 0; x < 3; x++)
        {
            printf("|");
            if (wins != NULL)
            {
                if ((x == (*wins).x && y == (*wins).y) || (x == (*(wins+1)).x && y == (*(wins+1)).y) || (x == (*(wins+2)).x && y == (*(wins+2)).y))
                {
                    printf("\033[0;32m");
                }
            }
            if (area[y][x] == ' ')
            {
                *pFlag = 1;
                printf("\033[0;42m");
            }
            printf("%c\033[0m", area[y][x]);
        }
        printf("|\n");
    }
    printf("____________\n\n");
    return *pFlag;
}

void nextPlayer()
{
    *pCurrentPlayer = (*pCurrentPlayer + 1) % 2;
}

void makeMove()
{
    struct Vector2 move;
    while (1)
    {
        printf("Type \033[1;34mx\033[0m for player \033[1;35m%c\033[0m: ", players[currentPlayer]);
        scanf("%d", &move.x);
        printf("Type \033[1;33my\033[0m for player \033[1;35m%c\033[0m: ", players[currentPlayer]);
        scanf("%d", &move.y);

        if (move.x >= 0 &&  move.x <= 2 && move.y >= 0 &&  move.y <= 2 && area[move.y][move.x] == ' ')
        {
            area[move.y][move.x] = players[currentPlayer];
            nextPlayer();
            clearTerminal();
            return;
        }

        clearTerminal();
        printArea(NULL);
        printf("\033[0;31mInvalid move!\033[0m\n");
    }
}

int CheckWin()
{
    struct Vector2* pCondition = (struct Vector2*) malloc(3 * sizeof(struct Vector2));
    for (int i = 0; i < 8; i++)
    {
        pCondition[0] = winConditions[i][0];
        pCondition[1] = winConditions[i][1];
        pCondition[2] = winConditions[i][2];
        
        if (area[(*pCondition).y][(*pCondition).x] != ' ' && area[(*(pCondition+1)).y][(*(pCondition+1)).x] != ' ' && area[(*(pCondition+2)).y][(*(pCondition+2)).x] != ' ')
        {
            if (area[(*pCondition).y][(*pCondition).x] == area[(*(pCondition+1)).y][(*(pCondition+1)).x] && area[(*pCondition).y][(*pCondition).x] == area[(*(pCondition+2)).y][(*(pCondition+2)).x])
            {
                printArea(pCondition);
                printf("\033[1;32m%c Won!\033[0m\n", area[(*pCondition).y][(*pCondition).x]);
                free(pCondition);
                return 1;
            }
        }
    }
    
    free(pCondition);
    return 0;
}

int TryRestart()
{
    char decision;
    printf("Do you want to play again?\n(Y/N): ");
    scanf("%s", &decision);
    if (decision == 'y' || decision == 'Y')
    {
        init();
        return 1;
    }
    else
    {
        printf("okey cya!\n");
        return 0;
    }
}

int main()
{
    init();
    while (1)
    {
        if (!printArea(NULL))
        {
            printf("\033[1;32mIts a draw!\033[0m\n");
            if (!TryRestart()) break;
            printArea(NULL);
        }
        makeMove();
        if (CheckWin())
        {
            if (!TryRestart()) break;
        }
    }
    return 0;
}