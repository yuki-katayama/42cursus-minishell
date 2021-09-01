#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h> //exit uint8_t getenv
# include <readline/readline.h> //rl_replace_line, rl_on_new_line, rl_redisplay
# include <unistd.h> // FILENO chdir getcwd
# include <limits.h> // LLONG_ PATH_MAX
# include <errno.h> //errno
# include <stdbool.h> //bool
# include "./pipe.h" //t_env

// ctrl_d
void				bi_ctrl_d(char *str);

//exit
int					bi_exit(char *str);

// exit_utils
bool				check_hypen(char **splited);
bool				check_sharp(char **splited);
char				*skip_or_delete(char *str);
char				*skip_option_flg(char *str);
unsigned long int	exit_atoi(const char *str, bool *err_flg);

// cd
int					bi_cd(char *str);

// pwd
int					bi_pwd(void);

// export
int	bi_export(char **argv, t_env *env);

// unset
int bi_unset(char **key, t_env *env);

#endif