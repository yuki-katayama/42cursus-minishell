#include "../../includes/pipe.h"
#include "../../libft/libft.h"

char	*msh_get_env(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strncmp(key, env->key, ft_strlen(env->key) + 1))
			return (env->value);
		env = env->next;
	}
	return ("");
}

t_env	*msh_del_env(char *key, t_env *env)
{
	t_env	*cur;
	t_env	*prev;

	prev = NULL;
	cur = env;
	while (cur)
	{
		if (ft_strncmp(key, cur->key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = cur->next;
			else
				env = cur->next;
			cur = NULL;
			break ;
		}
		prev = cur;
		cur = cur->next;
	}
	return (env);
}
