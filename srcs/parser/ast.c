/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:00:02 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/10 11:00:06 by dgomez-a         ###   ########.fr       */
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

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd_type = cmd_type;
	node->argv = argv;
	node->argc = argc;
	node->left = NULL;
	node->right = NULL;
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
	if (!root)
		return ;
	free_ast(root->left);
	free_ast(root->right);
	free(root->argv);
	free(root);
}

/**
 * Recursively prints the abstract syntax tree (AST) of a given tree node.
 *
 * @param root Pointer to the root of the tree node.
 * @param depth The current depth in the tree.
 *
 * @returns None
 */
void	print_ast(t_tree *root, int depth)
{
	int	i;

	if (!root)
		return ;
	i = 0;
	printf("\n------- NEW TREE NODE-------\n");
	while (i < depth)
	{
		printf("  ");
		i++;
	}
	if (root->type == NODE_CMD)
	{
		printf("CMD: %s\n", root->argv[0]);
		printf("CMD_TYPE: %d\n", root->cmd_type);
		for (i = 1; i < root->argc; i++)
			printf("ARG: %s\n", root->argv[i]);
	}
	else if (root->type == NODE_PIPE)
		printf("PIPE\n");
	else if (root->type == NODE_REDIR)
	{
		printf("REDIR\n");
		printf("REDIR_TYPE: %d\n", root->redir_type);
		if (root->input_file)
			printf("INPUT_FILE: %s\n", root->input_file);
		if (root->output_file)
			printf("OUTPUT_FILE: %s\n", root->output_file);
	}
	print_ast(root->left, depth + 1);
	print_ast(root->right, depth + 1);
}
