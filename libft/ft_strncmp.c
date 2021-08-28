#include "libft.h"
#include "stdio.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < (int)n - 1 && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (((char *)s1)[i] - ((char *)s2)[i]);
}
