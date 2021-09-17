//$TEST-> "aaa aaa bbb" aaa aaa bbb
#include "../../includes/pipe.h"
#include "../../includes/utils.h"
#include "../../libft/libft.h"

static void	start_with_dollar(char **str, char **start, t_env *env, size_t *len)
{
	char	c;
	char	*stoper;

	stoper = "\"'$";
	*start = ++*str;
	while (**str && !ft_strchr(stoper, **str))
		++*str;
	c = **str;
	**str = '\0';
	if (!**start)
		*start = "$";
	else
		*start = msh_get_env(*start, env);
	*len = ft_strlen(*start);
	**str = c;
}

//cat test$TEST$TEST
char	*expand_env_helper(char *str, size_t idx, t_env *env)
{
	char	*ret;
	char	*start;
	size_t	len;

	if (!*str)
	{
		if (!(ft_malloc_p((void **)&ret, sizeof(char *) * (idx + 1))))
			return (NULL);
		if (ret)
			ret[idx] = '\0';
		return (ret);
	}
	if (*str == '$')
		start_with_dollar(&str, &start, env, &len);
	else
	{
		start = str;
		while (!ft_strchr("$", *str))
			++str;
		len = str - start;
	}
	ret = expand_env_helper(str, idx + len, env);
	while (len--)
		ret[idx + len] = start[len];
	return (ret);
}

static t_token	*set_env_in_token(char **str, t_token *token, t_token **cur)
{
	char	*start;

	*str = ft_spaceskip(*str);
	start = *str;
	(*str)++;
	*str = ft_untilskip(*str, ' ');
	if (!(ft_malloc_p((void **)&*cur, sizeof(t_token))))
		return (NULL);
	(*cur)->str = msh_substr(start, *str);
	(*cur)->kind = token->kind;
	(*cur)->group = token->group;
	return (*cur);
}

static t_token	*split_env(t_token *token, t_env *env)
{
	char	*str;
	t_token	*next;
	t_token	*ret;
	t_token	**cur;

	next = token->next;
	ret = NULL;
	cur = &ret;
	str = expand_env_helper(token->str, 0, env);
	free(token->str);
	token->str = str;
	while (*str)
		cur = &set_env_in_token(&str, token, cur)->next;
	*cur = next;
	free(token->str);
	free(token);
	return (ret);
}

void	expand_env(t_token **token, t_env *env)
{
	int	is_dollar;

	while (*token)
	{
		is_dollar = !!ft_strchr((*token)->str, '$');
		if ((*token)->status == ST_SP && is_dollar)
			*token = split_env(*token, env);
		if ((*token)->status == ST_DQ && is_dollar)
			(*token)->str = expand_env_helper((*token)->str, 0, env);
		token = &(*token)->next;
	}
}
