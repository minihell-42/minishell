/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:15:04 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/04 13:03:46 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Command to compile:
cc -I includes srcs/parser/parser.c -L/opt/homebrew/lib -lreadline -o minishell
*/
#include "parser.h"

/**
 * Parses a sequence of tokens to build an abstract syntax tree (AST).
 *
 * @param tokens The input tokens to be parsed.
 *
 * @returns A pointer to the root of the AST representing the parsed tokens.
 *          Returns NULL if the input tokens are empty or if syntax validation fails.
 */
t_tree	*parse_tokens(t_token *tokens)
{
	if (!tokens || tokens->type == TKN_END)
		return (NULL);
	if (!validate_syntax(tokens))
		return (NULL);
	return (parse_pipeline(&tokens));
}

/**
 * Parses a pipeline of commands and creates an abstract syntax tree (AST) for the pipeline.
 *
 * @param tokens A pointer to the pointer to the tokens representing the pipeline.
 *
 * @returns A pointer to the root of the AST representing the pipeline.
 */
t_tree	*parse_pipeline(t_token **tokens)
{
	t_tree	*left_node;
	t_tree	*pipe_node;

	left_node = parse_command(tokens);
	if (!left_node)
		return (NULL);
	if ((*tokens)->type == TKN_PIPE)
	{
		(*tokens) = (*tokens)->next;
		pipe_node = create_ast_node(NODE_PIPE, NULL, 0, OTHER);
		pipe_node->left = left_node;
		pipe_node->right = parse_pipeline(tokens);
		return (pipe_node);
	}
	return (left_node);
}

t_tree	*parse_redirection(t_token **tokens)
{
	t_tree				*redir_node;
	t_redir_type	redir_type;
	char					**argv;

	if (!*tokens)
		return (NULL);
	
}

t_tree	*parse_command(t_token **tokens);
