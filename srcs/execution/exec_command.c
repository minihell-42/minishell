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

static void	write_cmd_error(t_tree *tree)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, tree->argv[0], ft_strlen(tree->argv[0]));
	write(STDERR_FILENO, ": command not found\n", 20);
}

static void	handle_sys_error(char *path, char *msg)
{
	perror(msg);
	free(path);
	exit(EXIT_FAILURE);
}

static void	exec_child_process(t_tree *tree, t_context *ctx, char **envp,
		char *program_path)
{
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		if (dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO) == -1)
			handle_sys_error(program_path, "minishell: dup2 failed for stdin");
		close(ctx->fd[STDIN_FILENO]);
	}
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
			handle_sys_error(program_path, "minishell: dup2 failed for stdout");
		close(ctx->fd[STDOUT_FILENO]);
	}
	if (ctx->fd_close >= 0)
		close(ctx->fd_close);
	execve(program_path, tree->argv, envp);
	perror("minishell: execve failed");
	free(program_path);
	exit(127);
}

int	exec_command(t_tree *tree, t_context *ctx, char **envp)
{
	int		pid;
	char	*program_path;

	if (tree->cmd_type >= ECHO && tree->cmd_type <= EXIT)
		return (handle_builtins(tree, ctx, &envp));
	program_path = get_program_path(tree->argv[0], envp);
	if (!program_path)
	{
		write_cmd_error(tree);
		return (-1);
	}
	pid = fork();
	if (pid == FORKED_ERROR)
	{
		perror("minishell: fork failed");
		free(program_path);
		return (-1);
	}
	else if (pid == FORKED_CHILD)
		exec_child_process(tree, ctx, envp, program_path);
	free(program_path);
	return (1);
}
