#include "../../includes/pipe.h"
#include "../../libft/libft.h"

int bi_env(t_env *env)
{
	t_env *cur;

	cur = env;
	while(cur)
	{
		ft_putstr_fd(cur->key, STDOUT_FILENO);
		ft_putchar_fd('=', STDOUT_FILENO);
		ft_putendl_fd(cur->value, STDOUT_FILENO);
		cur = cur->next;
	}
	return (0);
}