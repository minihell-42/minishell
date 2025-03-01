#ifndef PARSER_H
# define PARSER_H
# include "shell.h"

typedef enum s_token_type
{
	ARG,
	ENV_VAR,
	PIPE,
	HERE_DOC,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	SEMICOLON,
	NEWLINE,
	END
}	t_token_type;

typedef struct s_token
{
	char	*value;
	int		type;
	size_t	len;
	t_token	*next;
	t_token	*prev;
}	t_token;

typedef enum e_node_type
{
	CMD,
	PIPE,
	SEQUENCE,
	REDIR,
	ARG,
}	t_node_type;

typedef enum e_cmd_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	OTHER,
}	t_cmd_type;

typedef struct s_tree
{
	t_node_type	type;
	t_cmd_type	cmd_type;
	char		*value;
	t_tree		*left;
	t_tree		*right;
}	t_tree;

#endif
