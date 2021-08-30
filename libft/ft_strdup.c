#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dest;
	int		i;

	if (!(ft_malloc_p((void **)&dest, sizeof(char *) * (ft_strlen(src) + 1))))
		return (NULL);
	i = 0;
	while (*src)
		dest[i++] = *src++;
	dest[i] = '\0';
	return (dest);
}
