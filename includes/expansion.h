#ifndef EXPANSION_H
# define EXPANSION_H

void	expand_env(t_token **token, t_env *env);
char	*expand_env_helper(char *str, size_t idx, t_env *env);

#endif