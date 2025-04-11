/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:02:09 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/10 11:02:11 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

/**
 * Checks for unmatched quotes in the input string.
 *
 * @param input The input string to check for unmatched quotes.
 *
 * @return 1 if there are unmatched quotes, 0 otherwise.
 */
int	check_unmatched_quotes(char *input)
{
	int	single_quote;
	int	double_quote;

	single_quote = 0;
	double_quote = 0;
	while (*input)
	{
		if (*input == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (*input == '\"' && single_quote == 0)
			double_quote = !double_quote;
		input++;
	}
	if (single_quote || double_quote)
		return (1);
	return (0);
}

// TODO: handle signals
// TODO: improve quotes handling
int	main(void)
{
	char	*input;
	char	*new_input;
	t_token	*tokens;
	t_tree	*ast;

	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		while (check_unmatched_quotes(input))
		{
			new_input = readline("quote> ");
			if (new_input == NULL)
			{
				free(input);
				exit(0);
			}
			input = ft_strjoin(input, new_input);
			free(new_input);
		}
		add_history(input);
		tokens = lexer_tokenizer(input);
		print_tokens(tokens);
		ast = parse_tokens(tokens);
		free_tokens(tokens);
		print_ast(ast, 0);
		free(input);
	}
	return (0);
}
