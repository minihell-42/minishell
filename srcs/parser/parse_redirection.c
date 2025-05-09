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
static int	is_filename_token(int type)
{
	if (type == TKN_CMD || type == TKN_ARG)
		return (1);
	return (0);
}

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

/**
 * Creates a new redirection node with the given values.
 *
 * @param prev The previous node.
 * @param tokens The token list.
 *
 * @returns The new redirection node.
 */
static t_tree	*make_redirection_node(t_tree *prev, t_token **tokens)
{
	t_quote_type	quote;
	t_token			*tok;
	t_tree			*node;
	char			*file;

	tok = *tokens;
	*tokens = (*tokens)->next;
	if (!*tokens || !is_filename_token((*tokens)->type))
		return (NULL);
	file = ft_strdup((*tokens)->value);
	quote = (*tokens)->quote_type;
	*tokens = (*tokens)->next;
	node = create_ast_node(NODE_REDIR, NULL, 0, OTHER);
	if (!node)
		return (NULL);
	fill_redirection(node, tok->type, file, quote);
	node->left = prev;
	return (node);
}

static void	append_trailing_args(t_tree *root, t_token **tokens)
{
	t_quote_type	*old_quotes;
	t_quote_type	q;
	t_tree				*cmd_node;
	char					**old_argv;
	char					*new_argv;
	int						old_argc;
	int						i;

	cmd_node = root;
	while (cmd_node->type == NODE_REDIR)
		cmd_node = cmd_node->left;
	while (*tokens && is_filename_token((*tokens)->type))
	{
		new_argv = ft_strdup((*tokens)->value);
		q = (*tokens)->quote_type;
		old_argc = cmd_node->argc;
		old_argv = cmd_node->argv;
		old_quotes = cmd_node->arg_quotes;
		cmd_node->argv = malloc((old_argc + 2) * sizeof(char*));
		cmd_node->arg_quotes = malloc((old_argc + 1) * sizeof(t_quote_type));
		i = 0;
		while(i < old_argc)
		{
			cmd_node->argv[i] = old_argv[i];
			cmd_node->arg_quotes[i] = old_quotes[i];
			i++;
		}
		cmd_node->argv[old_argc] = new_argv;
		cmd_node->arg_quotes[old_argc] = q;
		cmd_node->argv[old_argc + 1] = NULL;
		cmd_node->argc = old_argc + 1;
		*tokens = (*tokens)->next;
	}
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
	t_tree	*cmd;
	t_tree	*new_cmd;

	cmd = parse_command(tokens);
	if (!cmd)
		return (NULL);
	while (*tokens && is_redir((*tokens)->type))
	{
		new_cmd = make_redirection_node(cmd, tokens);
		if (!new_cmd)
			return (free_ast(cmd), NULL);
		cmd = new_cmd;
	}
	append_trailing_args(cmd, tokens);
	return (cmd);
}
