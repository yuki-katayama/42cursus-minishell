#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h> //exit uint8_t getenv
# include <stdio.h> //readline
# include <readline/readline.h> //rl_replace_line, rl_on_new_line, rl_redisplay
# include <unistd.h> // FILENO chdir getcwd
# include <limits.h> // LLONG_
# include <errno.h> //errno
# include <stdbool.h> //bool

// ctrl_d
void				ft_ctrl_d(char *str);

//exit
void				ft_exit(char *str);

// exit_utils
bool				check_hypen(char **splited);
bool				check_sharp(char **splited);
char				*skip_or_delete(char *str);
char				*skip_option_flg(char *str);
unsigned long int	exit_atoi(const char *str, bool *err_flg);

// cd
int					ft_cd(char *str);

#endif