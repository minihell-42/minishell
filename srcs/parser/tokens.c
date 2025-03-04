#include "shell.h"

t_token	*tokenize_redirections(char *input);

t_token	*tokenize_pipes_and_separators(char *input);

void	print_tokens(t_token *tokens);
