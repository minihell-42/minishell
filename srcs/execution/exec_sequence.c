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

int	exec_sequence(t_tree *tree, t_context *ctx, char **envp)
{
	t_tree		*current;
	int			children;
	t_context	seq_ctx;
	int			status;

	current = tree;
	children = 0;
	while (current)
	{
		seq_ctx = *ctx;
		seq_ctx.fd[STDIN_FILENO] = STDIN_FILENO;
		seq_ctx.fd[STDOUT_FILENO] = STDOUT_FILENO;
		seq_ctx.fd_close = -1;
		children += exec_tree(current->left, &seq_ctx, envp);
		waitpid(-1, &status, 0);
		if (current->right && current->right->type != NODE_SEQUENCE)
		{
			children += exec_tree(current->right, &seq_ctx, envp);
			waitpid(-1, &status, 0);
			break ;
		}
		current = current->right;
	}
	return (children);
}
