#include "../../includes/builtin.h"
#include "../../libft/libft.h"

void	ft_pwd(void)
{
	char	path[PATH_MAX];

	if (!getcwd(path, sizeof(path)))
		perror("pwd: ");
	ft_putendl_fd(path, STDOUT_FILENO);
}
