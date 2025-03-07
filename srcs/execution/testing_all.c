// #include "../../includes/execution.h"

// /* Helper functions for node creation */
// static t_tree	*create_command_node(char **argv)
// {
// 	t_tree	*node;

// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	node->type = NODE_CMD;
// 	node->argv = argv;
// 	node->left = NULL;
// 	node->right = NULL;
// 	node->input_file = NULL;
// 	node->output_file = NULL;
// 	return (node);
// }

// static t_tree	*create_pipe_node(t_tree *left, t_tree *right)
// {
// 	t_tree	*node;

// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	node->type = NODE_PIPE;
// 	node->argv = NULL;
// 	node->left = left;
// 	node->right = right;
// 	node->input_file = NULL;
// 	node->output_file = NULL;
// 	return (node);
// }

// static t_tree	*create_sequence_node(t_tree *left, t_tree *right)
// {
// 	t_tree	*node;

// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	node->type = NODE_SEQUENCE;
// 	node->argv = NULL;
// 	node->left = left;
// 	node->right = right;
// 	node->input_file = NULL;
// 	node->output_file = NULL;
// 	return (node);
// }

// static t_tree	*create_redir_node(t_tree *cmd, char *input_file,
// 		char *output_file, int output_type)
// {
// 	t_tree	*node;

// 	node = malloc(sizeof(t_tree));
// 	if (!node)
// 		return (NULL);
// 	node->type = NODE_REDIR;
// 	node->argv = NULL;
// 	node->left = cmd;
// 	node->right = NULL;
// 	node->input_file = input_file;
// 	node->output_file = output_file;
// 	node->output_type = output_type;
// 	return (node);
// }

// /* Helper functions for command creation */
// static char	**create_argv(const char *cmd, const char *arg)
// {
// 	char	**argv;

// 	argv = malloc(sizeof(char *) * (arg ? 3 : 2));
// 	if (!argv)
// 		return (NULL);
// 	argv[0] = strdup(cmd);
// 	if (arg)
// 	{
// 		argv[1] = strdup(arg);
// 		argv[2] = NULL;
// 	}
// 	else
// 		argv[1] = NULL;
// 	return (argv);
// }

// static void	cleanup_argv(char **argv)
// {
// 	int	i;

// 	i = 0;
// 	while (argv[i])
// 		free(argv[i++]);
// 	free(argv);
// }

// static void	cleanup_tree(t_tree *tree)
// {
// 	if (!tree)
// 		return ;
// 	if (tree->argv)
// 		cleanup_argv(tree->argv);
// 	if (tree->input_file)
// 		free(tree->input_file);
// 	if (tree->output_file)
// 		free(tree->output_file);
// 	cleanup_tree(tree->left);
// 	cleanup_tree(tree->right);
// 	free(tree);
// }

// /* Test cases */
// static void	test_complex_pipe_redir_sequence(char **envp)
// {
// 	t_tree	*cmd1, *cmd2, *cmd3, *cmd4;
// 	t_tree	*pipe1, *pipe2, *redir1, *redir2, *seq;
// 	char	**argv1, **argv2, **argv3, **argv4;

// 	printf("\n=== Testing Complex Pipeline with Redirections and Sequence ===\n");
// 	printf("ls -l | grep 'src' > output1.txt ; cat < output1.txt | wc -l > output2.txt\n");

// 	// Create commands
// 	argv1 = create_argv("ls", "-l");
// 	argv2 = create_argv("grep", "src");
// 	argv3 = create_argv("cat", NULL);
// 	argv4 = create_argv("wc", "-l");

// 	cmd1 = create_command_node(argv1);
// 	cmd2 = create_command_node(argv2);
// 	cmd3 = create_command_node(argv3);
// 	cmd4 = create_command_node(argv4);

// 	// Create first pipeline with redirection
// 	pipe1 = create_pipe_node(cmd1, cmd2);
// 	redir1 = create_redir_node(pipe1, NULL, strdup("output1.txt"), TKN_REDIR_OUT);

// 	// Create second pipeline with redirection
// 	pipe2 = create_pipe_node(cmd3, cmd4);
// 	redir2 = create_redir_node(pipe2, strdup("output1.txt"), strdup("output2.txt"), TKN_REDIR_OUT);

// 	// Create sequence
// 	seq = create_sequence_node(redir1, redir2);

// 	// Execute
// 	exec(seq, envp);

// 	printf("\nContents of output1.txt:\n");
// 	system("cat output1.txt");
// 	printf("\nContents of output2.txt:\n");
// 	system("cat output2.txt");

// 	// Cleanup
// 	cleanup_tree(seq);
// 	// system("rm -f output1.txt output2.txt");
// }

// static void	test_multiple_redirections(char **envp)
// {
// 	t_tree	*cmd1, *cmd2, *cmd3;
// 	t_tree	*redir1, *redir2, *redir3, *seq1, *seq2;
// 	char	**argv1, **argv2, **argv3;

// 	printf("\n=== Testing Multiple Redirections in Sequence ===\n");
// 	printf("echo 'test1' > file1.txt ; echo 'test2' >> file1.txt ; cat < file1.txt\n");

// 	// Create commands
// 	argv1 = create_argv("echo", "test1");
// 	argv2 = create_argv("echo", "test2");
// 	argv3 = create_argv("cat", NULL);

// 	cmd1 = create_command_node(argv1);
// 	cmd2 = create_command_node(argv2);
// 	cmd3 = create_command_node(argv3);

// 	// Create redirections
// 	redir1 = create_redir_node(cmd1, NULL, strdup("file1.txt"), TKN_REDIR_OUT);
// 	redir2 = create_redir_node(cmd2, NULL, strdup("file1.txt"), TKN_REDIR_APPEND);
// 	redir3 = create_redir_node(cmd3, strdup("file1.txt"), NULL, 0);

// 	// Create sequences
// 	seq1 = create_sequence_node(redir1, redir2);
// 	seq2 = create_sequence_node(seq1, redir3);

// 	// Execute
// 	exec(seq2, envp);

// 	// Cleanup
// 	cleanup_tree(seq2);
// 	// system("rm -f file1.txt");
// }

// static void	test_complex_pipeline(char **envp)
// {
// 	t_tree	*cmd1, *cmd2, *cmd3, *cmd4;
// 	t_tree	*pipe1, *pipe2, *pipe3;
// 	char	**argv1, **argv2, **argv3, **argv4;

// 	printf("\n=== Testing Complex Pipeline ===\n");
// 	printf("ls -la | grep src | sort | wc -l\n");

// 	// Create commands
// 	argv1 = create_argv("ls", "-la");
// 	argv2 = create_argv("grep", "src");
// 	argv3 = create_argv("sort", NULL);
// 	argv4 = create_argv("wc", "-l");

// 	cmd1 = create_command_node(argv1);
// 	cmd2 = create_command_node(argv2);
// 	cmd3 = create_command_node(argv3);
// 	cmd4 = create_command_node(argv4);

// 	// Create pipeline
// 	pipe1 = create_pipe_node(cmd1, cmd2);
// 	pipe2 = create_pipe_node(pipe1, cmd3);
// 	pipe3 = create_pipe_node(pipe2, cmd4);

// 	// Execute
// 	exec(pipe3, envp);

// 	// Cleanup
// 	cleanup_tree(pipe3);
// }

// static void	test_error_cases(char **envp)
// {
// 	t_tree	*cmd1, *cmd2, *pipe1, *redir1;
// 	char	**argv1, **argv2;

// 	printf("\n=== Testing Error Cases ===\n");

// 	// Test nonexistent command
// 	printf("\nTesting nonexistent command:\n");
// 	argv1 = create_argv("nonexistentcmd", NULL);
// 	cmd1 = create_command_node(argv1);
// 	exec(cmd1, envp);
// 	cleanup_tree(cmd1);

// 	// Test nonexistent input file
// 	printf("\nTesting nonexistent input file:\n");
// 	argv1 = create_argv("cat", NULL);
// 	cmd1 = create_command_node(argv1);
// 	redir1 = create_redir_node(cmd1, strdup("nonexistentfile"), NULL, 0);
// 	exec(redir1, envp);
// 	cleanup_tree(redir1);

// 	// Test pipe with failed command
// 	printf("\nTesting pipe with failed command:\n");
// 	argv1 = create_argv("ls", "-l");
// 	argv2 = create_argv("nonexistentcmd", NULL);
// 	cmd1 = create_command_node(argv1);
// 	cmd2 = create_command_node(argv2);
// 	pipe1 = create_pipe_node(cmd1, cmd2);
// 	exec(pipe1, envp);
// 	cleanup_tree(pipe1);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	(void)argc;
// 	(void)argv;

// 	printf("=== Starting Comprehensive Execution Tests ===\n");

// 	// Test complex combinations
// 	test_complex_pipe_redir_sequence(envp);
// 	test_multiple_redirections(envp);
// 	test_complex_pipeline(envp);

// 	// Test error cases
// 	test_error_cases(envp);

// 	printf("\n=== All Tests Completed ===\n");
// 	return (0);
// }
