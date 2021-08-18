#include "../../includes/builtin.h"
#include "../../includes/error.h"
#include "../../includes/main.h"
#include "../../libft/libft.h"
#include "../../includes/utils.h"

void ft_ctrl_d(char *str)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	exit(0);
}

static unsigned long int exit_atoi(const char *str, bool *err_flg)
{
	unsigned long int res;
	int negative;

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
		if ((res > (unsigned long int)LLONG_MIN && negative == -1) || (res > (unsigned long int)LLONG_MAX && negative == 1))
		{
			*err_flg = true;
			return (LLONG_MAX);
		}
	}
	return (res * negative);
}

char *skip_option_flg(char *str)
{
	if (!(ft_strcmp(str, "--")))
		str += 2;
	return (str);
}

char *skip_delete(char *str)
{
	if (*str == '"')
		str = ft_chardel(str, '"');
	else if (*str == '\'')
		str = ft_chardel(str, '\'');
	else if (*str == '#')
		str = ft_charskip(str, '#');
	return (str);
}

static int arraylen_one(char *str)
{
	char *mem;
	bool err_flg;
	uint8_t status;

	mem = str;
	str = skip_delete(str);
	str = skip_option_flg(str);
	if (*str == '\0')
		exit(0);
	str = ft_spaceskip(str);
	mem = ft_chardel(mem, '"');
	mem = ft_chardel(mem, '\'');
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

void ft_exit(char *str)
{
	char **splited;
	int len;

	if (TEST)
		ft_putendl_fd("exit", STDERR_FILENO);
	splited = &msh_split_quates(str, ' ')[1];
	len = ft_arraylen(splited);
	if (len < 3)
	{
		if (*splited == NULL)
			exit(0);
		else if (ft_arraylen(splited) == 1)
			exit(arraylen_one(*splited));
		else if (*(ft_charskip(skip_delete(*splited), '#')) == '\0')
		{
			splited++;
			arraylen_one(*splited);
			exit(0);
		}
		else if (ft_strcmp(skip_delete(*splited), "--") == 0)
		{
			splited++;
			exit(arraylen_one(*splited));
		}
	}
	else if (!(ft_isdigitstr(skip_delete(*splited))))
	{
		exit_numeric_argument_error(*splited);
		exit(255);
	}
	exit_too_many_argument_error();
	errno = 1;
	if (TEST)
		exit(1);
	return ((void)NULL);
}
