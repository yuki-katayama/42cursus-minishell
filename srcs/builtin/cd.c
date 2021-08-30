#include "../../libft/libft.h"
#include "../../includes/builtin.h"

int	ft_cd(char *str)
{
	str = ft_spaceskip(str);
	if (*str == '\0')
	{
		if (chdir(getenv("HOME")) != 0)

			perror("cd HOME: ");
	}
	else
	{
		if (chdir(str) != 0)
			perror("cd: ");
	}
	return (1);
}
