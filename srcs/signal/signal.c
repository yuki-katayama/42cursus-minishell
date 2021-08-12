#include "../../includes/signal.h"

/*
** Ctrl + C
*/

static void	ft_signal_sigint(int sig)
{
	printf("%d\n", sig);
	exit(1);
}

/*
** Ctrl + \
*/

static void	ft_signal_sigquit(int sig)
{
	printf("%d\n", sig);
}

void	ft_signal(void)
{
	if (signal(SIGINT, ft_signal_sigint) == SIG_ERR)
	{
		exit(1);
	}
	if (signal(SIGQUIT, ft_signal_sigquit) == SIG_ERR)
	{
		exit(1);
	}
}
