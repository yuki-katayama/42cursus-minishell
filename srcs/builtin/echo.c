#include "../../includes/pipe.h"
#include "../../includes/builtin.h"
#include "../../includes/utils.h"
#include "../../includes/lexer.h"
#include "../../includes/expansion.h"

#include "../../libft/libft.h"

int	bi_echo(char **argv, t_env *env)
{
	(void)env;
	while (*argv)
	{
		ft_putstr_fd(*argv, STDOUT_FILENO);
		free(*argv);
		argv++;
		if (argv != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	free(*argv);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
