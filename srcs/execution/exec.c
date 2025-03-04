/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:03:02 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/03 18:23:52 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

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
	if (tree->type == CMD)
		return (exec_command(tree, ctx, envp));
	else if (tree->type == PIPE)
		return (exec_pipe(tree, ctx, envp));
	else if (tree->type == SEQUENCE)
		return (exec_sequence(tree, ctx, envp));
	else if (tree->type == REDIR)
		exec_redir(tree, ctx, envp);
	else if (tree->type == ARG)
		exec_arg(tree, ctx, envp);
	else
	{
		type_error("Invalid tree type");
		return (0);
	}
}
