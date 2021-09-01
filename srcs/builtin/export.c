#include "../../includes/builtin.h"
#include "../../includes/pipe.h"
#include "../../libft/libft.h"
#include "../../includes/utils.h"

t_env	*get_last_env(t_env *env)
{
	t_env	*last;

	if (!env)
		return (NULL);
	last = env;
	while (last->next)
		last = last->next;
	return (last);
}

t_env	*get_key_env(char *key, t_env *env)
{
	t_env	*env_key;

	if (!env)
		return (NULL);
	env_key = env;
	while (env_key->next)
	{
		if (env_key->key == key)
			break ;
		env_key = env_key->next;
	}
	return (env_key);
}

void	set_key_value(char *argv, char **key, char **value)
{
	*key = msh_substr(argv, ft_strchr(argv, '='));
	*value = msh_substr(ft_strchr(argv, '=') + 1, argv + ft_strlen(argv));
}

/*
** description:
**	keyが存在し、valueに変更があれば、return 2
**	keyが存在し、valueに変更がなければ、return 0
**	keyが存在しなければ、return 1
*/
int	is_replace_or_add(char *key, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!(ft_strncmp(key, tmp->key, ft_strlen(key) + 1)))
		{
			if (ft_strncmp(key, tmp->value, ft_strlen(key) + 1))
				return (2);
			return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int	bi_export(char **argv, t_env *env)
{
	t_env	*add;
	t_env	*mem;
	char	*key;
	char	*value;
	int		set_mode;

	while (++argv && *argv)
	{
		*argv = ft_chardel(*argv, "\"'");
		set_key_value(*argv, &key, &value);
		set_mode = is_replace_or_add(key, env);
		if (set_mode)
		{
			if (set_mode == 1)
			{
				if (!(ft_malloc_p((void **)&add, sizeof(t_env))))
					return (0);
				add->key = ft_strdup(key);
				add->value = ft_strdup(value);
				get_last_env(env)->next = add;
				add->next = NULL;
			}
			else if (set_mode == 2)
				get_key_env(key, env)->value = value;
		}
	}
	mem = env;
	while (mem)
	{
		printf("%s : %s\n", mem->key, mem->value);
		mem = mem->next;
	}
	return (0);
}
