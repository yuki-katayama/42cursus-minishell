#include "../../includes/pipe.h"
#include "../../includes/builtin.h"
#include "../../includes/utils.h"
#include "../../includes/lexer.h"
#include "../../includes/expansion.h"

#include "../../libft/libft.h"

int	bi_echo(char **splited, t_env *env)
{
	(void)env;
	splited++;
	while (*splited)
	{
		*splited = ft_chardel(*splited, "\"'");
		ft_putstr_fd(*splited, STDOUT_FILENO);
		free(*splited);
		splited++;
		if (splited != NULL)
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	free(*splited);
	ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
