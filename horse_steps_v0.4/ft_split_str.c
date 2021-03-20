#include <stdlib.h>
#include "ft_std.h"

int	if_space(char simb)
{
	if (simb == ' ' || simb == '\n' || simb == '\t' || simb == '\0')
		return (1);
	return (0);
}

int	words_counter(char *str)
{
	int counter;
	int i;

	counter = 0;
	i = 0;
	while (str[i])
	{
		if (!if_space(str[i]) && if_space(str[i+1]))
			counter++;
		i++;
	}
	return (counter);
}

char	**ft_split_whitespaces(char *str)
{
	int symb_c;
	char **words_array;
	int counter;

	symb_c = 0;
	counter = words_counter(str);
	words_array = (char**)malloc(sizeof(char*) * counter + 1);
	if (words_array)
	{
		while (*str)
		{
			if (!if_space(*str) && if_space(*(str+1)))
			{
				*words_array++ = ft_strncpy(str - symb_c, symb_c + 1);
				symb_c = 0;
			}
			else if (!if_space(*str) && !if_space(*(str+1)))
				symb_c++;
			str++;
		}
		*words_array = NULL;
		return (words_array - counter);
	}
	return (NULL);
}
void	ft_putdarray(char **darray)
{
	if (darray)
	{
		while (*darray)
		{
			ft_putstr(*darray++);
			ft_putchar('\n');
		}
	}
}