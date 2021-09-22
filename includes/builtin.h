#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h> //exit uint8_t getenv
# include <readline/readline.h> //rl_replace_line, rl_on_new_line, rl_redisplay
# include <unistd.h> // FILENO chdir getcwd
# include <limits.h> // LLONG_ PATH_MAX
# include <errno.h> //errno
# include <stdbool.h> //bool
# include "./pipe.h" //t_env
//exit
int					msh_exit(char **argv);

// cd
int					msh_cd(char *str);

// pwd
int					msh_pwd(void);

// export
int	msh_export(char **argv, t_env *env);

// unset
int msh_unset(char **key, t_env *env);

// env
int msh_env(t_env *env);

// echo
int msh_echo(char **splited, t_env *env);
#endif