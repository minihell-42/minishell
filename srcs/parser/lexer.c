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

#include "shell.h"
/* TODO: divide it in smaller funcions and add all the cases
t_token	*lexer_tokenize(char *input)
{
	t_token	*tokens;
	t_token	*current;
	int		i;
	int		len;

	tokens = NULL;
	current = NULL;
	i = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (is_whitespace(input[i]))
			i++;
		else if (is_operator(input[i]))
		{
			current = create_token(input[i], OPERATOR);
			i++;
		}
		else if (is_quote(input[i]))
		{
			current = create_token(input[i], QUOTE);
			i++;
		}
		else
		{
			current = create_token(input[i], ARGUMENT);
			i++;
		}
		if (current)
		{
			if (!tokens)
				tokens = current;
			else
				current->next = create_token(input[i], ARGUMENT);
		}
	}
	return (tokens);
}*/
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
