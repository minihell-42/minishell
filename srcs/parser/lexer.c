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

// TODO: divide it in smaller funcions, 
// TODO: implement strndup and ft_isspace, 
// TODO: handle $? expansion
t_token	*lexer_tokenize(char *input)
{
	t_token	*head;
	t_token	*current;
	t_token	*new_token;
	char	*start;
	int		is_first_word;

	head = NULL;
	current = NULL;
	is_first_word = 1;
	while (*input)
	{
		while (*input && isspace(*input))
			input++;
		if (!*input)
			break ;
		if (*input == '<' || *input == '>')
		{
			new_token = tokenize_redirections(input);
			input += ft_strlen(new_token->value) - 1;
			is_first_word = 1;
		}
		else if (*input == '|' || *input == '\n')
		{
			new_token = tokenize_pipes_and_separators(input);
			is_first_word = 1;
		}
		else if (*input == '$')
		{
			if (*(input + 1) == '?')
			{
				new_token = create_token(ft_strdup("$?"), TKN_ENV_VAR);
				input++;
			}
			else
			{
			start = input;
			while (*input && (ft_isalnum(*input) || *input == '_'))
				input++;
			new_token = create_token(strndup(start, input - start), TKN_ENV_VAR);
			}
		}
		else
		{
			start = input;
			while (*input && !isspace(*input) && *input != '|' && *input != '<'
				&& *input != '>' && *input != '\n')
				input++;
			if (is_first_word)
				new_token = create_token(strndup(start, input - start), TKN_CMD);
			else
				new_token = create_token(strndup(start, input - start), TKN_ARG);
			is_first_word = 0;
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