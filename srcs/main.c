#include "../includes/main.h"
#include "../includes/signal.h"
#include "../includes/utils.h"
#include "../includes/builtin.h"
#include "../includes/lexer.h"
#include "../includes/pipe.h"
#include "../includes/utils.h"
#include "../libft/libft.h"

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
	else if ((ft_strncmp(argv,
						"pwd ", ft_strlen("pwd ")) == 0)
		|| (ft_strcmp(argv, "pwd") == 0))
			return (3);
	return (0);
}

int	main(int argc, char **test)
{
	extern char **environ;
	char	**env;
	char	*argv;
	// uint8_t select;
	t_node	*node;
	t_env	*st_env;


	env = environ;
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
		node = nodalize(strdup("echo a > test"));
		st_env = init_env(env);
		multi_level_pipe(node, st_env);
		// select = select_buildin(argv);
		// if (select == 1)
		// 	ft_exit(argv + ft_strlen("exit"));
		// else if (select == 2)
		// 	ft_cd(argv + ft_strlen("cd"));
		// else if (select == 3)
		// 	ft_pwd();
		free(argv);
	}
	return (0);
}
