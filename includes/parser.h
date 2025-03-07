/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 19:14:35 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/03/04 16:32:49 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "shell.h"

typedef enum s_token_type
{
	TKN_ARG,
	TKN_ENV_VAR,
	TKN_PIPE,
	TKN_HERE_DOC,
	TKN_REDIR_IN,
	TKN_REDIR_OUT,
	TKN_REDIR_APPEND,
	TKN_SEMICOLON,
	TKN_NEWLINE,
	TKN_END
}						t_token_type;

typedef struct s_token	t_token;

struct					s_token
{
	char				*value;
	int					type;
	size_t				len;
	t_token				*next;
	t_token				*prev;
};

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_SEQUENCE,
	NODE_REDIR,
	NODE_ARG,
}						t_node_type;

typedef enum e_cmd_type
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT,
	OTHER,
}						t_cmd_type;

typedef struct s_tree	t_tree;

struct					s_tree
{
	t_node_type			type;
	t_cmd_type			cmd_type;
	char				**argv;
	int					argc;
	t_tree				*left;
	t_tree				*right;
	t_token_type		input_type;
	t_token_type		output_type;
	char				*input_file;
	char				*output_file;
};

#endif