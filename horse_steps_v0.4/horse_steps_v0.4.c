#include <unistd.h>
#include <stdlib.h>
#include "ft_std.h"
#include <assert.h>
#include <time.h>
#include <stdio.h>

const int SIZE = 15;
const int step_x_fix[] = { 1,1,-1,-1, 2,2,-2,-2};
const int step_y_fix[] = {-2,2,-2, 2,-1,1,-1, 1};

/* 
print an array
*/
void	print_int_array(int arr[], int size)
{
	int i;

	i = 0;
	ft_putstr("An array: ");
	while (i < size)
	{
		ft_itoa(arr[i]);
		ft_putchar(' ');
		i += 1;
	}
	ft_putchar('\n');
}

/*
returns true if this option is possible
*/
int		can_I_go(int **chessdesk, int i_cur, int j_cur, int opt)
{
	if (i_cur + step_x_fix[opt] >= 0 && \
    i_cur + step_x_fix[opt] < SIZE && \
    j_cur + step_y_fix[opt] >= 0 && \
    j_cur + step_y_fix[opt] < SIZE && \
    chessdesk[j_cur + step_y_fix[opt]][i_cur + step_x_fix[opt]] == 0)
		return (1);
	else
		return (0);
}
/*
returns number of possible next steps for current option
*/
int		num_pos_steps(int **chessdesk, int i_next, int j_next)
{
	int option;
	int sum;

	option = 0;
	sum = 0;
	while (option < 8)
	{
		if (can_I_go(chessdesk, i_next, j_next, option))
			sum += 1;
		option += 1;
	}
	return (sum);
}

void	sort_arrays(int arr1[], int arr2[])
{
	int j;
	int prom1, prom2;
	
	j = 0;
	while (j < 7)
	{
		if (arr1[j] > arr1[j+1])
		{
			prom1 = arr1[j];
			prom2 = arr2[j];
			arr1[j] = arr1[j+1];
			arr2[j] = arr2[j+1];
			arr1[j+1] = prom1;
			arr2[j+1] = prom2;
			j = 0;
		}
		else
			j += 1;
	}
}

void    accept_opt(int **chessdesk, int *i_tek, int *j_tek, int opt, int *step)
{
    *i_tek += step_x_fix[opt];
    *j_tek += step_y_fix[opt];
    assert(*i_tek < SIZE && *i_tek >= 0);
    assert(*j_tek < SIZE && *j_tek >= 0);
    *step += 1;
    chessdesk[*j_tek][*i_tek] = *step;
}

// возвращает предыдущий вариант
void    decline_opt(int **chessdesk, int *i_tek, int *j_tek, int opt, int *step)
{
    chessdesk[*j_tek][*i_tek] = 0;
    *step -= 1;
    *i_tek -= step_x_fix[opt];
    *j_tek -= step_y_fix[opt];
}



int		recursion_horse(int **chessdesk, int *i_cur, int *j_cur, int *cur_step, long *n_ent)
{
	int pos_steps[] = {0, 0, 0, 0, 0, 0, 0, 0};
	int steps_priority[] = {0, 1, 2, 3, 4, 5, 6, 7};
	int cur_opt;
	ft_putstr("current step is ");
	ft_itoa(*cur_step);
	ft_putchar('\n');
	print_desk(chessdesk);
	cur_opt = 0;
	if (*cur_step == SIZE * SIZE)
		return (1);
	*n_ent += 1;
	while (cur_opt < 8)
	{
		if (can_I_go(chessdesk, *i_cur, *j_cur, cur_opt))
		{
			pos_steps[cur_opt] = num_pos_steps(chessdesk, \
			*i_cur + step_x_fix[cur_opt], *j_cur + step_y_fix[cur_opt]);
		}
		cur_opt += 1;
	}
	cur_opt = 0;
	sort_arrays(pos_steps, steps_priority);
	print_int_array(pos_steps, 8);
	print_int_array(steps_priority, 8);
	while (cur_opt < 8)
	{
		if (can_I_go(chessdesk, *i_cur, *j_cur, steps_priority[cur_opt]))
		{
			accept_opt(chessdesk, i_cur, j_cur, steps_priority[cur_opt], cur_step);
			if (!recursion_horse(chessdesk, i_cur, j_cur, cur_step, n_ent))
			{
				decline_opt(chessdesk, i_cur, j_cur, steps_priority[cur_opt], cur_step);
				cur_opt += 1;
			}
		}
		else
		{
			ft_putstr("can't go, next try ");
			ft_itoa(steps_priority[cur_opt]);
			ft_putchar('\n');
			cur_opt += 1;
		}
		if (*cur_step == SIZE * SIZE)
			return (1);
	}
	return (0);
}

int     main(int argc, char **argv)
{
    int *i_st;
    int *j_st;
    int *cur_o;
    int *cur_s;
    int **chessdesk;
    int i, j;
    clock_t t0 = clock();
    long *rec_count;

	if (argc != 3)
	{
		ft_putstr("Wrong number of arguments - I need start position of knight!\n");
		return (-1);
	}
    i = atoi(argv[1]);
    j = atoi(argv[2]);
    i_st = &i;
    j_st = &j;
    cur_o = (int*)malloc(sizeof(int));
    *cur_o = 0;
    cur_s = (int*)malloc(sizeof(int));
    *cur_s = 1;
    rec_count = (long*)malloc(sizeof(long));
    *rec_count = 0;
    chessdesk = empty_desk(SIZE);
    chessdesk[j][i] = 1;
    ft_putstr("start point:\n");
    print_desk(chessdesk);
    recursion_horse(chessdesk, i_st, j_st, cur_s, rec_count);
    ft_putchar('\n');
    ft_itoa(*rec_count);
    ft_putchar('\n');
    clock_t tw;
    tw = clock();
    float time_in_sec = ((float)(tw - t0) / 1000000.0F );   
    printf("calc time is %.3f s\n",time_in_sec); 
}
