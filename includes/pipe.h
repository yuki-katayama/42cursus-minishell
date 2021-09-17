#ifndef PIPE_H
# define PIPE_H

# include <unistd.h> // dup2 dup fork execve pipe write
# include <sys/wait.h> // wait
# include <fcntl.h> // open close
# include <sys/stat.h> // stat
# include <stdlib.h> // free
# include "lexer.h"
# include <readline/readline.h> //readline

enum e_pipe
{
	READ,
	WRITE,
	PIPE
};

typedef struct s_env	t_env;

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

//pipe
void	multi_level_pipe(t_node *node, t_env *env);
char	*msh_get_env(char *key, t_env *env);

//here_doc
int		here_doc(char *str, int read, t_env *env);

//open_io
int		open_output(t_token *token);
int		open_input(t_token *token, int read_fd, t_env *env);

//format
char	*format_path(char *cmd, char **path);
char	**format_command(t_token *token, size_t idx);

//merge
void	marge_token(t_node *node);

#endif