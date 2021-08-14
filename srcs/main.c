#include "../includes/main.h"
#include "../includes/signal.h"
#include "unistd.h"

int	main(void)
{
	char	*command;

	while (1)
	{
		ft_signal();
		command = readline("minishell$ ");
		if (command == NULL)
		{
			printf("\033[%dAminishell$ exit\n" ,1);
			exit(0);
		}
		if (command && ft_strlen(command) > 0)
		{
			add_history(command);
		}
		free(command);
	}
	return (0);
}
