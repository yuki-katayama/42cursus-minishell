#include <stdio.h>

char	*ft_charskip(const char *str, char skip)
{
	while(*str == skip)
		str++;
	return ((char *)str);
}