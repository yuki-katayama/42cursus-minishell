#include "../../libft/libft.h"
#include "../../includes/builtin.h"

/* CDPATHを参照しなければならない。
	///の対応
*/

void msh_cd_error(char *path)
{
	path = ft_strjoin("minishell: cd: ", path);
	perror(path);
}

int	msh_cd(char *path, t_env *env)
{
	char *homeDir;

	if (!path)
		path = msh_get_env("HOME", env);
	else
		path = ft_spaceskip(path);
	if (chdir(path) != 0)
		msh_cd_error(path);
	return (0);
}
