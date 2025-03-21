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
 *    Returns NULL if the input tokens are empty or if syntax validation fails.
 */
t_tree	*parse_tokens(t_token *tokens)
{
	if (tokens && tokens->type == TKN_NEWLINE)
		tokens = tokens->next;
	if (!tokens || tokens->type == TKN_END)
		return (NULL);
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
	char	*filename;
	t_tree	*cmd_node;
	t_token	*redir_token;
	t_tree	*redir_node;

	cmd_node = parse_command(tokens);
	if (!cmd_node)
		return (NULL);
	while (*tokens && ((*tokens)->type == TKN_REDIR_IN
			|| (*tokens)->type == TKN_REDIR_OUT || (*tokens)->type
			== TKN_REDIR_APPEND || (*tokens)->type == TKN_HERE_DOC))
	{
		redir_token = *tokens;
		*tokens = (*tokens)->next;
		if (!*tokens || (((*tokens)->type != TKN_CMD) && ((*tokens)->type
					!= TKN_ARG) && ((*tokens)->type != TKN_ENV_VAR)))
			return (NULL);
		filename = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
		redir_node = create_ast_node(NODE_REDIR, NULL, 0, OTHER);
		if (redir_token->type == TKN_REDIR_IN)
		{
			redir_node->redir_type = REDIR_IN;
			redir_node->input_file = filename;
		}
		else if (redir_token->type == TKN_REDIR_OUT)
		{
			redir_node->redir_type = REDIR_OUT;
			redir_node->output_file = filename;
		}
		else if (redir_token->type == TKN_REDIR_APPEND)
		{
			redir_node->redir_type = REDIR_APPEND;
			redir_node->output_file = filename;
		}
		else if (redir_token->type == TKN_HERE_DOC)
		{
			redir_node->redir_type = HERE_DOC;
			redir_node->input_file = filename;
		}
		redir_node->left = cmd_node;
		cmd_node = redir_node;
	}
	return (cmd_node);
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
	t_token			*current;
	t_cmd_type		cmd_type;
	int				i;
	int				count;
	char			**argv;

	count = 0;
	current = *tokens;
	while (current && (current->type == TKN_CMD || current->type == TKN_ARG
			|| current->type == TKN_ENV_VAR))
	{
		count++;
		current = current->next;
	}
	if (count == 0)
		return (NULL);
	argv = (char **)malloc(sizeof(char *) * (count + 1));
	if (!argv)
		return (NULL);
	i = 0;
	while (*tokens && ((*tokens)->type == TKN_CMD || (*tokens)->type == TKN_ARG
			|| (*tokens)->type == TKN_ENV_VAR))
	{
		argv[i] = ft_strdup((*tokens)->value);
		*tokens = (*tokens)->next;
		i++;
	}
	argv[i] = NULL;
	cmd_type = is_builtin(argv[0]);
	return (create_ast_node(NODE_CMD, argv, count, cmd_type));
}
