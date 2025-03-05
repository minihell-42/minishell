#include "parser.h"

t_tree	*create_ast_node(t_node_type type, char *value);
void	print_ast(t_tree *root, int depth);
void	free_ast(t_tree *root);