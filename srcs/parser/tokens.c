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

t_token	*tokenize_env_var(char **input)
{
	t_token	*token;
	char	*start;

	start = *input;
	if (*(*input + 1) == '?')
	{
		(*input) += 2;
		token = create_token(ft_strdup("$?"), TKN_ENV_VAR);
	}
	(*input)++;
	while (*input && (ft_isalnum(**input) || **input == '_'))
		(*input)++;
	token = create_token(strndup(start, *input - start), TKN_ENV_VAR);
	return (token);
}

t_token	*tokenize_cmd_and_arg(char **input, int *is_first_word)
{
	t_token	*token;
	char	*start;

	start = *input;
	while (**input && !isspace(**input) && **input != '|' && **input != '<'
		&& **input != '>' && **input != '\n')
		(*input)++;
	if (*is_first_word)
	{
		token = create_token(strndup(start, *input - start), TKN_CMD);
		*is_first_word = 0;
	}
	else
		token = create_token(strndup(start, *input - start), TKN_ARG);
	return (token);
}

void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("------- NEW TOKEN -------\n");
		printf("Token: %s\n", current->value);
		printf("Type: %d\n", current->type);
		current = current->next;
	}
}
