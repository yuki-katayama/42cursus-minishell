#include "../../includes/utils.h"
#include "../../includes/builtin.h"
#include "../../libft/libft.h"

bool is_msh_bi(char *cmd)
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

int run_msh_bi(char **cmd_arg, t_env *env, char *process)
{
	char *cmd;
	char **argv;

	cmd = cmd_arg[0];
	argv = &cmd_arg[1];
	if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		msh_exit(argv);
	else if (ft_strncmp(cmd, "cd", ft_strlen("cd") + 1) == 0)
		msh_cd(*argv, env);
	else if (ft_strncmp(cmd, "exit", ft_strlen("exit") + 1) == 0)
		msh_pwd();
	else if (ft_strncmp(cmd, "export", ft_strlen("export") + 1) == 0)
		msh_export(argv, env);
	else if (ft_strncmp(cmd, "unset", ft_strlen("unset") + 1) == 0)
		msh_unset(argv, env);
	else if (ft_strncmp(cmd, "env", ft_strlen("env") + 1) == 0)
		msh_env(env);
	else if (ft_strncmp(cmd, "echo", ft_strlen("echo") + 1) == 0)
		msh_echo(argv, env);
	else if (ft_strncmp(cmd, "pwd", ft_strlen("pwd") + 1) == 0)
		msh_pwd();
	if (ft_strncmp(process, "child", ft_strlen("child") + 1) == 0)
		exit(0);
	return (0);
}