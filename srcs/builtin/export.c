#include "../../includes/builtin.h"
#include "../../includes/pipe.h"
#include "../../libft/libft.h"
#include "../../includes/utils.h"

static t_env	*get_last_env(t_env *env)
{
	t_env	*last;

	if (!env)
		return (NULL);
	last = env;
	while (last->next)
		last = last->next;
	return (last);
}

static t_env	*get_key_env(char *key, t_env *env)
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

/*
** description:
**	keyが存在し、valueに変更があれば、return 2
**	keyが存在し、valueに変更がなければ、return 0
**	keyが存在しなければ、return 1
*/
static int	is_replace_or_add(char *key, t_env *env)
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

static void	set_env(int set_mode, t_env *env, char *key, char *value)
{
	t_env	*add;

	if (set_mode == 1)
	{
		if (!(ft_malloc_p((void **)&add, sizeof(t_env))))
			return ;
		add->key = ft_strdup(key);
		add->value = ft_strdup(value);
		get_last_env(env)->next = add;
		add->next = NULL;
	}
	else if (set_mode == 2)
		get_key_env(key, env)->value = value;
}

int	bi_export(char **argv, t_env *env)
{
	char	*key;
	char	*value;
	int		set_mode;

	if (!ft_strchr(*argv, '='))
		return (1);
	while (argv && *argv)
	{
		key = msh_substr(*argv, ft_strchr(*argv, '='));
		value = msh_substr(ft_strchr(*argv, '=') + 1, \
							(*argv + ft_strlen(*argv)));
		set_mode = is_replace_or_add(key, env);
		if (set_mode)
			set_env(set_mode, env, key, value);
		argv++;
	}
	return (0);
}
