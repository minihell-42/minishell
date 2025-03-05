/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:15:04 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/04 13:03:46 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Command to compile:
cc -I includes srcs/parser/parser.c -L/opt/homebrew/lib -lreadline -o minishell
*/
#include "parser.h"

int	main(void)
{
	char	*input;
	t_token	*tokens;

	input = readline("minishell$ ");
	if (input == NULL)
		exit(0);
	tokens = lexer_tokenize(input);
	print_tokens(tokens);
	free(input);
	return (0);
}
