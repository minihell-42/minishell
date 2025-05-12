/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redir.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:24:22 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:24:23 by samcasti         ###   ########.fr       */
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
		if ((infile = open(tree->input_file, O_RDONLY)) == -1)
		{
			perror("minishell: open file failed");
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
	if ((outfile = open(tree->output_file, flags, 0644)) == -1)
	{
		perror("minishell: open output file failed");
		return (-1);
	}
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(ctx->fd[STDOUT_FILENO]);
	ctx->fd[STDOUT_FILENO] = outfile;
	return (0);
}

int	exec_redir(t_tree *tree, t_context *ctx, char ***envp)
{
	int			children;
	t_context	redir_ctx;

	redir_ctx = *ctx;
	if (tree->input_file)
	{
		if (exec_input_redir(tree, &redir_ctx) == -1)
			return (-1);
	}
	if (tree->output_file)
	{
		if (exec_output_redir(tree, &redir_ctx) == -1)
		{
			if (tree->input_file && redir_ctx.fd[STDIN_FILENO] != STDIN_FILENO)
				close(redir_ctx.fd[STDIN_FILENO]);
			return (-1);
		}
	}
	redir_ctx.fd_close = -1;
	children = exec_tree(tree->left, &redir_ctx, envp);
	if (tree->input_file && redir_ctx.fd[STDIN_FILENO] != STDIN_FILENO)
		close(redir_ctx.fd[STDIN_FILENO]);
	if (tree->output_file && redir_ctx.fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(redir_ctx.fd[STDOUT_FILENO]);
	return (children);
}
