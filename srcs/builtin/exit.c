#include "../../includes/builtin.h"
#include "../../includes/error.h"
#include "../../includes/main.h"
#include "../../libft/libft.h"
#include "../../includes/utils.h"

static int	arraylen_one(char *str)
{
	char	*mem;
	bool	err_flg;
	uint8_t	status;

	mem = str;
	str = skip_or_delete(str);
	str = skip_option_flg(str);
	if (*str == '\0')
		return (0);
	str = ft_spaceskip(str);
	mem = ft_chardel(mem, "\"'");
	if (ft_isdigitstr(str))
	{
		status = (uint8_t)exit_atoi(str, &err_flg);
		if (err_flg)
			exit_numeric_argument_error(mem);
		return (status);
	}
	else
	{
		exit_numeric_argument_error(mem);
		return (255);
	}
}

void	arraylen_under_three(char **splited)
{
	if (*splited == NULL || (check_sharp(splited) && ft_arraylen(splited) != 1))
		exit(0);
	else if (ft_arraylen(splited) == 1)
		exit(arraylen_one(*splited));
	else if (check_hypen(splited))
	{
		splited++;
		exit(arraylen_one(*splited));
	}
}

int	bi_exit(char *str)
{
	char	**splited;
	int		len;

	splited = msh_split_quates(str, ' ');
	if (splited == NULL)
		exit(0);
	len = ft_arraylen(splited);
	if (len < 3)
		arraylen_under_three(splited);
	else if (!(ft_isdigitstr(skip_or_delete(*splited))))
	{
		exit_numeric_argument_error(*splited);
		exit(255);
	}
	exit_too_many_argument_error();
	errno = 1;
	return (0);
}
