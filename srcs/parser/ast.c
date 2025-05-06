/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:00:02 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/05 11:57:57 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Creates a new node for an abstract syntax tree (AST).
 *
 * @param type The type of the node.
 * @param argv An array of arguments for the node.
 * @param argc The number of arguments in the array.
 * @param cmd_type The command type of the node.
 *
 * @returns A pointer to the newly created AST node.
 */
t_tree	*create_ast_node(t_node_type type, char **argv, int argc,
		t_cmd_type cmd_type)
{
	t_tree	*node;

	node = ft_calloc(1, sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd_type = cmd_type;
	node->argv = argv;
	node->argc = argc;
	node->input_quote = QUOTE_NONE;
	node->output_quote = QUOTE_NONE;
	return (node);
}

/**
 * Recursively frees the memory allocated for the abstract syntax tree nodes.
 *
 * @param root A pointer to the root node of the abstract syntax tree.
 *
 * @returns None
 */
void	free_ast(t_tree *root)
{
	int	i;

	i = -1;
	if (!root)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	if (root->argv)
	{
		while (root->argv[++i])
			free(root->argv[i]);
		free(root->argv);
	}
	if (root->arg_quotes)
		free(root->arg_quotes);
	if (root->type == NODE_REDIR)
	{
		if (root->input_file)
			free(root->input_file);
		if (root->output_file)
			free(root->output_file);
	}
	free(root);
}
