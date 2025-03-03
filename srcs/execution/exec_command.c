/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:11:08 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/03 18:17:53 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_command(t_tree *tree, t_context *ctx, char **envp)
{
	int		pid;
	char	*argv[2] = {"ls", 0};
	char	*program_path;

	// get token array from the tree and its length(argc)
	// populate argv with tokens and make the last element NULL
	// need to handle program path manually
	// pass this array to execve alongside envp
	pid = fork();
	if (pid == FORKED_ERROR)
		handle_fork_error();
	else if (pid == FORKED_CHILD)
	{
		dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
		dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
		if (ctx->fd_close >= 0)
			close(ctx->fd_close);
		execve(program_path, argv, envp);
	}
	else
		return (1);
}
