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
 * Gets a fragment from the input string.
 *
 * @param input Double pointer to the input string.
 *
 * @returns The extracted fragment.
 */
static char	*get_frag(char **input)
{
	char	quote;
	char	*frag;

	if (**input == '\'' || **input == '"')
	{
		quote = **input;
		frag = extract_quoted(input, quote);
	}
	else
	{
		frag = ft_strndup(*input, 1);
		(*input)++;
	}
	return (frag);
}

/**
 * Appends a fragment to the accumulated string.
 *
 * @param acc The accumulated string.
 * @param frag The fragment to append.
 *
 * @returns The updated accumulated string.
 */
static char	*append_frag(char *acc, char *frag)
{
	char	*tmp;

	tmp = acc;
	acc = ft_strjoin(acc, frag);
	free(tmp);
	return (acc);
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
 * Tokenizes the input command and argument.
 *
 * @param input Double pointer to the input string.
 * @param is_first_word Pointer to a flag indicating if it is the first word.
 *
 * @returns A pointer to the tokenized command or argument.
 */
t_token	*tokenize_cmd_and_arg(char **input, int *is_first_word)
{
	t_quote_type	qtype;
	t_token			*token;
	char			*frag;
	char			*acc;

	acc = ft_strdup("");
	qtype = QUOTE_NONE;
	while (**input && !ft_isspace(**input) && **input != '|' && **input != '<'
		&& **input != '>' && **input != '\n')
	{
		detect_quote(**input, &qtype);
		frag = get_frag(input);
		acc = append_frag(acc, frag);
		free(frag);
	}
	if (*is_first_word)
	{
		token = create_token(acc, TKN_CMD);
		*is_first_word = 0;
	}
	else
		token = create_token(acc, TKN_ARG);
	token->quote_type = qtype;
	return (token);
}
