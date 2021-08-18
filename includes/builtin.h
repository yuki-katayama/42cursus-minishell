#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h> //exit uint8_t
# include <stdio.h> //readline
# include <readline/readline.h> //rl_replace_line, rl_on_new_line, rl_redisplay
# include <unistd.h> // FILENO
# include <limits.h> // LLONG_
# include <errno.h> //errno

void	ft_ctrl_d(char *str);
int		ft_input_exit(char *command);
void	ft_exit(char *str);

#endif