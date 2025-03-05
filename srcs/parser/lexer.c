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

// TODO: divide it in smaller funcions, implement ft_strndup, implement ft_isspace, and handle errors
// TODO: handle quotes
// TODO: handle ARG token
// TODO: handle $? expansion
t_token	*lexer_tokenize(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	char	*start;

	head = NULL;
	current = NULL;
	while (*input)
	{
		while (*input && isspace(*input))
			input++;
		if (!*input)
			break ;
		if (*input == '|')
			new_token = create_token(ft_strdup("|"), TKN_PIPE);
		else if (*input == ';')
			new_token = create_token(ft_strdup(";"), TKN_SEMICOLON);
		else if (*input == '>')
		{
			if (*(input + 1) == '>')
			{
				new_token = create_token(ft_strdup(">>"), TKN_REDIR_APPEND);
				input++;
			}
			else
				new_token = create_token(ft_strdup(">"), TKN_REDIR_OUT);
		}
		else if (*input == '<')
		{
			if (*(input + 1) == '<')
			{
				new_token = create_token(ft_strdup("<<"), TKN_HERE_DOC);
				input++;
			}
			else
				new_token = create_token(ft_strdup("<"), TKN_REDIR_IN);
		}
		else if (*input == '\n')
			new_token = create_token(ft_strdup("\n"), TKN_NEWLINE);
		else if (*input == '$')
		{
			start = input;
			while (*input && (ft_isalnum(*input) || *input == '_'))
				input++;
			new_token = create_token(strndup(start, input - start), TKN_ENV_VAR);
		}
		else
		{
			start = input;
			while (*input && !isspace(*input) && *input != '|' && *input != ';' && *input != '<' && *input != '>' && *input != '\n')
				input++;
			new_token = create_token(strndup(start, input - start), TKN_CMD);
		}
		if (!new_token)
			return (NULL);
		if (!head)
			head = new_token;
		else
		{
			current->next = new_token;
			new_token->prev = current;
		}
		current = new_token;
		input++;
	}
	new_token = create_token(ft_strdup("\0"), TKN_END);
	if (current)
		current->next = new_token;
	else
		head = new_token;
	return (head);
}