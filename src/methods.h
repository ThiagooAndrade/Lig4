#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h>

#define line 6
#define column 7

#define WHITE_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define RED_COLOR FOREGROUND_RED
#define BLUE_COLOR FOREGROUND_BLUE


#ifndef METHODS_H
#define METHODS_H

void montarTabuleiro(char tabuleiro[line][column], HANDLE hConsole, int game, int jogador1vitories, int jogador2vitories)
{
    printf("\n\n");
    setConsoleTextColor(hConsole, 'w');
    printf("\t\t\t   1     2     3     4     5     6     7                          game: %d\n\n", game);
    printf("\t\t\t-------------------------------------------                       Vitorias:\n");
    printf("\t\t\t|");
    for (int l = 0; l < 6; l++)
    {

        if (l > 0)
        {
            setConsoleTextColor(hConsole, 'w');
            printf("-------------------------------------------");
            if (l == 1)
            {
                setConsoleTextColor(hConsole, 'r');
                printf("\t\tJogador 1 : %d", jogador1vitories);
                setConsoleTextColor(hConsole, 'b');
                printf("   Jogador 2 : %d", jogador2vitories);
                setConsoleTextColor(hConsole, 'w');
            }
            printf("\n");
            printf("\t\t\t|");
        }

        for (int c = 0; c < 7; c++)
        {
            if (tabuleiro[l][c] == 'X')
            {
                setConsoleTextColor(hConsole, 'r');
                printf("  %c  ", tabuleiro[l][c]);
            }
            else if (tabuleiro[l][c] == 'O')
            {
                setConsoleTextColor(hConsole, 'b');
                printf("  %c  ", tabuleiro[l][c]);
            }
            else
            {
                printf("  %c  ", tabuleiro[l][c]);
            }

            setConsoleTextColor(hConsole, 'w');
            printf("|");
            if (c == 6)
            {
                printf("\n");
                printf("\t\t\t");
            }
        }
    }
    printf("-------------------------------------------\n");
}

void jogo(char tabuleiro[line][column], int jogador, int column_select)
{
    char peca = (jogador == 1) ? 'X' : 'O';
    for (int i = 5; i >= 0; i--)
    {
        if (tabuleiro[i][column_select - 1] == ' ')
        {
            tabuleiro[i][column_select - 1] = peca;
            break;
        }
    }
}

#endif