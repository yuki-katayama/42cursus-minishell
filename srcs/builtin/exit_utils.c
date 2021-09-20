#include "../../includes/builtin.h"
#include "../../libft/libft.h"

char	*skip_or_delete(char *str)
{
	if (*str == '"' || *str == '\'')
		str = ft_chardel(str, "\"'");
	else if (*str == '#')
		str = ft_charskip(str, '#');
	return (str);
}

bool	check_sharp(char **splited)
{
	if (*(ft_charskip(skip_or_delete(*splited), '#')) == '\0')
		return (true);
	return (false);
}

bool	check_hypen(char **splited)
{
	if (ft_strncmp(skip_or_delete(*splited), "--", ft_strlen("--")) == 0)
		return (true);
	return (false);
}

char	*skip_option_flg(char *str)
{
	if (!(ft_strncmp(str, "--", ft_strlen(str))))
		str += 2;
	return (str);
}

unsigned long int	exit_atoi(const char *str, bool *err_flg)
{
	unsigned long int	res;
	int					negative;

	res = 0;
	negative = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			negative = negative * -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
		if ((res > (unsigned long int)LLONG_MIN && negative == -1) \
			|| (res > (unsigned long int)LLONG_MAX && negative == 1))
		{
			*err_flg = (true);
			return (LLONG_MAX);
		}
	}
	return (res * negative);
}
