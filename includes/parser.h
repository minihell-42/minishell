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
	TKN_CMD,
	TKN_ARG,
	TKN_PIPE,
	TKN_HERE_DOC,
	TKN_REDIR_IN,
	TKN_REDIR_OUT,
	TKN_REDIR_APPEND,
	TKN_NEWLINE,
	TKN_END
}						t_token_type;

typedef enum e_quote_type
{
	QUOTE_NONE,
	QUOTE_SINGLE,
	QUOTE_DOUBLE
}						t_quote_type;

typedef struct s_token	t_token;

struct					s_token
{
	char				*value;
	int					type;
	size_t				len;
	t_quote_type		quote_type;
	t_token				*next;
	t_token				*prev;
};

typedef enum e_node_type
{
	NODE_CMD,
	NODE_PIPE,
	NODE_REDIR
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

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	HERE_DOC,
}						t_redir_type;

typedef struct s_tree	t_tree;

struct					s_tree
{
	t_node_type			type;
	t_cmd_type			cmd_type;
	t_redir_type		redir_type;
	char				**argv;
	int					argc;
	t_quote_type		*arg_quotes;
	t_tree				*left;
	t_tree				*right;
	t_token_type		input_type;
	t_token_type		output_type;
	char				*input_file;
	char				*output_file;
	t_quote_type		input_quote;
	t_quote_type		output_quote;
	int					here_doc_fd;
};

// LEXER
t_token					*get_next_token(char **input, int *is_first_word);
t_token					*lexer_tokenizer(char *input);
t_token					*create_token(char *value, t_token_type type);
void					detect_quote(char c, t_quote_type *qtype);
char					*extract_quoted(char **input, char quote);
void					skip_whitespace(char **input);
void					append_token(t_token **head, t_token **current,
							t_token *new_token);
void					free_tokens(t_token *tokens);

// TOKENS
t_token					*tokenize_redirections(char *input);
t_token					*tokenize_pipes_and_separators(char *input);
t_token					*tokenize_cmd_and_arg(char **input, int *is_first_word);
t_token					*handle_redirection(char **input, int *is_first_word);
t_token					*handle_pipe_or_newline(char **input,
							int *is_first_word);
t_token					*handle_cmd(char **input, int *is_first_word);

// PARSER
t_tree					*parse_tokens(t_token *tokens);
t_tree					*parse_command(t_token **tokens);
t_tree					*parse_redirection(t_token **tokens);
t_tree					*parse_pipeline(t_token **tokens);
t_tree					*parse_heredoc_prefix(t_token **tokens);
t_cmd_type				is_builtin(char *cmd);
t_tree					*make_redirection_node(t_tree *prev, t_token **tokens);
int						is_redir(int type);
int						is_filename_token(int type);
int						alloc_new_arrays(int old_argc, char ***new_argv,
							t_quote_type **new_quotes, char *arg);
void					copy_and_append_args(t_tree *cmd_node, char **new_argv,
							t_quote_type *new_quotes, char *arg);
int						extract_filename(t_token **tokens, char **file,
							t_quote_type *quote);
void					append_arg(t_tree *cmd_node, char *arg, t_quote_type q);
void					append_trailing_args(t_tree *root, t_token **tokens);

// AST
t_tree					*create_ast_node(t_node_type type, char **argv,
							int argc, t_cmd_type cmd_type);
void					free_ast(t_tree *root);

// DEBUG
void					print_tokens(t_token *tokens);
void					print_ast(t_tree *root, int depth);

#endif