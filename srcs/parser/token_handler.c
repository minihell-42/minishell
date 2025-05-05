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

t_token	*handle_quote(char **input, int *is_first_word)
{
	t_token	*new_token;
	char	quote;
	char	*word;

	quote = **input;
	word = extract_quoted(input, quote);
	new_token = create_token(word, TKN_ARG);
	if (quote == '\'')
		new_token->quote_type = QUOTE_SINGLE;
	else
		new_token->quote_type = QUOTE_DOUBLE;
	*is_first_word = 0;
	return (new_token);
}

t_token	*handle_redirection(char **input, int *is_first_word)
{
	t_token	*new_token;

	new_token = tokenize_redirections(*input);
	*input += ft_strlen(new_token->value) - 1;
	skip_whitespace(input);
	*is_first_word = 0;
	return (new_token);
}

t_token	*handle_pipe_or_newline(char **input, int *is_first_word)
{
	t_token	*new_token;

	new_token = tokenize_pipes_and_separators(*input);
	*is_first_word = 1;
	*input += ft_strlen(new_token->value) - 1;
	return (new_token);
}

t_token	*handle_cmd(char **input, int *is_first_word)
{
	t_token	*new_token;

	new_token = tokenize_cmd_and_arg(input, is_first_word);
	return (new_token);
}
