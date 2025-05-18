/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 11:53:17 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/18 15:46:44 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Appends an argument to the command node.
 *
 * @param cmd_node The command node to append to.
 * @param arg The argument to append.
 * @param q The quote type of the argument.
 */
void	append_arg(t_tree *cmd_node, char *arg, t_quote_type q)
{
	t_quote_type	*new_quotes;
	char			**new_argv;
	int				old_argc;

	old_argc = cmd_node->argc;
	new_argv = NULL;
	new_quotes = NULL;
	if (!alloc_new_arrays(old_argc, &new_argv, &new_quotes, arg))
		return ;
	copy_and_append_args(cmd_node, new_argv, new_quotes, arg);
	free(cmd_node->argv);
	free(cmd_node->arg_quotes);
	cmd_node->argv = new_argv;
	cmd_node->argc = old_argc + 1;
	cmd_node->arg_quotes = new_quotes;
	cmd_node->arg_quotes[old_argc] = q;
}

/**
 * Appends trailing arguments to the command node.
 *
 * @param root The root node of the AST.
 * @param tokens The token list.
 */
void	append_trailing_args(t_tree *root, t_token **tokens)
{
	t_tree	*cmd_node;

	cmd_node = root;
	while (cmd_node->type == NODE_REDIR)
		cmd_node = cmd_node->left;
	while (*tokens && is_filename_token((*tokens)->type))
	{
		append_arg(cmd_node, ft_strdup((*tokens)->value),
			(*tokens)->quote_type);
		*tokens = (*tokens)->next;
	}
}

/**
 * Extracts the filename from the token list.
 *
 * @param tokens A pointer to the token list.
 * @param file A pointer to the filename string.
 * @param quote A pointer to the quote type.
 *
 * @returns 1 on success, 0 on failure.
 */
int	extract_filename(t_token **tokens, char **file, t_quote_type *quote)
{
	*tokens = (*tokens)->next;
	if (!*tokens || !is_filename_token((*tokens)->type))
		return (0);
	*file = ft_strdup((*tokens)->value);
	*quote = (*tokens)->quote_type;
	*tokens = (*tokens)->next;
	return (1);
}
