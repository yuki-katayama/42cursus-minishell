#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>

typedef struct s_token	t_token;
typedef struct s_node	t_node;
typedef enum e_token_kind	t_token_kind;

enum e_token_kind
{
	TK_CMD,
	TK_OP,
	TK_SQ,
	TK_DQ,
	TK_RI,
	TK_DRI,
	TK_RO,
	TK_DRO
};

struct s_token
{
	t_token_kind	kind;
	char			*str;
	t_token			*next;
};

struct s_node
{
	t_token	*cmd;
	t_token	*input;
	t_token	*output;
	t_node	*next;
};

#endif