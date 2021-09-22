#include "../../libft/libft.h"
#include "../../includes/builtin.h"

int	bi_cd(char *path)
{
	path = ft_spaceskip(path);
	if (*path == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd HOME: ");
	}
	else
	{
		bi_pwd();
		if (chdir(path) != 0)
			perror("cd: ");
		bi_pwd();
	}
	return (0);
}
