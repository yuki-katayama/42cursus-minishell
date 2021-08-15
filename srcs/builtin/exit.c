#include "../../includes/builtin.h"
#include "../../libft/libft.h"

int	ft_ctrl_d(char *str)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putendl_fd(str, STDOUT_FILENO);
	return (0);
}

/*
** exit + commandで、statusが変わるので後で処理を追加する。
*/

int	ft_input_exit(char *command)
{
	(void)command;
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (0);
}

void	ft_exit(char *str, int (*ft_exit)(char *))
{
	uint8_t	status;

	status = ft_exit(str);
	exit(status);
}
