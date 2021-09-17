#include "../../includes/pipe.h"
#include "../../includes/lexer.h"
#include "../../includes/utils.h"
#include "../../includes/expansion.h"
#include "../../libft/libft.h"

void	child_process(int *pipe_fd, t_node *node, \
						t_env *env, int read_fd)
{
	int	output_fd;
	int	input_fd;

	close(pipe_fd[READ]);
	expand_env(&node->cmd, env);
	expand_env(&node->input, env);
	expand_env(&node->output, env);
	marge_token(node);
	if (node->input)
	{
		dup2(input_fd = open_input(node->input, read_fd, env), READ);
		close(input_fd);
	}
	if (node->output)
		dup2(output_fd = open_output(node->output), WRITE), close(output_fd);
	else if (node->next)
		dup2(pipe_fd[WRITE], WRITE);
	close(pipe_fd[WRITE]);
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
	path = ft_split(msh_get_env("PATH", env), ':');
	while (node)
	{
		pipe(pipe_fd);
		pid = fork();
		if (!pid)
		{
			child_process(pipe_fd, node, env, read_fd);
			if (node->cmd)
				execve(format_path(node->cmd->str, path), \
						format_command(node->cmd, 0), NULL);
		}
		else
			adult_process(pipe_fd, node);
		node = node->next;
	}
	dup2(read_fd, READ), close(read_fd);
}
