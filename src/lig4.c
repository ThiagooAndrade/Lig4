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

#define line 6
#define column 7
#define WHITE_COLOR (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
#define RED_COLOR FOREGROUND_RED
#define BLUE_COLOR FOREGROUND_BLUE

int jogador = 1;

void montarTabuleiro(char tabuleiro[line][column], HANDLE hConsole, int game, int jogador1vitories, int jogador2vitories);
void jogo(char tabuleiro[line][column], int jogador, int column_select);
bool verificaJogada(char tabuleiro[line][column], int column_select);
bool verificaVitoria(char tabuleiro[line][column], char jogador);
void setConsoleTextColor(HANDLE hConsole, char color);

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int column_select, moves = 0, game = 1, jogador1vitories = 0, jogador2vitories = 0;
    char tabuleiro[line][column];
    char choice = 's';

    // enquanto choice for igual a 'S' ou 's' o jogo se reiniciará
    while ((choice == 'S' || choice == 's'))
    {
        // monta as matrizies e os vetores
        for (int l = 0; l < 6; l++)
        {
            for (int c = 0; c < 7; c++)
            {
                tabuleiro[l][c] = ' ';
            }
        }
        while (1)
        {
            system("cls");
            // monta o tabuleiro
            montarTabuleiro(tabuleiro, hConsole, game, jogador1vitories, jogador2vitories);
            // recolhe a resposta do jogador
            printf("Jogador %d choice a posicao onde deseja jogar: ", jogador);
            scanf("%d", &column_select);
            fflush(stdin);
            // verifica se a jogada foi feita corretamente
            if (verificaJogada(tabuleiro, column_select))
            {
                jogo(tabuleiro, jogador, column_select);
                moves++;
                // verifica se o jogador 1 ganhou
                if (verificaVitoria(tabuleiro, 'X'))
                {
                    jogador1vitories++;
                    game++;
                    system("cls");
                    montarTabuleiro(tabuleiro, hConsole, game, jogador1vitories, jogador2vitories);
                    printf("\nO jogador %d venceu o jogo!!\n\n", jogador);
                    sleep(2);
                    printf("Desejam jogar novamente? S/N: ");
                    scanf(" %c", &choice);
                    fflush(stdin);
                    Sleep(500);

                    if (choice == 'S' || choice == 's')
                    {
                        break;
                    }
                    else
                    {
                        exit(EXIT_SUCCESS);
                    }
                }
                // verifica se o jogador 2 ganhou
                if (verificaVitoria(tabuleiro, 'O'))
                {
                    jogador2vitories++;
                    game++;
                    system("cls");
                    montarTabuleiro(tabuleiro, hConsole, game, jogador1vitories, jogador2vitories);
                    printf("\nO jogador %d venceu o jogo!!\n\n", jogador);
                    sleep(2);
                    printf("Desejam jogar novamente? S/N: ");
                    scanf("%c", &choice);
                    fflush(stdin);
                    Sleep(500);
                    if (choice == 'S' || choice == 's')
                    {
                        break;
                    }
                    else
                    {
                        exit(EXIT_SUCCESS);
                    }
                }
                // se foi o jogador 1 que jogou o próximo será o jogador 2
                // se foi o jogador 2 que jogou o próximo será o jogador 1
                jogador = (jogador == 1) ? 2 : 1;
            }

            // empate do jogo
            if (moves == 42)
            {
                game++;
                system("cls");
                montarTabuleiro(tabuleiro, hConsole, game, jogador1vitories, jogador2vitories);
                sleep(1);
                printf("\n\nO jogo empatou!!\n\n");
                printf("Desejam jogar novamente? S/N: ");
                scanf("%c", &choice);
                fflush(stdin);
                Sleep(500);
                // se o jogador digitar 'S' ou 's' o jogo reiniciará
                if (choice == 'S' || choice == 's')
                {
                    break;
                }
                else
                {
                    exit(0);
                }
            }
        }
    }
    return 0;
}

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

bool verificaJogada(char tabuleiro[line][column], int column_select)
{
    if (column_select > 7 || column_select < 1)
    {
        return false;
    }

    return (tabuleiro[0][column_select - 1] == ' ');
}

bool verificaVitoria(char tabuleiro[line][column], char jogador)
{
    // Verifica na vertical
    for (int i = 0; i < 7; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            if (tabuleiro[x][i] == jogador && tabuleiro[x + 1][i] == jogador && tabuleiro[x + 2][i] == jogador && tabuleiro[x + 3][i] == jogador)
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
            if (tabuleiro[i][x] == jogador && tabuleiro[i][x + 1] == jogador && tabuleiro[i][x + 2] == jogador && tabuleiro[i][x + 3] == jogador)
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
            if (tabuleiro[i][x] == jogador && tabuleiro[i + 1][x + 1] == jogador && tabuleiro[i + 2][x + 2] == jogador && tabuleiro[i + 3][x + 3] == jogador)
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
            if (tabuleiro[i][x] == jogador && tabuleiro[i + 1][x - 1] == jogador && tabuleiro[i + 2][x - 2] == jogador && tabuleiro[i + 3][x - 3] == jogador)
            {
                return true;
            }
        }
    }

    return false;
}

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