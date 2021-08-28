#ifndef ERROR_H
# define ERROR_H

# include <unistd.h> //FILENO

void	exit_numeric_argument_error(char *str);
void	exit_too_many_argument_error(void);

#endif