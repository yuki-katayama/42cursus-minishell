/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:20:57 by nyokota           #+#    #+#             */
/*   Updated: 2022/01/10 21:26:43 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"
#include "env.h"
#include "utils.h"
#include "libft.h"
#include "parser.h"
#include "builtin.h"
#include "exit_status.h"
#include "ft_signal.h"

static void	child_process(t_executor *executor, t_env **env, \
							int *pipe_fd)
{
	xclose(pipe_fd[READ]);
	if (executor->next)
		xdup2(pipe_fd[WRITE], WRITE);
	xclose(pipe_fd[WRITE]);
	if (setup_redirects(executor->redirect))
		exit(EXIT_FAILURE);
	if (is_builtin(executor->command))
		exit(exec_builtin(executor, env));
	if (executor->command)
		execve(format_path(executor->command->str, \
				ft_split(get_env(*env, "PATH"), ':')), \
				format_command(executor->command), NULL);
}

static void	adult_process(int *pipe_fd)
{
	xclose(pipe_fd[WRITE]);
	xdup2(pipe_fd[READ], READ);
	xclose(pipe_fd[READ]);
}

static void	adult_exec_builtin(t_executor *executor, t_env **env)
{
	if (setup_redirects(executor->redirect))
		set_exit_status(EXIT_FAILURE);
	else
	{
		set_exit_status(exec_builtin(executor, env));
		restore_fd(executor->redirect);
	}
}

static void	wait_child(pid_t *pids, size_t n)
{
	int		status;
	int		sig;
	size_t	idx;

	idx = 0;
	while (idx < n)
	{
		sig = 0;
		xwaitpid(pids[idx], &status, 0);
		if (WIFSIGNALED(status))
			sig = 128 + WTERMSIG(status);
		++idx;
	}
	if (sig)
		set_exit_status(sig);
	else
		set_exit_status(WEXITSTATUS(status));
}

void	exec_command(t_executor *executor, t_env **env)
{
	int		pipe_fd[PIPE];
	int		read_fd;
	size_t	n;
	pid_t	pids[800];

	if (here_docs(executor, *env))
		return ;
	ft_child_sig_hundler();
	if (is_builtin(executor->command) && \
		!executor->next)
	{
		adult_exec_builtin(executor, env);
		return ;
	}
	read_fd = xdup(READ);
	n = 0;
	while (executor)
	{
		xpipe(pipe_fd);
		pids[n] = xfork();
		if (!pids[n++])
			child_process(executor, env, pipe_fd);
		else
			adult_process(pipe_fd);
		executor = executor->next;
	}
	wait_child(pids, n);
	xclose(READ), xdup2(read_fd, READ), xclose(read_fd);
}
