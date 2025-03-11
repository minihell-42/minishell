/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:00:34 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/10 11:00:36 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <ctype.h>

/**
 * Tokenizes redirection symbols in the input string.
 *
 * @param input The input string to tokenize.
 *
 * @returns A token representing the redirection symbol found in the input.
 */
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

/**
 * Tokenizes pipes and separators in the input string.
 *
 * @param input The input string to tokenize.
 *
 * @returns A token representing the pipe or newline character.
 */
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

/**
 * Tokenizes an environment variable from the input string.
 *
 * @param input A pointer to the input string containing 
 * the environment variable.
 *
 * @returns A token representing the environment variable.
 */
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

/**
 * Tokenizes the input command and argument.
 *
 * @param input Double pointer to the input string.
 * @param is_first_word Pointer to a flag indicating if it is the first word.
 *
 * @returns A pointer to the tokenized command or argument.
 */
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

/**
 * Prints the tokens in a linked list of tokens.
 *
 * @param tokens A pointer to the head of the linked list of tokens.
 *
 * @returns None
 */
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
