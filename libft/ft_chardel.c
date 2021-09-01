#include "libft.h"

static bool	is_delete(char str, char *c)
{
	if (ft_strchr(c, str))
		return (true);
	return (false);
}

static int	ft_getlen(char *str, char *c)
{
	int	len1;
	int	len2;
	int	i;

	i = -1;
	len1 = ft_strlen(str);
	len2 = len1;
	while (++i < len1)
	{
		if (is_delete(str[i], c))
			len2--;
	}
	return (len2);
}

char	*ft_chardel(char *str, char *c)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	len = ft_getlen(str, c);
	if (!(ft_malloc_p((void **)&ret, sizeof(char *) * (len + 1))))
		return (NULL);
	i = -1;
	j = -1;
	len = ft_strlen(str);
	while (++i < len)
	{
		if (!(is_delete(str[i], c)))
			ret[++j] = str[i];
	}
	ret[i] = '\0';
	return (ret);
}
