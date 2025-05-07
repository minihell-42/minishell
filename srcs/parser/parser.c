/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:15:04 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/05 10:59:55 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Validates the syntax of the tokens.
 *
 * @param tokens A pointer to the head of the token linked list.
 *
 * @returns 1 if the syntax is valid, 0 otherwise.
 */
static int	validate_syntax(t_token *tokens)
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

/**
 * Prints a syntax error message to the standard error output.
 *
 * @param token The token that caused the syntax error.
 */
static void	print_syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `",
		STDERR_FILENO);
	ft_putstr_fd(token, STDERR_FILENO);
	ft_putendl_fd("'", STDERR_FILENO);
}

/**
 * Retrieves the token that caused the syntax error.
 *
 * @param tokens The input tokens to be parsed.
 *
 * @returns A string representing the token that caused the syntax error.
 */
static char	*get_error_token(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	if (current->type == TKN_PIPE || is_redir(current->type))
	{
		if (is_redir(current->type) && (!current->next
				|| current->next->type == TKN_END))
			return ("newline");
		return (current->value);
	}
	while (current && current->type != TKN_END)
	{
		if (current->type == TKN_PIPE || is_redir(current->type))
		{
			if (!current->next || current->next->type == TKN_END)
				return("newline");
			return (current->value);
		}
		current = current->next;
	}
	return ("newline");
}

/**
 * Parses a sequence of tokens to build an abstract syntax tree (AST).
 *
 * @param tokens The input tokens to be parsed.
 *
 * @returns A pointer to the root of the AST representing the parsed tokens.
 *    Returns NULL if the input tokens are empty or if syntax validation fails.
 */
t_tree	*parse_tokens(t_token *tokens)
{
	char	*error_tkn;

	if (tokens && tokens->type == TKN_NEWLINE)
		tokens = tokens->next;
	if (!tokens || tokens->type == TKN_END)
		return (NULL);
	if (!validate_syntax(tokens))
	{
		error_tkn = get_error_token(tokens);
		print_syntax_error(error_tkn);
		g_signal = 2;
		return (NULL);
	}
		
	return (parse_pipeline(&tokens));
}

/**
 * Parses a pipeline of commands and creates an
 * abstract syntax tree (AST) for the pipeline.
 *
 * @param tokens A pointer to the pointer to the tokens
 * representing the pipeline.
 *
 * @returns A pointer to the root of the AST representing the pipeline.
 */
t_tree	*parse_pipeline(t_token **tokens)
{
	t_tree	*left_node;
	t_tree	*pipe_node;

	left_node = parse_redirection(tokens);
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
