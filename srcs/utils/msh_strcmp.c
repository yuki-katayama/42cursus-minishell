#include "../../includes/utils.h"
#include "../../libft/libft.h"

int	msh_strcmp(const char *s1, const char *s2)
{
	size_t	size;

	size = ft_strlen(s2);
	s1 = (const char *)ft_charskip(s1, ' ');
	while (--size)
	{
		s1 += 1;
		s2 += 1;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
