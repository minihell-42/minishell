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

void	wait_children(int children)
{
	int	i;
	int	sig;
	int	status;

	i = 0;
	while (i < children)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			g_signal = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
		{
			sig = WTERMSIG(status);
			if (sig != SIGPIPE)
				g_signal = sig + 128;
		}
		i++;
	}
}

void	exec(t_tree *tree, char ***envp)
{
	t_context	ctx;
	int			children;

	if (!tree)
		return ;
	if (!envp)
	{
		write(STDERR_FILENO, "minishell: envp is NULL\n", 26);
		return ;
	}
	expand_env_vars_in_tree(tree, *envp);
	ctx.fd[0] = STDIN_FILENO;
	ctx.fd[1] = STDOUT_FILENO;
	ctx.fd_close = -1;
	ctx.last_failed_file = NULL;
	children = exec_tree(tree, &ctx, envp);
	wait_children(children);
}

int	exec_tree(t_tree *tree, t_context *ctx, char ***envp)
{
	if (!tree)
		return (0);
	if (tree->type == NODE_CMD)
		return (exec_command(tree, ctx, envp));
	else if (tree->type == NODE_PIPE)
		return (exec_pipe(tree, ctx, envp));
	else
		return (exec_redir(tree, ctx, envp));
}
