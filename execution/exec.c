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

//test
void	exec(t_node *node)
{
	if (node->type == "CMD")
		exec_command(node);
	else if (node->type == "PIPE")
		exec_pipe(node);
	else if (node->type == "SEQUENCE")
		exec_sequence(node);
}
