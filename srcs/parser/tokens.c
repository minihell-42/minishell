#include "parser.h"
#include <ctype.h>

t_token	*tokenize_redirections(char *input)
{
	t_token	*token;

	if (*input == '>')
	{
		if (*(input + 1) == '>')
			token = create_token(ft_strdup(">>"), TKN_REDIR_APPEND);
		else
			token = create_token(ft_strdup(">"), TKN_REDIR_OUT);
	}
	else if (*input == '<')
	{
		if (*(input + 1) == '<')
			token = create_token(ft_strdup("<<"), TKN_HERE_DOC);
		else
			token = create_token(ft_strdup("<"), TKN_REDIR_IN);
	}
	else
		token = NULL;
	return (token);
}

t_token	*tokenize_pipes_and_separators(char *input)
{
	t_token	*token;

	if (*input == '|')
		token = create_token(ft_strdup("|"), TKN_PIPE);
	else if (*input == '\n')
		token = create_token(ft_strdup("\n"), TKN_NEWLINE);
	else
		token = NULL;
	return (token);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("start\n");
		printf("Token: %s\n", current->value);
		printf("Type: %d\n", current->type);
		current = current->next;
	}
}
