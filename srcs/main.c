#include "../includes/main.h"
#include "../includes/signal.h"

int	main(void)
{
	char	*command;

	while (1)
	{
		ft_signal();
		command = readline("minishell$ ");
		if (command == NULL)
			 exit(1);
		if (command && ft_strlen(command) > 0)
		{
			add_history(command);
		}
		free(command);
	}
	return (0);
}
