/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:24:22 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/12 16:26:52 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static int	exec_input_redir(t_tree *tree, t_context *ctx)
{
	int	infile;

	if (tree->redir_type == HERE_DOC)
	{
		infile = tree->here_doc_fd;
		if (infile == -1)
			return (-1);
	}
	else
	{
		infile = open(tree->input_file, O_RDONLY);
		if (infile == -1)
		{
			ctx->last_failed_file = tree->input_file;
			return (-1);
		}
	}
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		close(ctx->fd[STDIN_FILENO]);
	ctx->fd[STDIN_FILENO] = infile;
	return (0);
}

static int	exec_output_redir(t_tree *tree, t_context *ctx)
{
	int	outfile;
	int	flags;

	if (!tree->output_file)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (tree->redir_type == REDIR_APPEND)
		flags |= O_APPEND;
	else if (tree->redir_type == REDIR_OUT)
		flags |= O_TRUNC;
	outfile = open(tree->output_file, flags, 0644);
	if (outfile == -1)
	{
		ctx->last_failed_file = tree->output_file;
		return (-1);
	}
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(ctx->fd[STDOUT_FILENO]);
	ctx->fd[STDOUT_FILENO] = outfile;
	return (0);
}

static int	apply_all_redirs(t_tree *node, t_context *ctx)
{
	if (!node || node->type != NODE_REDIR)
		return (0);
	if (apply_all_redirs(node->left, ctx) == -1)
		return (-1);
	if (node->input_file && exec_input_redir(node, ctx) == -1)
		return (-1);
	if (node->output_file && exec_output_redir(node, ctx) == -1)
		return (-1);
	return (0);
}

int	exec_redir(t_tree *root, t_context *orig_ctx, char ***envp)
{
	t_context	redir_ctx;
	t_tree		*base;

	redir_ctx = *orig_ctx;
	if (apply_all_redirs(root, &redir_ctx) == -1)
	{
		fprintf(stderr, "minishell: %s: %s\n", redir_ctx.last_failed_file,
			strerror(errno));
		return (1);
	}
	base = root;
	while (base->type == NODE_REDIR)
		base = base->left;
	return (exec_tree(base, &redir_ctx, envp));
}
