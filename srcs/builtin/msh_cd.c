#include "../../libft/libft.h"
#include "../../includes/builtin.h"

int	msh_cd(char *path)
{
	path = ft_spaceskip(path);
	if (*path == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd HOME: ");
	}
	else
	{
		msh_pwd();
		if (chdir(path) != 0)
			perror("cd: ");
		msh_pwd();
	}
	return (0);
}
