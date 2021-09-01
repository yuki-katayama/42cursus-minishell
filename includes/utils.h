#ifndef UTILS_H
# define UTILS_H

# include "pipe.h"

char	**msh_split_quates(char const *s, char c);
char	*msh_substr(char *start, char *end);
char	*msh_get_env(char *key, t_env *env);
t_env	*msh_del_env(char *key, t_env *env);

#endif