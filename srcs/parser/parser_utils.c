#include "parser.h"

t_tree	*parse_tokens(t_token *tokens);
t_tree	*parse_command(t_token **tokens);
t_tree	*parse_redirection(t_token **tokens);
t_tree	*parse_pipeline(t_token **tokens);
t_tree	*parse_sequence(t_token **tokens);