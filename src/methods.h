/*
 *   LIG 4
 *   Thiago Miguel de Luna Andrade
 *   2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <windows.h>

#ifndef METHODS_H
#define METHODS_H

void setConsoleTextColor(HANDLE hConsole, char color)
{
    switch (color)
    {
    case 'w':
        SetConsoleTextAttribute(hConsole, WHITE_COLOR);
        break;
    case 'r':
        SetConsoleTextAttribute(hConsole, RED_COLOR);
        break;
    default:
        SetConsoleTextAttribute(hConsole, BLUE_COLOR);
        break;
    }
}

void showBoard(char tabuleiro[line][column], HANDLE hConsole, int game, int player1vitories, int player2vitories)
{
    printf("\n\n");
    setConsoleTextColor(hConsole, 'w');
    printf("\t\t\t   1     2     3     4     5     6     7                          Partida: %d\n\n", game);
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
                printf("\t\tplayer 1 : %d", player1vitories);
                setConsoleTextColor(hConsole, 'b');
                printf("   player 2 : %d", player2vitories);
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

void updateBoard(char tabuleiro[line][column], int player, int column_select)
{
    char peca = (player == 1) ? 'X' : 'O';
    for (int i = 5; i >= 0; i--)
    {
        if (tabuleiro[i][column_select - 1] == ' ')
        {
            tabuleiro[i][column_select - 1] = peca;
            break;
        }
    }
}

bool checkPlay(char tabuleiro[line][column], int column_select)
{
    if (column_select > 7 || column_select < 1)
    {
        return false;
    }

    return (tabuleiro[0][column_select - 1] == ' ');
}

bool checkVitory(char tabuleiro[line][column], char player)
{
    // Verifica na vertical
    for (int i = 0; i < 7; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (tabuleiro[x][i] == player && tabuleiro[x + 1][i] == player && tabuleiro[x + 2][i] == player && tabuleiro[x + 3][i] == player)
            {
                return true;
            }
        }
    }

    // Verifica na horizontal
    for (int i = 0; i < 6; i++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tabuleiro[i][x] == player && tabuleiro[i][x + 1] == player && tabuleiro[i][x + 2] == player && tabuleiro[i][x + 3] == player)
            {
                return true;
            }
        }
    }

    // Verifica na diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (tabuleiro[i][x] == player && tabuleiro[i + 1][x + 1] == player && tabuleiro[i + 2][x + 2] == player && tabuleiro[i + 3][x + 3] == player)
            {
                return true;
            }
        }
    }

    // Verifica na diagonal
    for (int i = 0; i < 3; i++)
    {
        for (int x = 3; x < 7; x++)
        {
            if (tabuleiro[i][x] == player && tabuleiro[i + 1][x - 1] == player && tabuleiro[i + 2][x - 2] == player && tabuleiro[i + 3][x - 3] == player)
            {
                return true;
            }
        }
    }

    return false;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
#endif