#include "../../includes/pipe.h"
#include "../../includes/expansion.h"
#include "../../libft/libft.h"

int	here_doc(char *str, int read, t_env *env)
{
	int		pipe_fd[PIPE];
	int		tmp_fd;
	char	*line;

	line = NULL;
	tmp_fd = dup(READ);
	dup2(read, READ);
	pipe(pipe_fd);
	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(str, line))
			break ;
		if (line)
			ft_putendl_fd(expand_env_helper(line, 0, env), pipe_fd[WRITE]);
		free(line);
	}
	close(pipe_fd[WRITE]);
	free(line);
	dup2(tmp_fd, read);
	return (pipe_fd[READ]);
}
