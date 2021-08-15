#include "../../includes/utils.h"

char	*msh_substr(char *start, char *end)
{
	char	*ret;
	size_t	idx;

	ret = malloc(sizeof(*ret) * (end - start + 1));
	if (!ret)
		exit(1);
	idx = 0;
	while (start != end)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}