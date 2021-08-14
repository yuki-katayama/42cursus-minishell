#include "../../includes/builtin.h"

int	ft_ctrl_d(char *str)
{
	printf("\033[%dA%s\n", 1, str);
	return (0);
}

int	ft_input_exit(char *command)
{
	(void)command;
	return (0);
}

void	ft_exit(char *str, int (*ft_exit)(char *))
{
	uint8_t	status;

	status = ft_exit(str);
	exit(status);
}
