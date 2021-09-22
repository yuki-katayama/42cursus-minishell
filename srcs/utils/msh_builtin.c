#include "../../includes/utils.h"
#include "../../includes/builtin.h"
#include "../../libft/libft.h"

bool msh_is_bi(char *cmd)
{
	if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0
		|| ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0
		|| ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0
		|| ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0
		|| ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0
		|| ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0
		|| ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		return (true);
	return (false);
}

int msh_run_bi(char **cmd_arg, t_env *env, char *process)
{
	char *cmd;
	char **argv;

	cmd = cmd_arg[0];
	argv = &cmd_arg[1];
	if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		bi_exit(argv);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		bi_cd(*argv);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		bi_pwd();
	else if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		bi_export(argv, env);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		bi_unset(argv, env);
	else if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
		bi_env(env);
	else if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		bi_echo(argv, env);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		bi_pwd();
	if (ft_strncmp(process, "child", ft_strlen("child") + 1) == 0)
		exit(0);
	return (0);
}