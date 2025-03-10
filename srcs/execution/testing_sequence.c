// #include "../../includes/execution.h"
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/wait.h>
// #include <unistd.h>

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

// // Helper function to create a sequence node
// t_tree	*create_test_sequence(t_tree *left, t_tree *right)
// {
// 	t_tree	*node;

// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	node->type = NODE_SEQUENCE;
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

// // Function to run a sequence test
// void	run_sequence_test(char *test_name, t_tree *tree, char **envp)
// {
// 	t_context	ctx;

// 	printf("\n===== Testing: %s =====\n", test_name);
// 	// Initialize context
// 	ctx.fd[0] = STDIN_FILENO;
// 	ctx.fd[1] = STDOUT_FILENO;
// 	ctx.fd_close = -1;
// 	// Execute the tree
// 	exec(tree, envp);
// 	printf("===== Test completed =====\n\n");
// }

// // Test cases for sequences
// void	test_simple_sequence(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*cmd3;
// 	t_tree	*seq1;

// 	// ls ; echo "HELLO WORLD" ; pwd
// 	cmd1 = create_test_cmd("ls");
// 	cmd2 = create_test_cmd("echo HELLO WORLD");
// 	cmd3 = create_test_cmd("pwd");
// 	seq1 = create_test_sequence(cmd1, create_test_sequence(cmd2, cmd3));
// 	run_sequence_test("Simple sequence (ls ; echo HELLO WORLD ; pwd)", seq1,
// 		envp);
// 	free_test_tree(seq1);
// }

// void	test_sequence_with_pipe(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*cmd3;
// 	t_tree	*pipe_node;
// 	t_tree	*seq;

// 	// ls | grep .c ; echo "Done with grep"
// 	cmd1 = create_test_cmd("ls");
// 	cmd2 = create_test_cmd("grep .c");
// 	cmd3 = create_test_cmd("echo Done with grep");
// 	pipe_node = create_test_pipe(cmd1, cmd2);
// 	seq = create_test_sequence(pipe_node, cmd3);
// 	run_sequence_test("Sequence with pipe (ls | grep .c ; echo Done with grep)",
// 		seq, envp);
// 	free_test_tree(seq);
// }

// void	test_complex_sequence(char **envp)
// {
// 	t_tree	*cmd1;
// 	t_tree	*cmd2;
// 	t_tree	*cmd3;
// 	t_tree	*cmd4;
// 	t_tree	*pipe1;
// 	t_tree	*pipe2;
// 	t_tree	*seq;

// 	// ls | grep .c ; cat Makefile | grep CC
// 	cmd1 = create_test_cmd("ls");
// 	cmd2 = create_test_cmd("grep .c");
// 	cmd3 = create_test_cmd("cat Makefile");
// 	cmd4 = create_test_cmd("grep CC");
// 	pipe1 = create_test_pipe(cmd1, cmd2);
// 	pipe2 = create_test_pipe(cmd3, cmd4);
// 	seq = create_test_sequence(pipe1, pipe2);
// 	run_sequence_test("Complex sequence (ls | grep .c ; cat Makefile | grep CC)",
// 		seq, envp);
// 	free_test_tree(seq);
// }

// void	test_many_sequences(char **envp)
// {
// 	t_tree	*seq1;

// 	t_tree *cmd1, *cmd2, *cmd3, *cmd4, *cmd5;
// 	// echo "One" ; echo "Two" ; echo "Three" ; echo "Four" ; echo "Five"
// 	cmd1 = create_test_cmd("echo One");
// 	cmd2 = create_test_cmd("echo Two");
// 	cmd3 = create_test_cmd("echo Three");
// 	cmd4 = create_test_cmd("echo Four");
// 	cmd5 = create_test_cmd("echo Five");
// 	seq1 = create_test_sequence(cmd1, create_test_sequence(cmd2,
// 				create_test_sequence(cmd3, create_test_sequence(cmd4, cmd5))));
// 	run_sequence_test("Many sequences (echo One ; echo Two ; echo Three ; echo Four ; echo Five)",
// 		seq1, envp);
// 	free_test_tree(seq1);
// }

// void	test_error_in_sequence(char **envp)
// {
// 	t_tree	*seq;

// 	t_tree *cmd1, *cmd2, *cmd3;
// 	// echo "Before error" ; non_existent_command ; echo "After error"
// 	cmd1 = create_test_cmd("echo Before error");
// 	cmd2 = create_test_cmd("non_existent_command");
// 	cmd3 = create_test_cmd("echo After error");
// 	seq = create_test_sequence(cmd1, create_test_sequence(cmd2, cmd3));
// 	run_sequence_test("Error in sequence (echo Before error ; non_existent_command ; echo After error)",
// 		seq, envp);
// 	free_test_tree(seq);
// }

// void	test_pipe_and_error(char **envp)
// {
// 	t_tree *cmd1, *cmd2, *cmd3;
// 	t_tree *pipe1, *seq;
// 	// ls | non_existent_command ; echo "After pipe error"
// 	cmd1 = create_test_cmd("ls");
// 	cmd2 = create_test_cmd("non_existent_command");
// 	cmd3 = create_test_cmd("echo After pipe error");
// 	pipe1 = create_test_pipe(cmd1, cmd2);
// 	seq = create_test_sequence(pipe1, cmd3);
// 	run_sequence_test("Pipe with error (ls | non_existent_command ; echo After pipe error)",
// 		seq, envp);
// 	free_test_tree(seq);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;
// 	char	**shell_env;
// 	shell_env = copy_environment(envp);
// 	printf("Starting sequence tests...\n");
// 	test_simple_sequence(shell_env);
// 	test_sequence_with_pipe(shell_env);
// 	test_complex_sequence(shell_env);
// 	test_many_sequences(shell_env);
// 	test_error_in_sequence(shell_env);
// 	test_pipe_and_error(shell_env);
// 	printf("All sequence tests completed.\n");
// 	return (0);
// }
