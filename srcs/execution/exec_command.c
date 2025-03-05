/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:11:08 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/04 17:23:27 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	exec_child_process(t_tree *tree, t_context *ctx, char **envp,
		char *program_path)
{
	dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
	dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
	if (ctx->fd_close >= 0)
		close(ctx->fd_close);
	execve(program_path, tree->argv, envp);
	perror("execve failed");
	free(program_path);
	exit(EXIT_FAILURE);
}

int	exec_command(t_tree *tree, t_context *ctx, char **envp)
{
	int		pid;
	char	*program_path;

	program_path = get_program_path(tree->argv[0], envp);
	if (!program_path)
	{
		write(STDERR_FILENO, "bash: command not found\n", 24);
		return (-1);
	}
	pid = fork();
	if (pid == FORKED_ERROR)
	{
		printf("Fork error");
		free(program_path);
		return (-1);
	}
	else if (pid == FORKED_CHILD)
		exec_child_process(tree, ctx, envp, program_path);
	free(program_path);
	return (1);
}
