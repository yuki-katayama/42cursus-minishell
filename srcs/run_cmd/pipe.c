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
	return ("");
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
			.key = ft_strdup(*envp),
			.value = ft_strdup(++str)
		};
		++envp;
		cur = &(*cur)->next;
	}
	*cur = malloc(sizeof(**cur));
	**cur = (t_env)
		{
			.key = ft_strdup("TEST"),
			.value = ft_strdup("bbbbb   aaaa")
		};
	return (head);
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
	while (str && str[len])
		++len;
	return (len);
}

void	ft_puts(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
}

char	*ft_strdup(const char *str)
{
	char	*ret;
	size_t	idx;

	ret = malloc(sizeof(*ret) * (ft_strlen(str) + 1));
	idx = 0;
	while (*str)
		ret[idx++] = *str++;
	ret[idx] = '\0';
	return (ret);
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

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *)str);
		++str;
	}
	if (!c)
		return ((char *)str);
	return (NULL);
}

static void	start_with_dollar(char **str, char **start, t_env *env, size_t *len)
{
	int		c;
	char	*stoper;

	stoper = "\"'$";
	*start = ++*str;
	while (**str && !ft_strchr(stoper, **str))
		++*str;
	c = **str;
	**str = '\0';
	*start = msh_get_env(*start, env);
	*len = ft_strlen(*start);
	**str = c;
}
//cat test$TEST$TEST
static char	*expand_env_helper(char *str, size_t idx, t_env *env)
{
	char	*ret;
	char	*start;
	size_t	len;

	if (!*str)
	{
		ret = malloc(sizeof(*ret) * (idx + 1));
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
//$TEST-> "aaa aaa bbb" aaa aaa bbb
static t_token	*split_env(t_token *token, t_env *env)
{
	char	*str;
	char	*start;
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
	{
		str = skip(str);
		start = str;
		str = skip_until_c(str, ' ');
		*cur = malloc(sizeof(**cur));
		(*cur)->str = msh_substr(start, str);
		(*cur)->kind = token->kind;
		(*cur)->group = token->group;
		cur = &(*cur)->next;
	}
	*cur = next;
	free(token->str);
	free(token);
	return (ret);
}
static int	is_marge(t_token *cur, t_token *next)
{
	return (cur->group == next->group && !(cur->status == ST_SP && next->status == ST_SP));
}
//aaa"bbb"
void	marge_token_helper(t_token **token)
{
	char	*tmp_str;

	while (*token && (*token)->next)
	{
		if (is_marge(*token, (*token)->next))
		{
			tmp_str = ft_strjoin((*token)->str, (*token)->next->str);
			free((*token)->next->str);
			(*token)->next->str = tmp_str;
			free((*token)->str);
			free(*token);
			*token = (*token)->next;
		}
		else
			token = &(*token)->next;
	}
}
void	marge_token(t_node *node)
{
	marge_token_helper(&node->cmd);
	marge_token_helper(&node->input);
	marge_token_helper(&node->output);
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

int	here_doc(char *str, int read, t_env *env)
{
	int	pipe_fd[PIPE];
	int	tmp_fd;
	char *line;

	tmp_fd = dup(READ);
	dup2(read, READ);
	pipe(pipe_fd);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(str, line))
			break ;
		if (line)
			ft_puts(expand_env_helper(line, 0, env), pipe_fd[WRITE]);
		free(line);
	}
	close(pipe_fd[WRITE]);
	free(line);
	dup2(tmp_fd, read);
	return (pipe_fd[READ]);
}

int	open_input(t_token *token, int read_fd, t_env *env)
{
	int	ret;

	ret = -1;
	while (token)
	{
		if (ret != -1)
			close(ret);
		if (token->kind == TK_RI)
			ret = open(token->str, O_RDONLY);
		if (token->kind == TK_DRI)
			ret = here_doc(token->str, read_fd, env);
		token = token->next;
	}
	return (ret);
}

int	open_output(t_token *token)
{
	int	ret;

	ret = -1;
	while (token)
	{
		if (ret != -1)
			close(ret);
		if (token->kind == TK_RO)
			ret = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
		if (token->kind == TK_DRO)
			ret = open(token->str, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
		token = token->next;
	}
	return (ret);
}


void	child_process(int *pipe_fd, t_node *node, char **path, t_env *env, int read_fd)
{
	int	output_fd;
	int	input_fd;

	close(pipe_fd[READ]);
	expand_env(&node->cmd, env);
	expand_env(&node->input, env);
	expand_env(&node->output, env);
	marge_token(node);
	if (node->input)
		dup2(input_fd = open_input(node->input, read_fd, env), READ), close(input_fd);
	if (node->output)
		dup2(output_fd = open_output(node->output), WRITE), close(output_fd);
	else if (node->next)
		dup2(pipe_fd[WRITE], WRITE);
	close(pipe_fd[WRITE]);
	if (node->cmd)
		execve(format_path(node->cmd->str, path), format_command(node->cmd, 0), NULL);
}

void	adult_process(int *pipe_fd, t_node *node)
{
	//if (!node->next)
		wait(NULL);
	close(pipe_fd[WRITE]);
	dup2(pipe_fd[READ], READ), close(pipe_fd[READ]);
}

void	multi_level_pipe(t_node *node, t_env *env)
{
	int		pipe_fd[PIPE];
	pid_t	pid;
	char	**path;
	int		read_fd;

	read_fd = dup(READ);
	path =  ft_split(msh_get_env("PATH", env), ':');
	while (node)
	{
		pipe(pipe_fd);
		pid = fork();
		if (!pid)
			child_process(pipe_fd, node, path, env, read_fd);
		else
			adult_process(pipe_fd, node);
		node = node->next;
	}
	dup2(READ, read_fd), close(READ);
	//free split
}