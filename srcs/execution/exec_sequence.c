/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:48:38 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/03 19:01:25 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	init_seq_context(t_context *seq_ctx, t_context *ctx)
{
	*seq_ctx = *ctx;
	seq_ctx->fd[STDIN_FILENO] = STDIN_FILENO;
	seq_ctx->fd[STDOUT_FILENO] = STDOUT_FILENO;
	seq_ctx->fd_close = -1;
}

static int	wait_for_children(int last_children)
{
	int	status;

	while (last_children > 0)
	{
		waitpid(-1, &status, 0);
		last_children--;
	}
	return (0);
}

static int	exec_left_command(t_tree *current, t_context *ctx, char **envp)
{
	t_context	seq_ctx;
	int			last_children;

	init_seq_context(&seq_ctx, ctx);
	last_children = exec_tree(current->left, &seq_ctx, envp);
	if (last_children > 0)
		wait_for_children(last_children);
	return (last_children);
}

static int	exec_last_command(t_tree *current, t_context *ctx, char **envp,
		int *children)
{
	t_context	seq_ctx;
	int			last_children;

	init_seq_context(&seq_ctx, ctx);
	last_children = exec_tree(current->right, &seq_ctx, envp);
	if (last_children > 0)
		wait_for_children(last_children);
	*children += last_children;
	return (0);
}

int	exec_sequence(t_tree *tree, t_context *ctx, char **envp)
{
	t_tree	*current;
	int		children;
	int		last_children;

	current = tree;
	children = 0;
	while (current)
	{
		last_children = exec_left_command(current, ctx, envp);
		if (current->right && current->right->type != NODE_SEQUENCE)
		{
			exec_last_command(current, ctx, envp, &children);
			break ;
		}
		children += last_children;
		current = current->right;
	}
	return (children);
}
