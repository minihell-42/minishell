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

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	t_token	*tokens;
	t_tree	*ast;
	char **copy_env;
	(void)argc;
	(void)argv;

	copy_env = copy_environment(envp);
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			exit(0);
		add_history(input);
		tokens = lexer_tokenizer(input);
		// print_tokens(tokens);
		ast = parse_tokens(tokens);
		free_tokens(tokens);
		// print_ast(ast, 0);
		exec(ast, copy_env);
		free(input);
	}
	return (0);
}
