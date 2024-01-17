/*
 *   LIG 4
 *   Thiago Miguel de Luna Andrade
 *   2023
 */

#include "methods.h"

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // enquanto option for igual a 'S' ou 's' o jogo se reiniciará
    while ((option == 'S' || option == 's'))
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
            clearScreen();
            // monta o tabuleiro
            showBoard(tabuleiro, hConsole, game, player1vitories, player2vitories);
            // recolhe a resposta do jogador
            printf("player %d escolha a posicao onde deseja jogar: ", player);
            scanf("%d", &column_select);
            fflush(stdin);
            // verifica se a jogada foi feita corretamente
            if (checkPlay(tabuleiro, column_select))
            {
                updateBoard(tabuleiro, player, column_select);
                moves++;
                // verifica se o jogador 1 ganhou
                if (checkVitory(tabuleiro, 'X'))
                {
                    player1vitories++;
                    game++;
                    clearScreen();
                    showBoard(tabuleiro, hConsole, game, player1vitories, player2vitories);
                    printf("\nO jogador %d venceu o jogo!!\n\n", player);
                    sleep(2);
                    printf("Desejam jogar novamente? S/N: ");
                    scanf(" %c", &option);
                    fflush(stdin);
                    Sleep(500);
                    if (option == 'S' || option == 's')
                    {
                        break;
                    }
                    else
                    {
                        exit(EXIT_SUCCESS);
                    }
                }
                // verifica se o jogador 2 ganhou
                if (checkVitory(tabuleiro, 'O'))
                {
                    player2vitories++;
                    game++;
                    clearScreen();
                    showBoard(tabuleiro, hConsole, game, player1vitories, player2vitories);
                    printf("\nO player %d venceu o jogo!!\n\n", player);
                    sleep(2);
                    printf("Desejam jogar novamente? S/N: ");
                    scanf(" %c", &option);
                    fflush(stdin);
                    Sleep(500);
                    if (option == 'S' || option == 's')
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
                player = (player == 1) ? 2 : 1;
            }

            // empate do jogo
            if (moves == 42)
            {
                game++;
                clearScreen();
                showBoard(tabuleiro, hConsole, game, player1vitories, player2vitories);
                sleep(1);
                printf("\n\nO jogo empatou!!\n\n");
                printf("Desejam jogar novamente? S/N: ");
                scanf("%c", &option);
                fflush(stdin);
                Sleep(500);
                // se o jogador digitar 'S' ou 's' o jogo reiniciará
                if (option == 'S' || option == 's')
                {
                    break;
                }
                else
                {
                    exit(EXIT_SUCCESS);
                }
            }
        }
    }
    return 0;
}