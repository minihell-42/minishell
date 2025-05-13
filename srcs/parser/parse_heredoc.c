/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 13:15:15 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/13 13:15:18 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Creates and initializes the initial heredoc node with command.
 *
 * @param tokens A pointer to the pointer to the tokens.
 *
 * @returns The initial heredoc node or NULL on error.
 */
static t_tree	*create_initial_heredoc(t_token **tokens)
{
	t_tree	*cmd;
	t_tree	*node;

	node = make_redirection_node(NULL, tokens);
	if (!node)
		return (NULL);
	cmd = parse_command(tokens);
	if (!cmd)
	{
		free_ast(node);
		return (NULL);
	}
	node->left = cmd;
	return (node);
}

/**
 * Processes additional redirections in a token stream.
 *
 * @param node The initial node to attach redirections to.
 * @param tokens The token stream.
 *
 * @returns Updated node or NULL on error.
 */
static t_tree	*process_redirections(t_tree *node, t_token **tokens)
{
	t_tree	*new_node;
	t_tree	*result;

	result = node;
	while (*tokens && is_redir((*tokens)->type))
	{
		new_node = make_redirection_node(result, tokens);
		if (!new_node)
		{
			free_ast(result);
			return (NULL);
		}
		result = new_node;
	}
	return (result);
}

/**
 * Parses a heredoc prefix and creates the corresponding AST.
 *
 * @param tokens A pointer to the pointer to the tokens.
 *
 * @returns A pointer to the root of the AST representing the heredoc.
 */
t_tree	*parse_heredoc_prefix(t_token **tokens)
{
	t_tree	*node;

	node = create_initial_heredoc(tokens);
	if (!node)
		return (NULL);
	node = process_redirections(node, tokens);
	if (!node)
		return (NULL);
	append_trailing_args(node, tokens);
	return (node);
}
