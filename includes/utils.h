#ifndef UTILS_H
# define UTILS_H
# include <stdlib.h>

char	**msh_split_quates(char const *s, char c);
char	*skip(char *str);
char	*skip_until_c(char *str, char c);
char	*msh_substr(char *start, char *end);

#endif