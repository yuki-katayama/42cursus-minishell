#include "../../libft/libft.h"
#include "../../includes/builtin.h"

int	bi_cd(char *str)
{
	str = ft_spaceskip(str);
	if (*str == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd HOME: ");
	}
	else
	{
		bi_pwd();
		if (chdir(str) != 0)
			perror("cd: ");
		bi_pwd();
	}
	return (0);
}
