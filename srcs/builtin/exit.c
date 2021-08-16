#include "../../includes/builtin.h"
#include "../../includes/error.h"
#include "../../libft/libft.h"

static unsigned long int	exit_atoi(const char *str, bool *err_flg)
{
	unsigned long int	res;
	int			negative;

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
		if ((res > (unsigned long int)LLONG_MIN && negative == -1)
		||	(res > (unsigned long int)LLONG_MAX && negative == 1))
		{
			*err_flg = true;
			return (LLONG_MAX);
		}
	}
	return (res * negative);
}

int	ft_ctrl_d(char *str)
{
	ft_putstr_fd("\033[1A", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	return (0);
}

/*
** exit + commandで、statusが変わるので後で処理を追加する。
*/

int    ft_input_exit(char *str)
{
	bool err_flg;
	uint8_t num;

    err_flg = false;
    num = 0;
    str = ft_skip(str, ft_strlen("exit "));
    str = ft_spaceskip(str);
    if (!(ft_isdigitstr(str)))
    {
        exit_numeric_argument_error(str);
        return (255);
    }
    num = (uint8_t)exit_atoi(str, &err_flg);
    if (err_flg)
        exit_numeric_argument_error(str);
    return (num);
}

void	ft_exit(char *str, int (*ft_exit)(char *))
{
	uint8_t	status;

	status = ft_exit(str);
	exit(status);
}
