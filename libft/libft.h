#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h> //size_t malloc
# include <unistd.h> //write
# include <stdbool.h> // bool

int		ft_malloc_p(void **p, size_t len);
int		ft_malloc_pp(void ***p, size_t len);
size_t	ft_strlen(const char *s);
char	*ft_spaceskip(const char *str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);
char	*ft_skip(const char *str, int len);
int		ft_isdigit(int c);
bool	ft_isdigitstr(char *str);
char	*ft_charskip(const char *str, char skip);
void	*ft_free_char(char **word, int index);
int		ft_arraylen(char **array);


#endif
