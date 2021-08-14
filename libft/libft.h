#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h> //size_t malloc

int		ft_malloc_p(void **p, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_charskip(const char *str, char skip);

#endif
