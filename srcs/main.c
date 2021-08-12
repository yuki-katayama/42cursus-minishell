#include "../includes/main.h"

int	main(void)
{
	char	*command;

	while (1)
	{
		command = readline("minishell$ ");
		if (command && ft_strlen(command) > 0)
		{
			add_history(command);
		}
		ft_signal();
		free(command);
	}
	return (0);
}
