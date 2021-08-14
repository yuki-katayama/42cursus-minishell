#include "../includes/main.h"
#include "../includes/signal.h"
#include "../includes/utils.h"
#include "../includes/builtin.h"

int	main(void)
{
	char	*command;

	while (1)
	{
		ft_signal();
		command = readline("minishell$ ");
		if (command && ft_strlen(command) > 0)
			add_history(command);
		if (command == NULL)
			ft_exit("minishell$ exit", ft_ctrl_d);
		if (msh_strcmp(command, "exit") == 0)
			ft_exit(command, ft_input_exit);
		free(command);
	}
	return (0);
}
