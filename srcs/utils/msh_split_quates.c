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
	if ((c == '"' || c == '\''))
	{
		if (*quatation == false)
			*quatation = true;
		else
			*quatation = false;
		return (0);
	}
	if (c == sep && *quatation == false)
		return (1);
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
		while (str[++i] && !(check_if_sep(str[i], sep, quatation)))
			;
	}
	return (count);
}

static char	*assign_res(char const *str, char sep, bool quatation)
{
	int		i;
	char	*res;

	quatation = false;
	i = 0;
	while (str[i] && (!check_if_sep(str[i], sep, &quatation)))
		i++;
	if (!(ft_malloc_p((void **)&res, i + 1)))
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

int	set_value(char *s, char c, char **words, bool *quatation)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (s[i] && s != NULL)
	{
		while (s[i] && check_if_sep(s[i], c, quatation))
			i++;
		if (s[i])
		{
			words[j] = assign_res(s + i, c, quatation);
			if (!(words[j++]))
				return (*(int *)ft_free_char(words, i));
		}
		while (s[++i] && !(check_if_sep(s[i], c, quatation)))
			;
	}
	return (j);
}

char	**msh_split_quates(char const *s, char c)
{
	char	**words;
	int		j;
	bool	quatation;

	quatation = false;
	if (!s)
		return (NULL);
	if (!(ft_malloc_pp((void ***)&words, \
		sizeof(char *) * (cnt_str(s, c, &quatation) + 1))))
		return (NULL);
	j = set_value((char *)s, c, words, &quatation);
	if (j == 0)
		return (NULL);
	words[j] = NULL;
	return (words);
}
