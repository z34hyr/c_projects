#include <unistd.h>
#include <stdlib.h>

void	ft_putchar(char c)
{
	int res = write(1, &c, 1);
	(void)res;
}

void	ft_putstr(char *str)
{
	while (*str)
	{
		ft_putchar(*str);
		str++;
	}
}

void	ft_itoa(int number)
{
	if (number < 0)
	{
		ft_putchar('-');
		number *= -1;
	}
	if (number / 10 != 0)
		ft_itoa(number / 10);
	ft_putchar((char)(number % 10 + 48));
}

char	*ft_strncpy(char *str, int count)
{
	char	*result;
	int	i;

	i = 0;
	result = NULL;
	result = (char*)malloc(sizeof(char) * (count + 1));
	if (result)
	{
		while (i < count && str[i] != '\0')
		{
			result[i] = str[i];
			i++;	
		}
		result[i] = '\0';
	}
	return (result);
}
