/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_sequence.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 17:48:38 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/03 19:01:25 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	exec_sequence(t_tree *tree, t_context *ctx, char **envp)
{
	t_tree	*current;
	int		children;

	current = tree;
	children = 0;
	while (current)
	{
		children += exec_tree(current->left, ctx, envp);
		current = current->right;
	}
	return (children);
}
