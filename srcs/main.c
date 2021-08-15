#include "../includes/main.h"
#include "../includes/signal.h"
#include "../includes/utils.h"
#include "../includes/builtin.h"

int	main(void)
{
	char	*argv;

	while (1)
	{
		ft_signal();
		argv = readline("minishell$ ");
		if (argv && ft_strlen(argv) > 0)
			add_history(argv);
		if (argv == NULL)
			ft_exit("minishell$ exit", ft_ctrl_d);
		argv = ft_spaceskip(argv);
		if ((ft_strncmp(argv, \
						"exit ", ft_strlen("exit ")) == 0) \
		|| ft_strcmp(argv + ft_strlen("exit"), "exit") == 0)
			ft_exit(argv, ft_input_exit);
		free(argv);
	}
	return (0);
}
