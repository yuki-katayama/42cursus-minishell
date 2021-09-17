#include "../../libft/libft.h"
#include "../../includes/builtin.h"

void	bi_ctrl_d(char *str)
{
	ft_putstr_fd("\033[0A\n", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(0);
}
