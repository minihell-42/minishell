/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:00:28 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/10 11:00:30 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Determines if a given command is a built-in command.
 *
 * @param cmd The command to check.
 *
 * @returns The type of the built-in command.
 */
t_cmd_type	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (OTHER);
}

/**
 * Determines if a given token is a redirection token.
 *
 * @param type The type of the token.
 *
 * @returns 1 if the token is a redirection token, 0 otherwise.
 */
int	is_redir(int type)
{
	return (type == TKN_REDIR_IN || type == TKN_REDIR_OUT
		|| type == TKN_REDIR_APPEND || type == TKN_HERE_DOC);
}

// TODO: Make it more strict
/**
 * Validates the syntax of the tokens.
 *
 * @param tokens A pointer to the head of the token linked list.
 *
 * @returns 1 if the syntax is valid, 0 otherwise.
 */
int	validate_syntax(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (!current || is_redir(current->type) || current->type == TKN_PIPE)
		return (0);
	while (current && current->type != TKN_END)
	{
		if (current->type == TKN_PIPE)
		{
			if (!current->next || is_redir(current->next->type)
				|| current->next->type == TKN_PIPE
				|| current->next->type == TKN_END)
				return (0);
		}
		else if (is_redir(current->type))
		{
			if (!current->next || is_redir(current->next->type)
				|| current->next->type == TKN_PIPE
				|| current->next->type == TKN_END)
				return (0);
		}
		current = current->next;
	}
	return (1);
}
