/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:00:16 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/10 11:00:20 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
// this will be removed
#include <ctype.h>

/**
 * Extracts a quoted string from the input string.
 *
 * @param input A pointer to a pointer to the input string.
 * @param quote The quote character to extract.
 *
 * @returns The extracted quoted string.
 */
char	*extract_quoted(char **input, char quote)
{
	char	*start;
	char	*val;
	
	(*input)++;
	start = *input;
	while (**input && **input != quote)
		(*input)++;
	val = strndup(start, *input - start);
	if (**input == quote)
		(*input)++;
	return (val);
}

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
	token->prev = NULL;
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
	while (**input && isspace(**input) && **input != '\n')
		(*input)++;
}
