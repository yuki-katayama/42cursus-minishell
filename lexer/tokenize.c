#include "../includes/lexer.h"
#include "../includes/utils.h"

t_token	*tokenize_helper(char **str, char c, t_token_kind kind)
{
	t_token	*ret;
	char	*start;

	ret = malloc(sizeof(*ret));
	if (!ret)
		exit(1);
	ret->kind = kind;
	ret->next = NULL;
	if (!(kind == TK_CMD || kind == TK_OP))
		++*str;
	*str = skip(*str);
	start = *str;
	while (**str && **str != c)
		++*str;
	ret->str = msh_substr(start, (*str)++);
	return (ret);
}

t_token	*select_token(char **str, int *cmd_flag)
{
	t_token	*ret;

	if (**str == '\'')
		ret = tokenize_helper(str, '\'', TK_SQ);
	else if (**str == '"')
		ret = tokenize_helper(str, '\"', TK_DQ);
	else if (**str == '<' && *((*str) + 1) != '<')
		ret = tokenize_helper(str, ' ', TK_RI);
	else if (**str == '<' && *((*str) + 1) == '<')
		ret = tokenize_helper(str, ' ', TK_DRI);
	else if (**str == '>' && *((*str) + 1) != '>')
		ret = tokenize_helper(str, ' ', TK_RO);
	else if (**str == '>' && *((*str) + 1) == '>')
		ret = tokenize_helper(str, ' ', TK_DRO);
	else if (*cmd_flag)
		ret = tokenize_helper(str, ' ', TK_CMD);
	else
		ret = tokenize_helper(str, ' ', TK_OP);
	if (ret->kind == TK_CMD)
		*cmd_flag = 0;
	return (ret);
}

t_token	*tokenize(char *str)
{
	t_token			*head;
	t_token			**cur;
	int				cmd_flag;

	head = NULL;
	cur = &head;
	cmd_flag = 1;
	while (str && *str)
	{
		str = skip(str);
		(*cur) = select_token(&str, &cmd_flag);
		cur = &(*cur)->next;
	}
	return (head);
}

t_node	*nodalize(char *str)
{
	t_node			*head;
	t_node			**cur;
	char			*start;

	head = NULL;
	cur = &head;
	while (str && *str)
	{
		*cur = malloc(sizeof(**cur));
		if (!*cur)
			exit(1);
		start = str;
		while (*str && *str != '|')
		{
			if (*str == '\'')
				str = skip_until_c(str, '\'');
			if (*str == '"')
				str = skip_until_c(str, '"');
			++str;
		}
		!*str && (*str++ = '\0');
		**cur = (t_node){.token = tokenize(start)};
		cur = &(*cur)->next;
	}
	return (head);
}
