#include "utils.h"

char	*skip(char *str)
{
	while (*str == ' ')
		++str;
	return (str);
}

char	*skip_until_c(char *str, char c)
{
	++str;
	while (*str && *str != c)
		++str;
	return (str);
}