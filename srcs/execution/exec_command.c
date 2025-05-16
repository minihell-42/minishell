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

void	write_cmd_error(t_tree *tree)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tree->argv[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
}

static void	handle_sys_error(char *path, char *msg, t_tree *tree, char **envp)
{
	perror(msg);
	free(path);
	free_exit(tree, &envp);
	exit(EXIT_FAILURE);
}

static void	exec_child_process(t_tree *tree, t_context *ctx, char **envp,
		char *program_path)
{
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
	{
		if (dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO) == -1)
			handle_sys_error(program_path, "minishell: dup2 failed for stdin",
				tree, envp);
		close(ctx->fd[STDIN_FILENO]);
	}
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
	{
		if (dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO) == -1)
			handle_sys_error(program_path, "minishell: dup2 failed for stdout",
				tree, envp);
		close(ctx->fd[STDOUT_FILENO]);
	}
	if (ctx->fd_close >= 0)
		close(ctx->fd_close);
	execve(program_path, tree->argv, envp);
	perror("minishell: execve failed");
	free(program_path);
	free_exit(tree, &envp);
	exit(127);
}

int	exec_external(t_tree *tree, t_context *ctx, char ***envp,
		char *program_path)
{
	struct stat	sb;
	int			pid;

	if (!program_path)
		return (handle_command_not_found(tree));
	if (stat(program_path, &sb) == 0 && S_ISDIR(sb.st_mode))
		return (handle_is_directory(tree, program_path));
	pid = fork();
	if (pid == FORKED_ERROR)
		return (handle_fork_error(program_path));
	else if (pid == FORKED_CHILD)
		exec_child_process(tree, ctx, *envp, program_path);
	free(program_path);
	return (1);
}

int	exec_command(t_tree *tree, t_context *ctx, char ***envp)
{
	char	*program_path;

	if (!tree || !ctx || !envp || !*envp)
		return (-1);
	if (tree->cmd_type >= ECHO && tree->cmd_type <= EXIT)
		return (handle_builtin_with_fd(tree, ctx, envp));
	clean_empty_argv(tree);
	if (!tree->argv || !tree->argv[0] || *(tree->argv[0]) == '\0')
	{
		g_signal = 0;
		return (0);
	}
	program_path = get_program_path(tree->argv[0], *envp);
	return (exec_external(tree, ctx, envp, program_path));
}
