/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:47:18 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 15:47:53 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

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

/**
 * Determines if a given token is a filename token.
 *
 * @param type The type of the token.
 *
 * @returns 1 if the token is a filename token, 0 otherwise.
 */
int	is_filename_token(int type)
{
	if (type == TKN_CMD || type == TKN_ARG)
		return (1);
	return (0);
}

int	alloc_new_arrays(int old_argc, char ***new_argv, t_quote_type **new_quotes,
		char *arg)
{
	*new_argv = malloc((old_argc + 2) * sizeof(**new_argv));
	if (!*new_argv)
	{
		free(arg);
		return (0);
	}
	*new_quotes = malloc((old_argc + 1) * sizeof(**new_quotes));
	if (!*new_quotes)
	{
		free(*new_argv);
		free(arg);
		return (0);
	}
	return (1);
}

void	copy_and_append_args(t_tree *cmd_node, char **new_argv,
		t_quote_type *new_quotes, char *arg)
{
	int	i;
	int	old_argc;

	i = 0;
	old_argc = cmd_node->argc;
	while (i < old_argc)
	{
		new_argv[i] = cmd_node->argv[i];
		new_quotes[i] = cmd_node->arg_quotes[i];
		i++;
	}
	new_argv[old_argc] = arg;
	new_quotes[old_argc] = cmd_node->arg_quotes[i];
	new_argv[old_argc + 1] = NULL;
}
