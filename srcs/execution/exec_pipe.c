/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 16:10:10 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/04 15:19:16 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_left_side(t_tree *left_side, t_context *ctx, char **envp, int pid[2])
{
	t_context	left_ctx;

	left_ctx = *ctx;
	left_ctx.fd[STDOUT_FILENO] = pid[STDOUT_FILENO];
	left_ctx.fd_close = pid[STDIN_FILENO];
	return (exec_tree(left_side, &left_ctx, envp));
}

int	exec_right_side(t_tree *right_side, t_context *ctx, char **envp, int pid[2])
{
	t_context	right_ctx;

	right_ctx = *ctx;
	right_ctx.fd[STDIN_FILENO] = pid[STDIN_FILENO];
	right_ctx.fd_close = pid[STDOUT_FILENO];
	return (exec_tree(right_side, &right_ctx, envp));
}

int	exec_pipe(t_tree *tree, t_context *ctx, char **envp)
{
	int		pid[2];
	int		children;
	t_tree	*left_side;
	t_tree	*right_side;

	children = 0;
	if (pipe(pid) == -1)
	{
		perror("minishell: pipe failed");
		return (-1);
	}
	left_side = tree->left;
	right_side = tree->right;
	children += exec_left_side(left_side, ctx, envp, pid);
	children += exec_right_side(right_side, ctx, envp, pid);
	if (close(pid[STDIN_FILENO]) == -1 || close(pid[STDOUT_FILENO]) == -1)
	{
		perror("minishell: close failed");
		return (-1);
	}
	return (children);
}
