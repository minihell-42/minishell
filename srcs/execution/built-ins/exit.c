/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:23:00 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/13 14:55:17 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_exit(t_tree *tree, char ***envp)
{
	int	status;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (tree->argc == 1)
	{
		free_exit(tree, envp);
		exit(0);
	}
	if (!is_numeric(tree->argv[1]))
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putstr_fd(tree->argv[1], STDERR_FILENO);
		ft_putendl_fd(": numeric argument required", STDERR_FILENO);
		free_exit(tree, envp);
		exit(2);
	}
	status = ft_atoi(tree->argv[1]);
	if (tree->argc > 2)
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	free_exit(tree, envp);
	exit(status % 256);
	return (0);
}
