/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:44:39 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/05 11:44:41 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Handles redirection tokens in the input string.
 *
 * @param input A pointer to a pointer to the input string.
 * @param is_first_word A pointer to a flag indicating if the token
 * 											is the first word.
 *
 * @returns A pointer to the newly created token.
 */
t_token	*handle_redirection(char **input, int *is_first_word)
{
	t_token	*new_token;

	new_token = tokenize_redirections(*input);
	*input += ft_strlen(new_token->value);
	skip_whitespace(input);
	*is_first_word = 0;
	return (new_token);
}

/**
 * Handles pipe or newline tokens in the input string.
 *
 * @param input A pointer to a pointer to the input string.
 * @param is_first_word A pointer to a flag indicating if the token
 * 											is the first word.
 *
 * @returns A pointer to the newly created token.
 */
t_token	*handle_pipe_or_newline(char **input, int *is_first_word)
{
	t_token	*new_token;

	new_token = tokenize_pipes_and_separators(*input);
	*is_first_word = 1;
	*input += ft_strlen(new_token->value);
	return (new_token);
}

/**
 * Handles command tokens in the input string.
 *
 * @param input A pointer to a pointer to the input string.
 * @param is_first_word A pointer to a flag indicating if the token
 * 											is the first word.
 *
 * @returns A pointer to the newly created token.
 */
t_token	*handle_cmd(char **input, int *is_first_word)
{
	t_token	*new_token;

	new_token = tokenize_cmd_and_arg(input, is_first_word);
	return (new_token);
}
