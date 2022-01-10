/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nyokota <nyokota@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 20:30:04 by nyokota           #+#    #+#             */
/*   Updated: 2022/01/09 17:34:18 by nyokota          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_signal.h"
#include "libft.h"
#include <errno.h>
#include "exit_status.h"

static void	ft_signal_sigint(int sig)
{
	(void)sig;
	ft_put_str_fd("\b\b  \b\b\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	set_exit_status(errno = 1);
}

static void	ft_signal_process_sigint(int sig)
{
	(void)sig;
	ft_put_str_fd("\n", 1);
	set_exit_status(errno = 1);
}

static void	ft_sig_hundler(void	(*sig_func)(int	sig))
{
	if (signal(SIGINT, sig_func) == SIG_ERR || \
		signal(SIGQUIT, SIG_IGN) == SIG_ERR)
	{
		ft_put_str_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}

void	ft_signal(void)
{
	ft_sig_hundler(ft_signal_sigint);
}

void	ft_signal_process(void)
{
	ft_sig_hundler(ft_signal_process_sigint);
}
