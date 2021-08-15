#include "../../includes/utils.h"
#include "../../libft/libft.h"

int	msh_atoi(const char *str)
{
	long int	res;
	int			negative;

	res = 0;
	negative = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = negative * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
		if (res > (long int)INT_MIN * -1 && negative == -1)
			return (0);
		if (res > INT_MAX && negative == 1)
			return (-1);
	}
	return ((int)res * negative);
}
