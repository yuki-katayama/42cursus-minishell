#include "../../includes/pipe.h"
#include "../../libft/libft.h"

char	*format_path(char *cmd, char **path)
{
	char		*ret;
	char		*tmp;
	struct stat	sb;

	tmp = ft_strjoin("/", cmd);
	while (path)
	{
		ret = ft_strjoin(*path, tmp);
		if (!stat(ret, &sb))
			if (S_ISREG(sb.st_mode))
				return (free(tmp), ret);
		free(ret);
		++path;
	}
	return (NULL);
}

char	**format_command(t_token *token, size_t idx)
{
	char	**ret;

	if (!token)
	{
		if(!(ft_malloc_pp((void ***)&ret, sizeof(char **) * (idx + 1))))
			return (NULL);
		if (ret)
			ret[idx] = NULL;
		return (ret);
	}
	ret = format_command(token->next, idx + 1);
	if (ret)
		ret[idx] = token->str;
	return (ret);
}
