#include "ft_signal.h"
#include "libft.h"
#include <errno.h>

static void	ft_heredoc_signal_sigint(int sig)
{
	(void)sig;
	ft_put_str_fd("\n", 1);
	exit(1);
}

static void	ft_heredoc_signal_sigquit(int sig)
{
	(void)sig;
	ft_put_str_fd("\b\b  \b\b", 1);
	ft_put_str_fd("Quit: 3\n", 1);
	exit(1);
}

void	ft_heredoc_sig_hundler(void)
{
	if (signal(SIGINT, ft_heredoc_signal_sigint) == SIG_ERR || \
		signal(SIGQUIT, ft_heredoc_signal_sigquit) == SIG_ERR)
	{
		ft_put_str_fd(strerror(errno), STDERR_FILENO);
		exit(1);
	}
}