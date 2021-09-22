#ifndef UTILS_H
# define UTILS_H

# include "pipe.h"
# include <stdbool.h>

char	**msh_split_quates(char const *s, char c);
char	*msh_substr(char *start, char *end);
char	*msh_get_env(char *key, t_env *env);
t_env	*msh_del_env(char *key, t_env *env);
int		msh_run_bi(char **cmd_arg, t_env *env, char *process);
bool	msh_is_bi(char *cmd);

#endif