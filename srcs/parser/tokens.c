#include "parser.h"

t_token	*tokenize_redirections(char *input);

t_token	*tokenize_pipes_and_separators(char *input);

void	print_tokens(t_token *tokens)
{
  t_token	*current;

  current = tokens;
  while (current)
  {
    printf("start\n");
    printf("Token: %s\n", current->value);
    printf("Type: %d\n", current->type);
    current = current->next;
  }
}
