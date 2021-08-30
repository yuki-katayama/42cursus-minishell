#include "../../includes/pipe.h"
#include "../../libft/libft.h"

static int	is_marge(t_token *cur, t_token *next)
{
	return (cur->group == next->group && !(cur->status == ST_SP && next->status == ST_SP));
}
//aaa"bbb"
static void	marge_token_helper(t_token **token)
{
	char	*tmp_str;

	while (*token && (*token)->next)
	{
		if (is_marge(*token, (*token)->next))
		{
			tmp_str = ft_strjoin((*token)->str, (*token)->next->str);
			free((*token)->next->str);
			(*token)->next->str = tmp_str;
			free((*token)->str);
			free(*token);
			*token = (*token)->next;
		}
		else
			token = &(*token)->next;
	}
}

void	marge_token(t_node *node)
{
	marge_token_helper(&node->cmd);
	marge_token_helper(&node->input);
	marge_token_helper(&node->output);
}