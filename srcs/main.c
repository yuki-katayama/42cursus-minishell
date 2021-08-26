#include "../includes/main.h"
#include "../includes/signal.h"
#include "../includes/utils.h"
#include "../includes/builtin.h"

int	main(int argc, char **test)
{
	char	*argv;

	(void)argc;
	while (1)
	{
		ft_signal();
		if (TEST)
			argv = test[2];
		else
			argv = readline("minishell$ ");
		if (argv && ft_strlen(argv) > 0)
			add_history(argv);
		if (argv == NULL)
			ft_ctrl_d("minishell$ exit");
		argv = ft_spaceskip(argv);
		if ((ft_strncmp(argv, \
						"exit ", ft_strlen("exit ")) == 0) \
		|| ft_strcmp(argv, "exit") == 0)
			ft_exit(argv);
		else if ((ft_strncmp(argv,
						"cd ", ft_strlen("cd ")) == 0) ||
			(ft_strcmp(argv, "cd") == 0))
			ft_cd(argv + 3);
		free(argv);
	}
	return (0);
}
