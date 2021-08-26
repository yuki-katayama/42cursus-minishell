#include "../../includes/builtin.h"

void ft_pwd(void)
{
	char path[300] = {0};

	if (!getcwd(path, sizeof(path)))
		perror("pwd: ");
	
	printf("%s\n", path);
}
