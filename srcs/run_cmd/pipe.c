#include "../../includes/pipe.h"
#include "../../includes/utils.h"
#include "../../includes/lexer.h"


int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	if (*s1++ != *s2++)
		return (1);
	return (!(!*s1 && !*s2));
}

char	*msh_get_env(char *key, t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(key, env->key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

static char	*sub_split(const char *start, const char *end)
{
	char	*ret;
	size_t	idx;

	ret = malloc(sizeof(char) * (end - start + 1));
	if (!ret)
		return (NULL);
	idx = 0;
	while (start != end)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}

static char	**rec_split(const char *str, const char c, size_t idx)
{
	char	**ret;
	char	*ptr;

	while (*str && *str == c)
		++str;
	if (!*str)
	{
		ret = malloc(sizeof(char *) * (idx + 1));
		if (ret)
			ret[idx] = NULL;
		return (ret);
	}
	ptr = (char *)str;
	while (*str && *str != c)
		++str;
	ptr = sub_split(ptr, str);
	if (!ptr)
		return (NULL);
	ret = rec_split(str, c, idx + 1);
	if (ret)
		ret[idx] = ptr;
	else
		free(ptr);
	return (ret);
}

char	**ft_split(const char *s, const char c)
{
	if (!s)
		return (NULL);
	return (rec_split((char *)s, c, 0));
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		++len;
	return (len);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*ret;
	size_t	idx;

	if (!s1 || !s2)
		return (NULL);
	ret = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	idx = 0;
	while (*s1)
		ret[idx++] = *s1++;
	while (*s2)
		ret[idx++] = *s2++;
	ret[idx] = '\0';
	return (ret);
}



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
		ret = malloc(sizeof(*ret) * (idx + 1));
		if (ret)
			ret[idx] = NULL;
		return (ret);
	}
	ret = format_command(token->next, idx + 1);
	if (ret)
		ret[idx] = token->str;
	return (ret);
}

int	open_input(t_token *token)
{
	int	ret;

	while (token)
	{
		if (token->kind == TK_RI)
			ret = open(token->str, O_RDONLY);
		if (token->kind == TK_DRI)
			/*ret = here_doc(token->str)*/;
		token = token->next;
	}
	return (ret);
}

int	open_output(t_token *token)
{
	int	ret;

	while (token)
	{
		if (token->kind == TK_RO)
			ret = open(token->str, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
		if (token->kind == TK_DRO)
			ret = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
		token = token->next;
	}
	return (ret);
}

void	child_process(int *pipe_fd, t_node *node, char **path)
{
	int	output_fd;
	int	input_fd;

	close(pipe_fd[READ]);
	//expand_environment_variables(node);
	if (node->input)
		dup2(input_fd = open_input(node->input), READ), close(input_fd);
	if (node->output)
		dup2(output_fd = open_output(node->output), WRITE), close(output_fd);
	else if (node->next)
		dup2(pipe_fd[WRITE], WRITE);
	close(pipe_fd[WRITE]);
	execve(format_path(node->cmd->str, path), format_command(node->cmd, 0), NULL);
}

void	adult_process(int *pipe_fd, t_node *node)
{
	if (!node->next)
		wait(NULL);
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], READ), close(pipe_fd[READ]);
}

void	multi_level_pipe(t_node *node, t_env *env)
{
	int		pipe_fd[PIPE];
	pid_t	pid;
	char	**path;

	path =  ft_split(msh_get_env("PATH", env), ':');
	while (node)
	{
		pipe(pipe_fd);
		pid = fork();
		if (!pid)
			child_process(pipe_fd, node, path);
		else
			adult_process(pipe_fd, node);
		node = node->next;
	}
	//free split
}

t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	**cur;
	char	*str;

	head = NULL;
	cur = &head;
	while (*envp)
	{
		*cur = malloc(sizeof(**cur));
		str = *envp;
		while (*str && *str != '=')
			++str;
		*str = '\0';
		**cur = (t_env)
		{
			.key = *envp,
			.value = ++str
		};
		++envp;
		cur = &(*cur)->next;
	}
	return (head);
}