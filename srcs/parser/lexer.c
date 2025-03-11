/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 12:53:03 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/04 13:02:20 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
// this will be removed
#include <ctype.h>

/**
 * Parses the input string to extract the next token.
 *
 * @param input A pointer to the input string.
 * @param is_first_word A pointer to a flag indicating if the token is 
 * the first word.
 *
 * @returns A pointer to the next token extracted from the input string.
 */
t_token	*get_next_token(char **input, int *is_first_word)
{
	t_token	*new_token;

	skip_whitespace(input);
	if (!**input)
		return (NULL);
	if (**input == '<' || **input == '>')
	{
		new_token = tokenize_redirections(*input);
		*input += ft_strlen(new_token->value) - 1;
		skip_whitespace(input);
		*is_first_word = 0;
	}
	else if (**input == '|' || **input == '\n')
	{
		new_token = tokenize_pipes_and_separators(*input);
		*is_first_word = 1;
		*input += ft_strlen(new_token->value) - 1;
	}
	else if (**input == '$')
		new_token = tokenize_env_var(input);
	else
		new_token = tokenize_cmd_and_arg(input, is_first_word);
	return (new_token);
}

/**
 * Appends a new token to the linked list of tokens.
 *
 * @param head Pointer to the head of the linked list.
 * @param current Pointer to the current token in the linked list.
 * @param new_token Pointer to the new token to be appended.
 *
 * @returns None
 */
void	append_token(t_token **head, t_token **current, t_token *new_token)
{
	if (!*head)
		*head = new_token;
	else
	{
		(*current)->next = new_token;
		new_token->prev = *current;
	}
	*current = new_token;
}

/**
 * Tokenizes the input string and creates a linked list of tokens.
 *
 * @param input The input string to tokenize.
 *
 * @returns A pointer to the head of the token linked list.
 */
t_token	*lexer_tokenizer(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	int		is_first_word;

	head = NULL;
	current = NULL;
	is_first_word = 1;
	while (*input)
	{
		new_token = get_next_token(&input, &is_first_word);
		if (!new_token)
			return (NULL);
		append_token(&head, &current, new_token);
		input++;
	}
	current->next = create_token(ft_strdup("\0"), TKN_END);
	return (head);
}
