#ifndef PIPE_H
# define PIPE_H

# include <sys/stat.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include "lexer.h"

typedef struct s_env t_env;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

enum e_pipe
{
	READ,
	WRITE,
	PIPE
};

t_env	*init_env(char **envp);
void	multi_level_pipe(t_node *node, t_env *env);
void	expand_environment_variables(t_token **token, t_env *env);
char	*msh_get_env(char *key, t_env *env);

#endif