/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:34:26 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/06 11:34:48 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Prints the tokens in a linked list of tokens.
 *
 * @param tokens A pointer to the head of the linked list of tokens.
 *
 * @returns None
 */
void	print_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		printf("------- NEW TOKEN -------\n");
		printf("Token: %s\n", current->value);
		printf("Type: %d\n", current->type);
		current = current->next;
	}
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
		i = 1;
		while (i < root->argc)
		{
			printf("ARG: %s\n", root->argv[i]);
			i++;
		}
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
