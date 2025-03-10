#include "../../includes/execution.h"

// Parse a command string into argc/argv
static void	parse_command(char *cmd_str, int *argc, char ***argv)
{
	char	*cmd_copy;
	char	*token;
	int		count;
	int		i;

	count = 0;
	// First, count the arguments
	cmd_copy = ft_strdup(cmd_str);
	token = strtok(cmd_copy, " \t");
	while (token)
	{
		count++;
		token = strtok(NULL, " \t");
	}
	free(cmd_copy);
	// Allocate the argv array
	*argv = malloc(sizeof(char *) * (count + 1)); // +1 for NULL terminator
	if (!*argv)
		return ;
	// Fill the argv array
	cmd_copy = ft_strdup(cmd_str);
	token = strtok(cmd_copy, " \t");
	i = 0;
	while (token)
	{
		(*argv)[i] = ft_strdup(token);
		i++;
		token = strtok(NULL, " \t");
	}
	(*argv)[i] = NULL; // NULL terminate the array
	*argc = count;
	free(cmd_copy);
}

t_tree	*create_cmd_node(char *cmd_str, t_cmd_type cmd_type)
{
	t_tree	*node;

	node = malloc(sizeof(t_tree));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->cmd_type = cmd_type;
	// Parse the command string into argv array
	parse_command(cmd_str, &node->argc, &node->argv);
	if (!node->argv)
	{
		free(node);
		return (NULL);
	}
	node->left = NULL;
	node->right = NULL;
	return (node);
}

// Function to free a tree node
void	free_cmd_node(t_tree *node)
{
	int	i;

	if (!node)
		return ;
	if (node->argv)
	{
		for (i = 0; i < node->argc && node->argv[i]; i++)
			free(node->argv[i]);
		free(node->argv);
	}
	free(node);
}

int	main(int argc, char **argv, char **envp)
{
	t_tree *tree;

	(void)argc;
	(void)argv;

	// Test 1: Simple command
	tree = create_cmd_node("pwd", OTHER);
	if (!tree)
	{
		printf("Failed to create tree\n");
		return (1);
	}

	// Print command and arguments
	printf("Executing command: %s\n", tree->argv[0]);
	printf("Arguments: ");
	for (int i = 1; i < tree->argc; i++)
		printf("%s ", tree->argv[i]);
	printf("\n");

	// Execute the command
	exec(tree, envp);

	// Free the node
	free_cmd_node(tree);

	return (0);
}