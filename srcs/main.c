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
	char	**copy_env;

	(void)argc;
	(void)argv;
	copy_env = copy_environment(envp);
	if (!copy_env)
	{
		write(STDERR_FILENO, "minishell: envp is NULL\n", 26);
		return (1);
	}
	setup_signals();
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_free_array(copy_env);
			exit(0);
		}
		add_history(input);
		tokens = lexer_tokenizer(input);
		// print_tokens(tokens);
		ast = parse_tokens(tokens);
		free_tokens(tokens);
		// print_ast(ast, 0);
		process_heredocs(ast, copy_env);
		exec(ast, &copy_env);
		free_ast(ast);
		free(input);
	}
	ft_free_array(copy_env);
	rl_clear_history();
	return (0);
}
