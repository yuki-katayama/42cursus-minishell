#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h> //exit uint8_t
# include <stdio.h> //readline
# include <readline/readline.h> //rl_replace_line, rl_on_new_line, rl_redisplay
# include <unistd.h> // FILENO
# include <limits.h> // LLONG_
# include <errno.h> //errno
# include <stdbool.h> //bool

// exit
void				ft_ctrl_d(char *str);
void				ft_exit(char *str);
bool				check_sharp(char **splited);
bool				check_hypen(char **splited);
char				*skip_option_flg(char *str);
char				*skip_or_delete(char *str);
unsigned long int	exit_atoi(const char *str, bool *err_flg);

#endif