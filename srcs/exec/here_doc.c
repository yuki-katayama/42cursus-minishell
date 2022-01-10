/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:21:16 by nyokota           #+#    #+#             */
/*   Updated: 2021/12/03 17:30:20 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "expansion.h"
#include "libft.h"
#include "utils.h"

int	here_doc(char *str, t_env *env, int read_fd)
{
	int		pipe_fd[PIPE];
	int		tmp_fd;
	char	*line;
	char	*expand_str;

	line = NULL;
	tmp_fd = xdup(READ);
	xdup2(read_fd, READ);
	xpipe(pipe_fd);
	while (42)
	{
		line = readline("> ");
		if (!line || !ft_strncmp(str, line, ft_strlen(str) + 1))
			break ;
		ft_putendl_fd(expand_str = expand_env(env, line), pipe_fd[WRITE]);
		free(expand_str);
		free(line);
	}
	xclose(pipe_fd[WRITE]);
	free(line);
	xdup2(tmp_fd, read_fd);
	return (pipe_fd[READ]);
}
