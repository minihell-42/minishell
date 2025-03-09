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

void	skip_whitespace(char **input)
{
	while (**input && isspace(**input))
		(*input)++;
}

t_token	*lexer_tokenize(char *input)
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
		skip_whitespace(&input);
		if (!*input)
			break ;
		if (*input == '<' || *input == '>')
		{
			new_token = tokenize_redirections(input);
			input += ft_strlen(new_token->value) - 1;
			skip_whitespace(&input);
			is_first_word = 0;
		}
		else if (*input == '|' || *input == '\n')
		{
			new_token = tokenize_pipes_and_separators(input);
			is_first_word = 1;
			input += ft_strlen(new_token->value) - 1;
		}
		else if (*input == '$')
			new_token = tokenize_env_var(&input);
		else
			new_token = tokenize_cmd_and_arg(&input, &is_first_word);
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
	current->next = create_token(ft_strdup("\0"), TKN_END);
	return (head);
}