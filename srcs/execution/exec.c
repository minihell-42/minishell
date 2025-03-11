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

void	exec(t_tree *tree, char **envp)
{
	t_context	ctx;
	int			children;
	int			i;
	int			status;

	i = 0;
	ctx.fd[0] = STDIN_FILENO;
	ctx.fd[1] = STDOUT_FILENO;
	ctx.fd_close = -1;
	children = exec_tree(tree, &ctx, envp);
	while (i < children)
	{
		waitpid(-1, &status, 0);
		i++;
	}
}

int	exec_tree(t_tree *tree, t_context *ctx, char **envp)
{
	if (!tree)
		return (0);
	if (tree->type == NODE_CMD)
		return (exec_command(tree, ctx, envp));
	else if (tree->type == NODE_PIPE)
		return (exec_pipe(tree, ctx, envp));
	// else if (tree->type == NODE_SEQUENCE)--> we don't have to handle this
	// 	return (exec_sequence(tree, ctx, envp));
	// else if (tree->type == NODE_REDIR)
	// 	exec_redir(tree, ctx, envp);
	// else if (tree->type == NODE_ARG)
	// 	exec_arg(tree, ctx, envp);
	else
	{
		printf("Invalid type");
		return (0);
	}
}
