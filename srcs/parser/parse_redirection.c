/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:29:11 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/05 10:39:35 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Fills the redirection fields of a node with the given values.
 *
 * @param node The node to fill.
 * @param tkn_type The type of the redirection token.
 * @param file The filename for the redirection.
 * @param q The quote type of the filename.
 */
static void	fill_redirection(t_tree *node, int tkn_type, char *file,
		t_quote_type quote)
{
	if (tkn_type == TKN_REDIR_IN)
	{
		node->redir_type = REDIR_IN;
		node->input_file = file;
		node->input_quote = quote;
	}
	else if (tkn_type == TKN_REDIR_OUT)
	{
		node->redir_type = REDIR_OUT;
		node->output_file = file;
		node->output_quote = quote;
	}
	else if (tkn_type == TKN_REDIR_APPEND)
	{
		node->redir_type = REDIR_APPEND;
		node->output_file = file;
		node->output_quote = quote;
	}
	else
	{
		node->redir_type = HERE_DOC;
		node->input_file = file;
		node->input_quote = quote;
	}
}

static t_tree	*create_command_if_null(char *file)
{
	char	**empty_argv;
	t_tree	*prev;

	empty_argv = malloc(sizeof(*empty_argv));
	if (!empty_argv)
	{
		free(file);
		return (NULL);
	}
	empty_argv[0] = NULL;
	prev = create_ast_node(NODE_CMD, empty_argv, 0, OTHER);
	if (!prev)
	{
		free(empty_argv);
		free(file);
		return (NULL);
	}
	return (prev);
}

/**
 * Creates a new redirection node with the given values.
 *
 * @param prev The previous node.
 * @param tokens The token list.
 *
 * @returns The new redirection node.
 */
t_tree	*make_redirection_node(t_tree *prev, t_token **tokens)
{
	t_quote_type	quote;
	t_token			*tok;
	t_tree			*node;
	char			*file;

	tok = *tokens;
	if (!extract_filename(tokens, &file, &quote))
		return (NULL);
	node = create_ast_node(NODE_REDIR, NULL, 0, OTHER);
	if (!node)
	{
		free(file);
		return (NULL);
	}
	fill_redirection(node, tok->type, file, quote);
	if (prev == NULL)
	{
		prev = create_command_if_null(file);
		if (!prev)
			return (free_ast(node), NULL);
	}
	node->left = prev;
	return (node);
}

static t_tree	*process_redir_first(t_token **tokens)
{
	t_tree	*node;
	t_tree	*new_node;

	node = make_redirection_node(NULL, tokens);
	if (!node)
		return (NULL);
	while (*tokens && is_redir((*tokens)->type))
	{
		new_node = make_redirection_node(node, tokens);
		if (!new_node)
		{
			free_ast(node);
			return (NULL);
		}
		node = new_node;
	}
	append_trailing_args(node, tokens);
	return (node);
}

/**
 * Parses a redirection and creates an
 * abstract syntax tree (AST) for the redirection.
 *
 * @param tokens A pointer to the pointer to the tokens
 * representing the redirection.
 *
 * @returns A pointer to the root of the AST representing the redirection.
 */
t_tree	*parse_redirection(t_token **tokens)
{
	t_tree	*node;
	t_tree	*new_node;

	if (*tokens && is_redir((*tokens)->type))
		return (process_redir_first(tokens));
	node = parse_command(tokens);
	if (!node)
		return (NULL);
	while (*tokens && is_redir((*tokens)->type))
	{
		new_node = make_redirection_node(node, tokens);
		if (!new_node)
		{
			free_ast(node);
			return (NULL);
		}
		node = new_node;
	}
	append_trailing_args(node, tokens);
	return (node);
}
