#include "libft.h"

static char	*sub_split(const char *start, const char *end)
{
	char	*ret;
	size_t	idx;

	if (!(ft_malloc_p((void **)&ret, sizeof(char *) * (end - start + 1))))
		return (NULL);
	if (!ret)
		return (NULL);
	idx = 0;
	while (start != end)
		ret[idx++] = *start++;
	ret[idx] = '\0';
	return (ret);
}

static char	**rec_split(const char *str, const char c, size_t idx)
{
	char	**ret;
	char	*ptr;

	while (*str && *str == c)
		++str;
	if (!*str)
	{
		if (!(ft_malloc_p((void **)&ret, sizeof(char *) * (idx + 1))))
			return (NULL);
		if (ret)
			ret[idx] = NULL;
		return (ret);
	}
	ptr = (char *)str;
	while (*str && *str != c)
		++str;
	ptr = sub_split(ptr, str);
	if (!ptr)
		return (NULL);
	ret = rec_split(str, c, idx + 1);
	if (ret)
		ret[idx] = ptr;
	else
		free(ptr);
	return (ret);
}

char	**ft_split(const char *s, const char c)
{
	if (!s)
		return (NULL);
	return (rec_split((char *)s, c, 0));
}
