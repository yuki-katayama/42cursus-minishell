#include "../../includes/pipe.h"
#include "../../includes/lexer.h"
#include "../../includes/utils.h"

#include "../../libft/libft.h"

void	lst_add_back(t_token **token, t_token *new)
{
		while (*token)
			token = &(*token)->next;
		*token = new;
}

t_token *tokenize_helper(char **str, t_kind kind, size_t group)
{
		t_token *ret;
		t_token **cur;
		char    *start;

		ret = NULL;
		cur = &ret;
		*str = ft_spaceskip(*str);
		while (!ft_strchr(" <>", **str))
		{
				if(!(ft_malloc_p((void **)&*cur, sizeof(t_token))))
					return (NULL);
				if (**str == '\'')
					*str = ft_untilskip(start = *str + 2, '\''), (*cur)->status = ST_SQ;
                else if (**str == '"')
					*str = ft_untilskip(start = *str + 2, '"'), (*cur)->status = ST_DQ;
				else
				{
						start = *str;
						while (!ft_strchr(" \"'<>", **str))
							++*str;
						(*cur)->status = ST_SP;
				}
				(*cur)->kind = kind;
				(*cur)->group = group;
				(*cur)->next = NULL;
				(*cur)->str = msh_substr(start, *str);
				if ((*cur)->status != ST_SP && (**str == '\'' || **str == '"'))
					++*str;
				cur = &(*cur)->next;
		}
		return (ret);
}

t_node  tokenize(char *str)
{
		t_node  node;
		size_t  group;

		group = 0;
		node = (t_node){};
		str = ft_spaceskip(str);
		while (*str)
		{
			if (*str == '<' && str[1] != '<')
				++str, lst_add_back(&node.input, tokenize_helper(&str, TK_RI, group));
			else if (*str == '<' && str[1] == '<')
				str += 2, lst_add_back(&node.input, tokenize_helper(&str, TK_DRI, group));
			else if (*str == '>' && str[1] != '>')
				++str, lst_add_back(&node.output, tokenize_helper(&str, TK_RO, group));
			else if (*str == '>' && str[1] == '>')
				str += 2, lst_add_back(&node.output, tokenize_helper(&str, TK_DRO, group));
			else
				lst_add_back(&node.cmd, tokenize_helper(&str, TK_CMD, group));
			str = ft_spaceskip(str);
			++group;
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
			if(!(ft_malloc_p((void **)&*cur, sizeof(t_node))))
				return (NULL);
			if (!*cur)
				exit(1);
			start = str;
			while (*str && *str != '|')
			{
				if (*str == '\'')
					str = ft_untilskip(str + 1, '\'');
				else if (*str == '"')
					str = ft_untilskip(str + 1, '"');
				++str;
			}
			*str && (*str++ = '\0');
			**cur = tokenize(start);
			cur = &(*cur)->next;
		}
		return (head);
}

// #include <string.h>
// #include <stdio.h>

// int main(int argc, char const *argv[], char **envp)
// {
// 		t_node *node = nodalize(strdup("echo a | echo $TEST"));
// 		// t_node *node = nodalize(strdup("echo a > test"));
// 		t_env *env = init_env(envp);
// 		multi_level_pipe(node, env);
// 		return 0;
// }