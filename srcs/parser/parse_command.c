/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 10:48:45 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/05 10:58:07 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

/**
 * Determines if a given command is a built-in command.
 *
 * @param cmd The command to check.
 *
 * @returns The type of the built-in command.
 */
t_cmd_type	is_builtin(char *cmd)
{
	if (!ft_strcmp(cmd, "echo"))
		return (ECHO);
	if (!ft_strcmp(cmd, "cd"))
		return (CD);
	if (!ft_strcmp(cmd, "pwd"))
		return (PWD);
	if (!ft_strcmp(cmd, "export"))
		return (EXPORT);
	if (!ft_strcmp(cmd, "unset"))
		return (UNSET);
	if (!ft_strcmp(cmd, "env"))
		return (ENV);
	if (!ft_strcmp(cmd, "exit"))
		return (EXIT);
	return (OTHER);
}

/**
 * Counts the number of command tokens in a given linked list of tokens.
 *
 * @param token A pointer to the first token in the linked list.
 *
 * @returns The number of command tokens in the linked list.
 */
static int	count_cmd_tokens(t_token *token)
{
	t_token	*current;
	int		count;

	count = 0;
	current = token;
	while (current && (current->type == TKN_CMD || current->type == TKN_ARG
			|| current->type == TKN_ENV_VAR || current->type == TKN_SHELL_VAR))
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * Fills an array of strings with the values of command tokens in a given
 * linked list of tokens.
 *
 * @param argv A pointer to the array of strings to fill.
 * @param arg_quotes A pointer to the array of quote types to fill.
 * @param tokens A pointer to the pointer to the first token in the linked list.
 */
static void	fill_args(char **argv, t_quote_type *arg_quotes, t_token **tokens)
{
	t_token	*current;
	int		i;

	i = 0;
	current = *tokens;
	while (current && (current->type == TKN_CMD || current->type == TKN_ARG
			|| current->type == TKN_ENV_VAR || current->type == TKN_SHELL_VAR))
	{
		argv[i] = ft_strdup(current->value);
		arg_quotes[i] = current->quote_type;
		current = current->next;
		i++;
	}
	*tokens = current;
	argv[i] = NULL;
}

/**
 * Parses a command and creates an abstract syntax tree (AST) for the command.
 *
 * @param tokens A pointer to the pointer to the tokens
 * representing the command.
 *
 * @returns A pointer to the root of the AST representing the command.
 */
t_tree	*parse_command(t_token **tokens)
{
	t_quote_type	*arg_quotes;
	t_tree			*node;
	int				count;
	char			**argv;

	count = count_cmd_tokens(*tokens);
	if (count == 0)
		return (NULL);
	argv = malloc(sizeof(char *) * (count + 1));
	arg_quotes = malloc(sizeof(t_quote_type) * count);
	if (!argv || !arg_quotes)
	{
		free(argv);
		free(arg_quotes);
		return (NULL);
	}
	fill_args(argv, arg_quotes, tokens);
	node = create_ast_node(NODE_CMD, argv, count, is_builtin(argv[0]));
	if (node)
		node->arg_quotes = arg_quotes;
	else
		free(arg_quotes);
	return (node);
}
