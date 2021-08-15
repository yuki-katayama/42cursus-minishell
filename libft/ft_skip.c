#include "libft.h"

char	*ft_skip(const char *str, int len)
{
	if (len < 0)
		return (NULL);
	len += 1;
	while(--len)
		str++;
	return ((char *)str);
}
