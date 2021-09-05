#include "../includes/main.h"
#include "../includes/signal.h"
#include "../includes/utils.h"
#include "../includes/builtin.h"
#include "../includes/lexer.h"
#include "../includes/pipe.h"
#include "../includes/utils.h"
#include "../includes/expansion.h"
#include "../libft/libft.h"

static bool	is_builtin(char *argv, char *cmd, char *cmd_sp)
{
	if (!argv)
		return (false);
	if ((ft_strncmp(argv, cmd_sp, ft_strlen(cmd_sp)) == 0) \
			|| ft_strncmp(argv, cmd, ft_strlen(cmd) + 1) == 0)
		return (true);
	return (false);
}

static int	run_builtin(char *argv, t_env *env)
{
	if (is_builtin(argv, "exit", "exit "))
		bi_exit(argv + ft_strlen("exit"));
	else if (is_builtin(argv, "cd", "cd "))
		return (bi_cd(argv + ft_strlen("cd")));
	else if (is_builtin(argv, "pwd", "pwd "))
		return (bi_pwd());
	else if (is_builtin(argv, "export", "export "))
		return (bi_export(msh_split_quates(argv, ' '), env));
	else if (is_builtin(argv, "unset", "unset "))
		return (bi_unset(msh_split_quates(argv, ' '), env));
	else if (is_builtin(argv, "env", "env "))
		return (bi_env(env));
	else if (is_builtin(argv, "echo", "echo "))
		return (bi_echo(msh_split_quates(argv, ' '), env));
	return (1);
}

static t_env	*init_env(char **envp)
{
	t_env	*head;
	t_env	**cur;
	char	*str;

	head = NULL;
	cur = &head;
	while (*envp)
	{
		if (!(ft_malloc_p((void **)&*cur, sizeof(t_env))))
			return (NULL);
		str = *envp;
		while (*str && *str != '=')
			++str;
		*str = '\0';
		**cur = (t_env)
		{
			.key = ft_strdup(*envp++),
			.value = ft_strdup(++str)
		};
		cur = &(*cur)->next;
	}
	return (head);
}

int	main(void)
{
	extern char	**environ;
	char		*argv;
	t_node		*node;
	t_env		*st_env;
	char		**pipe_split;

	st_env = init_env(environ);
	while (1)
	{
		ft_signal();
		argv = readline("minishell$ ");
		if (argv && ft_strlen(argv) > 0)
			add_history(argv);
		if (argv == NULL)
			bi_ctrl_d("minishell$ exit");
		argv = ft_spaceskip(argv);
		node = nodalize(ft_strdup(argv));
		multi_level_pipe(node, st_env);
		pipe_split = ft_split(argv, '|');
		if (ft_arraylen(pipe_split) != 0)
			run_builtin(pipe_split[ft_arraylen(pipe_split) - 1], st_env);
		free(argv);
	}
	return (0);
}
