#include "../../includes/pipe.h"
#include "../../libft/libft.h"

char	*msh_get_env(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return ("");
}
