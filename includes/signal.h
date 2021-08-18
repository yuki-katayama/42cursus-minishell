#ifndef SIGNAL_H
# define SIGNAL_H

# include <signal.h> // signal
# include <stdio.h> // readline
# include <stdlib.h> // exit
# include <string.h> //strerror
# include <sys/errno.h> //errno
# include <unistd.h> // FILENO

# include <readline/readline.h> //rl_replace_line, rl_on_new_line, rl_redisplay
void	ft_signal(void);

#endif