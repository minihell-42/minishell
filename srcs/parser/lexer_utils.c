#include "parser.h"
// this will be removed
#include <ctype.h>

/**
 * Creates a new token with the given value and type.
 *
 * @param value The value of the token.
 * @param type The type of the token.
 *
 * @returns A pointer to the newly created token.
 */
t_token	*create_token(char *value, t_token_type type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

/**
 * Frees the memory allocated for a linked list of tokens.
 *
 * @param tokens A pointer to the head of the token linked list.
 *
 * @returns None
 */
void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
}

/**
 * Skips over whitespace characters in a string.
 *
 * @param input A pointer to a pointer to the input string.
 *
 * @returns None
 */
void	skip_whitespace(char **input)
{
	while (**input && isspace(**input))
		(*input)++;
}
