/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 18:20:08 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/13 18:20:17 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	handle_builtin_with_fd(t_tree *tree, t_context *ctx, char ***envp)
{
	int	pid;
	int	status;

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
			free_exit(tree, envp);
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

void	clean_empty_argv(t_tree *tree)
{
	char	*empty_arg_to_free;
	int		i;

	while (tree->argv && tree->argv[0] && *(tree->argv[0]) == '\0'
		&& tree->argv[1] != NULL)
	{
		empty_arg_to_free = tree->argv[0];
		i = 0;
		while (tree->argv[i + 1] != NULL)
		{
			tree->argv[i] = tree->argv[i + 1];
			i++;
		}
		tree->argv[i] = NULL;
		if (empty_arg_to_free)
			free(empty_arg_to_free);
	}
}

int	handle_command_not_found(t_tree *tree)
{
	write_cmd_error(tree);
	g_signal = 127;
	return (-1);
}

int	handle_is_directory(t_tree *tree, char *program_path)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(tree->argv[0], STDERR_FILENO);
	ft_putendl_fd(": Is a directory", STDERR_FILENO);
	free(program_path);
	g_signal = 126;
	return (-1);
}

int	handle_fork_error(char *program_path)
{
	perror("minishell: fork failed");
	free(program_path);
	return (-1);
}
