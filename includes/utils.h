#ifndef UTILS_H
# define UTILS_H

# include "pipe.h"
# include <stdbool.h>

char	*msh_substr(char *start, char *end);
//msh_builin.c
int		run_msh_bi(char **cmd_arg, t_env *env, char *process);
bool	is_msh_bi(char *cmd);
//msh_env_utils.c
char	*msh_get_env(char *key, t_env *env);
t_env	*msh_del_env(char *key, t_env *env);
//msh_exit_utils.c
char	*skip_or_delete(char *str);
bool	check_sharp(char **splited);
bool	check_hypen(char **splited);
char	*skip_option_flg(char *str);
unsigned long int	exit_atoi(const char *str, bool *err_flg);
#endif