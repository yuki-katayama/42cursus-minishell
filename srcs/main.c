#include "../includes/main.h"
#include "../includes/signal.h"
#include "../includes/utils.h"
#include "../includes/builtin.h"

int select_buildin(char *argv)
{
	if ((ft_strncmp(argv, \
						"exit ", ft_strlen("exit ")) == 0) \
		|| ft_strcmp(argv, "exit") == 0)
			return (1);
	else if ((ft_strncmp(argv,
						"cd ", ft_strlen("cd ")) == 0)
		|| (ft_strcmp(argv, "cd") == 0))
			return (2);
}

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
		if (select_buildin(argv) == 1)
			ft_exit(argv + ft_strlen("exit"));
		if (select_buildin(argv) == 2)
			ft_cd(argv + ft_strlen("cd"));
		if (select_buildin(argv) == 2)
			ft_cd(argv + ft_strlen("pwd"));
		free(argv);
	}
	return (0);
}
