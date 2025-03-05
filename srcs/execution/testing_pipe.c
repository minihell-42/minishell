// #include "../../includes/execution.h"

// // Helper function to create a command node for testing
// t_tree	*create_test_cmd(char *cmd_str)
// {
// 	t_tree	*node;
// 	char	*cmd_copy;
// 	char	*token;
// 	int		argc;
// 	int		i;

// 	argc = 0;
// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	// Initialize the node
// 	node->type = NODE_CMD;
// 	node->left = NULL;
// 	node->right = NULL;
// 	// Count arguments
// 	cmd_copy = strdup(cmd_str);
// 	token = strtok(cmd_copy, " \t");
// 	while (token)
// 	{
// 		argc++;
// 		token = strtok(NULL, " \t");
// 	}
// 	free(cmd_copy);
// 	// Allocate argv array
// 	node->argv = malloc((argc + 1) * sizeof(char *));
// 	if (!node->argv)
// 	{
// 		free(node);
// 		return (NULL);
// 	}
// 	// Fill argv array
// 	cmd_copy = strdup(cmd_str);
// 	token = strtok(cmd_copy, " \t");
// 	i = 0;
// 	while (token)
// 	{
// 		node->argv[i] = strdup(token);
// 		token = strtok(NULL, " \t");
// 		i++;
// 	}
// 	node->argv[i] = NULL;
// 	free(cmd_copy);
// 	return (node);
// }

// // Helper function to create a pipe node
// t_tree	*create_test_pipe(t_tree *left, t_tree *right)
// {
// 	t_tree	*node;

// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	node->type = NODE_PIPE;
// 	node->left = left;
// 	node->right = right;
// 	node->argv = NULL;
// 	return (node);
// }

// // Function to free a tree
// void	free_test_tree(t_tree *node)
// {
// 	int	i;

// 	if (!node)
// 		return ;
// 	free_test_tree(node->left);
// 	free_test_tree(node->right);
// 	if (node->argv)
// 	{
// 		i = 0;
// 		while (node->argv[i])
// 		{
// 			free(node->argv[i]);
// 			i++;
// 		}
// 		free(node->argv);
// 	}
// 	free(node);
// }

// // Function to run a single pipe test
// void	run_pipe_test(char *test_name, t_tree *tree, char **envp)
// {
// 	t_context	ctx;
// 	int			children;
// 	int			status;
// 	int			i;

// 	printf("\n===== Testing: %s =====\n", test_name);
// 	// Initialize context
// 	ctx.fd[0] = STDIN_FILENO;
// 	ctx.fd[1] = STDOUT_FILENO;
// 	ctx.fd_close = -1;
// 	// Execute the tree
// 	children = exec_tree(tree, &ctx, envp);
// 	// Wait for all children
// 	i = 0;
// 	while (i < children)
// 	{
// 		waitpid(-1, &status, 0);
// 		i++;
// 	}
// 	// Add a small delay or force stdout to flush
// 	fflush(stdout);
// 	usleep(100000); // 100ms delay to let output flush
// 	printf("===== Test completed =====\n\n");
// }

// // Test cases
// void	test_simple_pipe(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*pipe_node;

// 	// ls | wc -l
// 	cmd1 = create_test_cmd("ls -la");
// 	cmd2 = create_test_cmd("wc -l");
// 	pipe_node = create_test_pipe(cmd1, cmd2);
// 	run_pipe_test("Simple pipe (ls | wc -l)", pipe_node, envp);
// 	free_test_tree(pipe_node);
// }

// void	test_multiple_pipes(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*cmd3;
// 	t_tree	*pipe1;
// 	t_tree	*pipe2;

// 	cmd1 = create_test_cmd("ls");
// 	cmd2 = create_test_cmd("cat Makefile");
// 	cmd3 = create_test_cmd("grep CC");
// 	pipe1 = create_test_pipe(cmd1, cmd2);
// 	pipe2 = create_test_pipe(pipe1, cmd3);
// 	run_pipe_test("Multiple pipes (ls | cat Makefile | grep CC)", pipe2, envp);
// 	free_test_tree(pipe2);
// }

// void	test_complex_pipes(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*cmd3;
// 	t_tree	*cmd4;
// 	t_tree	*pipe1;
// 	t_tree	*pipe2;
// 	t_tree	*pipe3;

// 	// ls | cat Makefile | grep CC | wc -l
// 	cmd1 = create_test_cmd("ls");
// 	cmd2 = create_test_cmd("cat Makefile");
// 	cmd3 = create_test_cmd("grep CC");
// 	cmd4 = create_test_cmd("wc -l");
// 	pipe1 = create_test_pipe(cmd1, cmd2);
// 	pipe2 = create_test_pipe(pipe1, cmd3);
// 	pipe3 = create_test_pipe(pipe2, cmd4);
// 	run_pipe_test("Complex pipe (ls | cat Makefile | grep CC | wc -l)", pipe3,
// 		envp);
// 	free_test_tree(pipe3);
// }

// void	test_error_handling(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*pipe_node;

// 	// non_existent_command | wc -l
// 	cmd1 = create_test_cmd("non_existent_command");
// 	cmd2 = create_test_cmd("wc -l");
// 	pipe_node = create_test_pipe(cmd1, cmd2);
// 	run_pipe_test("Error handling (non_existent_command | wc -l)", pipe_node,
// 		envp);
// 	free_test_tree(pipe_node);
// }

// void	test_large_data(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*pipe_node;

// 	// cat /etc/passwd | grep root
// 	cmd1 = create_test_cmd("cat /etc/passwd");
// 	cmd2 = create_test_cmd("grep root");
// 	pipe_node = create_test_pipe(cmd1, cmd2);
// 	run_pipe_test("Large data (cat /etc/passwd | grep root)", pipe_node, envp);
// 	free_test_tree(pipe_node);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	printf("Starting pipe tests...\n");
// 	test_simple_pipe(envp);
// 	test_multiple_pipes(envp);
// 	test_complex_pipes(envp);
// 	test_error_handling(envp);
// 	test_large_data(envp);
// 	printf("All pipe tests completed.\n");
// 	return (0);
// }
