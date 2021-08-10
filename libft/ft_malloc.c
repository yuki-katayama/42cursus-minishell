#include "libft.h"

int	ft_malloc_p(void **p, size_t len)
{
	*p = malloc(len);
	if (*p == NULL)
		return (0);
	return (1);
}
