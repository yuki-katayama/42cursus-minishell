#include "../../includes/signal.h"

/*
** Ctrl + C
*/

static void	ft_signal_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	errno = 1;
}

/*
** Ctrl + \
** 何もしない
*/

static void	ft_signal_sigquit(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
}

void	ft_signal(void)
{
	if (signal(SIGINT, ft_signal_sigint) == SIG_ERR)
	{
		printf("%s", strerror(errno));
		exit(1);
	}
	if (signal(SIGQUIT, ft_signal_sigquit) == SIG_ERR)
	{
		printf("%s", strerror(errno));
		exit(1);
	}
}
