#include "../includes/lexer.h"
#include "../includes/utils.h"
#include "../includes/pipe.h"


void	lst_add_back(t_token **token, t_token *new)
{
	while (*token)
		token = &(*token)->next;
	*token = new;
}

t_token	*tokenize_helper(char **str, char c, t_token_kind kind)
{
	t_token	*ret;
	char	*start;

	ret = malloc(sizeof(*ret));
	if (!ret)
		exit(1);
	ret->kind = kind;
	ret->next = NULL;
	if (kind == TK_DRI || kind == TK_DRO)
		*str += 2;
	if (kind == TK_SQ || kind == TK_DQ || kind == TK_RI || kind == TK_RO)
		++*str;
	*str = skip(*str);
	start = *str;
	while (**str && **str != c)
		++*str;
		ret->str = msh_substr(start, *str);
	if (**str)
		++*str;
	return (ret);
}

t_node	tokenize(char *str)
{
	t_node	node;

	node = (t_node){};
	while (*str)
	{
		str = skip(str);
		if (*str == '\'')
			lst_add_back(&node.cmd, tokenize_helper(&str, '\'', TK_SQ));
		else if (*str == '"')
			lst_add_back(&node.cmd, tokenize_helper(&str, '"', TK_DQ));
		else if (*str == '<' && *(str + 1) != '<')
			lst_add_back(&node.input, tokenize_helper(&str, ' ', TK_RI));
		else if (*str == '<' && *(str + 1) == '<')
			lst_add_back(&node.input, tokenize_helper(&str, ' ', TK_DRI));
		else if (*str == '>' && *(str + 1) != '>')
			lst_add_back(&node.output, tokenize_helper(&str, ' ', TK_RO));
		else if (*str == '>' && *(str + 1) == '>')
			lst_add_back(&node.output, tokenize_helper(&str, ' ', TK_DRO));
		else
			lst_add_back(&node.cmd, tokenize_helper(&str, ' ', TK_CMD));
	}
	return (node);
}

t_node	*nodalize(char *str)
{
	t_node	*head;
	t_node	**cur;
	char	*start;

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
		*str && (*str++ = '\0');
		**cur = tokenize(start);
		cur = &(*cur)->next;
	}
	return (head);
}

#include <string.h>

int main(int argc, char const *argv[], char **envp)
{
	t_node *node = nodalize(strdup("cat tokenize.c | cat | cat  outfile"));
	t_env *env = init_env(envp);
	multi_level_pipe(node, env);
	return 0;
}
