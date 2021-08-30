#include "../../includes/pipe.h"

int	open_input(t_token *token, int read_fd, t_env *env)
{
	int	ret;

	ret = -1;
	while (token)
	{
		if (ret != -1)
			close(ret);
		if (token->kind == TK_RI)
			ret = open(token->str, O_RDONLY);
		if (token->kind == TK_DRI)
			ret = here_doc(token->str, read_fd, env);
		token = token->next;
	}
	return (ret);
}

int	open_output(t_token *token)
{
	int	ret;

	ret = -1;
	while (token)
	{
		if (ret != -1)
			close(ret);
		if (token->kind == TK_RO)
			ret = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, S_IREAD | S_IWRITE);
		if (token->kind == TK_DRO)
			ret = open(token->str, O_WRONLY | O_CREAT | O_APPEND, S_IREAD | S_IWRITE);
		token = token->next;
	}
	return (ret);
}