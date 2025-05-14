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

void	free_exit(t_tree *ast, char ***envp)
{
	if (envp)
		ft_free_array(*envp);
	if (ast)
		free_ast(ast);
	rl_clear_history();
}

void	main_loop(char **envp)
{
	char	*input;
	t_token	*tokens;
	t_tree	*ast;

	ast = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
		{
			ft_free_array(envp);
			exit(0);
		}
		add_history(input);
		tokens = lexer_tokenizer(input);
		ast = parse_tokens(tokens);
		free(input);
		free_tokens(tokens);
		process_heredocs(ast, envp);
		exec(ast, &envp);
		if (ast)
			free_ast(ast);
	}
}

int	main(int argc, char **argv, char **envp)
{
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
	main_loop(copy_env);
	return (0);
}
