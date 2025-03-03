/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 20:03:02 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/01 20:30:14 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	exec(t_tree *tree)
{
	if (tree->type == "CMD")
		exec_command(tree);
	else if (tree->type == "PIPE")
		exec_pipe(tree);
	else if (tree->type == "SEQUENCE")
		exec_sequence(tree);
	else if(tree->type == "REDIR")
		exec_redir(tree);
	else if(tree->type == "ARG")
		exec_arg(tree);
	else
		type_error("");
}
