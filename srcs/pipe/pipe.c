#include "../../includes/pipe.h"
#include "../../includes/lexer.h"
#include "../../includes/utils.h"
#include "../../includes/expansion.h"

#include "../../libft/libft.h"

char	*msh_get_env(char *key, t_env *env)
{
	if (!*key)
		return ("$");
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
		if(!(ft_malloc_p((void **)&*cur, sizeof(t_env))))
			return (NULL);
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
	if(!(ft_malloc_p((void **)&*cur, sizeof(t_env))))
		return (NULL);
	**cur = (t_env)
		{
			.key = ft_strdup("TEST"),
			.value = ft_strdup("bbbbb   aaaa")
		};
	return (head);
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
	dup2(read_fd, READ), close(read_fd);
	//free split
}
