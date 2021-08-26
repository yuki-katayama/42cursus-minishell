#include "../../libft/libft.h"
#include "../../includes/builtin.h"

int ft_cd(char *str)
{
	char path[300] = {0};

	str = ft_spaceskip(str);
	if (*str == '\0')
	{
		if (chdir(getenv("HOME")) != 0)
			perror("cd HOME");
		printf("%s\n", getcwd(path, 300));
	}
	else
	{
		if (!getcwd(path, sizeof(path)))
			return -1;
		printf("%s: a\n", path);
		if (chdir(str) != 0)
			perror("lsh");
		if (!getcwd(path, sizeof(path)))
			return -1;
		printf("%s\n", path);
	}
	return (1);
}
