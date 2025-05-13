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
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tree->argv[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
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

int	exec_command(t_tree *tree, t_context *ctx, char ***envp)
{
	int			pid;
	int			status;
	char		*program_path;
	struct stat	sb;

	if (!tree || !ctx || !envp || !*envp)
		return (-1);
	if (tree->cmd_type >= ECHO && tree->cmd_type <= EXIT)
	{
		if (ctx->fd[STDIN_FILENO] != STDIN_FILENO
			|| ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		{
			pid = fork();
			if (pid == FORKED_ERROR)
			{
				perror("minishell: fork failed");
				return (-1);
			}
			else if (pid == FORKED_CHILD)
			{
				status = handle_builtins(tree, ctx, envp);
				exit(status);
			}
			return (1);
		}
		else
		{
			status = handle_builtins(tree, ctx, envp);
			g_signal = status;
			return (0);
		}
	}
	program_path = get_program_path(tree->argv[0], *envp);
	if (!program_path)
	{
		write_cmd_error(tree);
		g_signal = 127;
		return (-1);
	}
	// new implementation
	if (stat(program_path, &sb) == 0 && S_ISDIR(sb.st_mode))
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(tree->argv[0], STDERR_FILENO);
		ft_putendl_fd(": Is a directory", STDERR_FILENO);
		free(program_path);
		g_signal = 126;
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
		exec_child_process(tree, ctx, *envp, program_path);
	free(program_path);
	return (1);
}
