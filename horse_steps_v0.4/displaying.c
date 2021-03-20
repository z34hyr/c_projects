#include <unistd.h>
#include <stdlib.h>
#include "ft_std.h"

int **empty_desk(int size)
{
    int j;
    int i;
    int **chessdesk;

    i = 0;
    j = 0;
    chessdesk = (int**)malloc(sizeof(int*) * (size + 1));
    while (j < size)
    {
        chessdesk[j] = (int*)malloc(sizeof(int) * (size + 1));
        j++;
    }
    chessdesk[j] = NULL;
    j = 0;
    while (j < size)
    {
        while (i < size)
        {
            chessdesk[j][i] = 0;
            i++;
        }
        chessdesk[j][i] = -1;
        i = 0;
        j++;
    }
    return (chessdesk);
}

void print_desk(int **chessdesk)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (chessdesk[j])
    {
        while (chessdesk[j][i] != -1)
        {
            if (chessdesk[j][i] <= 9)
                ft_putchar(' ');
            ft_itoa(chessdesk[j][i]);
            ft_putchar(' ');
            i++;
        }
        ft_putchar('\n');
        i = 0;
        j++;
    }
}