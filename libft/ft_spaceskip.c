#include "libft.h"

char	*ft_spaceskip(const char *str)
{
	while ((*str == ' ' || *str == '\t' || *str == '\n') \
			|| (*str == '\r' || *str == '\v' || *str == '\f'))
		str++;
	return ((char *)str);
}
