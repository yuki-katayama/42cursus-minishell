#include "../../includes/utils.h"
#include "../../libft/libft.h"

char	*msh_substr(char *start, char *end)
{
	char	*ret;
	size_t	idx;

	if (!(ft_malloc_p((void **)&ret, sizeof(char *) * (end - start + 1))))
		exit(1);
	idx = 0;
	while (start != end)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}
