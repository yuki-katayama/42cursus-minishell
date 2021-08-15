#include "../../includes/builtin.h"
#include "../../libft/libft.h"

int	ft_ctrl_d(char *str)
{
	printf("\033[%dA%s\n", 1, str);
	return (0);
}

/*
** exit + commandで、statusが変わるので後で処理を追加する。
*/

int	ft_input_exit(char *command)
{
	(void)command;
	printf("exit\n");
	return (0);
}

void	ft_exit(char *str, int (*ft_exit)(char *))
{
	uint8_t	status;

	status = ft_exit(str);
	exit(status);
}
