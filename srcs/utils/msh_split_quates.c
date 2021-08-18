#include "../../libft/libft.h"

/*
input: aa "a b c" 'a b c de' cd
output:[
	aa,
	"a b c",
	'a b c de',
	cd,
];
*/
static int	check_if_sep(char c, char sep, bool *quatation)
{
	if ((c == '"' || c == '\'') && *quatation == false)
	{
		*quatation = true;
		return (0);
	}
	if (c == sep && *quatation == false)
		return (1);
	if ((c == '"' || c == '\'') && *quatation == true)
	{
		*quatation = false;
		return (0);
	}
	return (0);
}

static int	cnt_str(char const *str, char sep, bool *quatation)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		while (check_if_sep(str[i], sep, quatation))
			i++;
		count++;
		if (str[i] != '\0')
			i++;
		while (str[i] && !(check_if_sep(str[i], sep, quatation)))
			i++;
	}
	return (count);
}

static int	ft_strlen_sep(char const *s, char sep, bool quatation)
{
	int	i;

	i = 0;
	while (s[i] && (!check_if_sep(s[i], sep, &quatation)))
		i++;
	return (i);
}

static char	*assign_res(char const *str, char sep, bool quatation)
{
	int		i;
	char	*res;

	quatation = false;
	if (!(ft_malloc_p((void **)&res, (ft_strlen_sep(str, sep, quatation) + 1))))
		return (NULL);
	i = 0;
	while (str[i] && !(check_if_sep(str[i], sep, &quatation)))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	**msh_split_quates(char const *s, char c)
{
	char	**words;
	size_t	i;
	int		j;
	bool quatation;

	quatation = false;
	if (!s)
		return (NULL);
	if (!(ft_malloc_pp((void ***)&words, sizeof(char *) * (cnt_str(s, c, &quatation) + 1))))
		return (NULL);
	j = 0;
	i = 0;
	while (s[i] && s != NULL)
	{
		while (s[i] && check_if_sep(s[i], c, &quatation))
			i++;
		if (s[i])
		{
			words[j] = assign_res(s + i, c, quatation);
			if (!(words[j++]))
				return (ft_free_char(words, (int)i));
		}
		if (s[i] != '\0')
			i++;
		while (s[i] && !(check_if_sep(s[i], c, &quatation)))
			i++;
	}
	words[j] = NULL;
	return (words);
}
