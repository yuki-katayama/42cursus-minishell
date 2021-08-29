#ifndef PIPE_H
# define PIPE_H

# include <unistd.h> // dup2 dup fork execve pipe write
# include <sys/wait.h> // wait
# include <fcntl.h> // open close
# include <sys/stat.h> // stat
# include <stdlib.h> // free
# include "lexer.h"

enum e_pipe
{
	READ,
	WRITE,
	PIPE
};

typedef struct s_env t_env;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

t_env	*init_env(char **envp);
void	multi_level_pipe(t_node *node, t_env *env);
void	expand_env(t_token **token, t_env *env);
char	*msh_get_env(char *key, t_env *env);
void	marge_token(t_node *node);
char	**format_command(t_token *token, size_t idx);
char	*format_path(char *cmd, char **path);
int	here_doc(char *str, int read, t_env *env);
char	**ft_split(const char *s, const char c);

#endif