/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:03:02 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/04 17:18:11 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"
#include <readline/readline.h>

void	exec(t_tree *tree, char **envp)
{
	t_context	ctx;
	int			children;
	int			i;

	i = 0;
	ctx.fd[0] = STDIN_FILENO;
	ctx.fd[1] = STDOUT_FILENO;
	ctx.fd_close = -1;
	children = exec_tree(tree, &ctx, envp);
	while (i < children)
	{
		wait(NULL);
		i++;
	}
}

int	exec_tree(t_tree *tree, t_context *ctx, char **envp)
{
	if (tree->type == NODE_CMD)
		return (exec_command(tree, ctx, envp));
	else if (tree->type == NODE_PIPE)
		return (exec_pipe(tree, ctx, envp));
	else if (tree->type == NODE_SEQUENCE)
		return (exec_sequence(tree, ctx, envp));
	else if (tree->type == NODE_REDIR)
		exec_redir(tree, ctx, envp);
	else if (tree->type == NODE_ARG)
		exec_arg(tree, ctx, envp);
	else
	{
		type_error("Invalid tree type");
		printf("Invalid type");
		return (0);
	}
}

int	main(int argc, char *argv[], char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	(void)envp;
	input = readline("minishell$ ");
	return (0);
}
