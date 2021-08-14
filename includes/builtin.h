#ifndef BUILTIN_H
# define BUILTIN_H

# include <stdlib.h> //exit
# include <stdio.h>
# include <readline/readline.h> //rl_replace_line, rl_on_new_line, rl_redisplay

int		ft_ctrl_d(char *str);
int		ft_input_exit(char *command);
void	ft_exit(char *str, int (*ft_exit)(char *));

#endif