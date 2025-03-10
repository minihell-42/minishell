// #include "../../includes/execution.h"

// // Function to create a simple command node
// t_tree *create_command_node(char *cmd, char **args)
// {
//     t_tree *node;
//     int i;
    
//     node = malloc(sizeof(t_tree));
//     if (!node)
//         return (NULL);
    
//     node->type = NODE_CMD;
//     node->cmd_type = OTHER;
//     node->left = NULL;
//     node->right = NULL;
    
//     // Count args
//     i = 0;
//     while (args && args[i])
//         i++;
    
//     node->argc = i + 1;
//     node->argv = malloc(sizeof(char *) * (node->argc + 1));
//     if (!node->argv)
//     {
//         free(node);
//         return (NULL);
//     }
    
//     node->argv[0] = ft_strdup(cmd);
//     for (i = 0; args && args[i]; i++)
//         node->argv[i + 1] = ft_strdup(args[i]);
//     node->argv[node->argc] = NULL;
    
//     return (node);
// }

// // Function to create a redirection node with both input and output
// t_tree *create_input_redir_node(t_tree *cmd_node, char *input_file, char *output_file, int append)
// {
//     t_tree *node;
    
//     node = malloc(sizeof(t_tree));
//     if (!node)
//         return (NULL);
    
//     node->type = NODE_REDIR;
//     node->cmd_type = OTHER;
//     node->left = cmd_node;
//     node->right = NULL;
//     node->argc = 0;
//     node->argv = NULL;
    
//     // Set input redirection
//     node->input_file = input_file ? ft_strdup(input_file) : NULL;
//     node->input_type = input_file ? TKN_REDIR_IN : 0;
    
//     // Set output redirection
//     node->output_file = output_file ? ft_strdup(output_file) : NULL;
//     node->output_type = output_file ? (append ? TKN_REDIR_APPEND : TKN_REDIR_OUT) : 0;
    
//     return (node);
// }

// // Function to free the tree
// void free_tree(t_tree *tree)
// {
//     int i;
    
//     if (!tree)
//         return;
    
//     free_tree(tree->left);
//     free_tree(tree->right);
    
//     if (tree->argv)
//     {
//         for (i = 0; tree->argv[i]; i++)
//             free(tree->argv[i]);
//         free(tree->argv);
//     }
    
//     if (tree->input_file)
//         free(tree->input_file);
//     if (tree->output_file)
//         free(tree->output_file);
    
//     free(tree);
// }

// // Function to test combined input and output redirection
// int test_combined_redirection(char *cmd, char **args, char *input_file, 
//                               char *output_file, int append, char **envp)
// {
//     t_tree *cmd_node;
//     t_tree *redir_node;
    
//     printf("\n--- Testing: %s < %s %s %s ---\n", 
//            cmd, input_file, append ? ">>" : ">", output_file);
    
//     // Create nodes
//     cmd_node = create_command_node(cmd, args);
//     if (!cmd_node)
//     {
//         printf("Error: Failed to create command node\n");
//         return (-1);
//     }
    
//     redir_node = create_input_redir_node(cmd_node, input_file, output_file, append);
//     if (!redir_node)
//     {
//         printf("Error: Failed to create redir node\n");
//         free_tree(cmd_node);
//         return (-1);
//     }
    
//     // Execute and get result
//     exec(redir_node, envp);
    
//     // Clean up
//     free_tree(redir_node);
    
//     printf("--- Test complete ---\n");
    
//     // If output file was created, display its contents
//     if (output_file)
//     {
//         int fd = open(output_file, O_RDONLY);
//         char buffer[1024];
//         ssize_t bytes_read;
        
//         if (fd != -1)
//         {
//             printf("Output file contents:\n");
//             while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
//             {
//                 buffer[bytes_read] = '\0';
//                 printf("%s", buffer);
//             }
//             printf("\n");
//             close(fd);
//         }
//     }
    
//     return (0);
// }

// // Function to test input redirection
// int test_input_redirection(char *cmd, char **args, char *input_file, char **envp)
// {
//     t_tree *cmd_node;
//     t_tree *redir_node;
    
//     printf("\n--- Testing: %s < %s ---\n", cmd, input_file);
    
//     // Create nodes
//     cmd_node = create_command_node(cmd, args);
//     if (!cmd_node)
//     {
//         printf("Error: Failed to create command node\n");
//         return (-1);
//     }
    
//     redir_node = create_input_redir_node(cmd_node, input_file, NULL, 0);
//     if (!redir_node)
//     {
//         printf("Error: Failed to create redir node\n");
//         free_tree(cmd_node);
//         return (-1);
//     }
    
//     // Execute and get result
//     exec(redir_node, envp);
    
//     // Clean up
//     free_tree(redir_node);
    
//     printf("--- Test complete ---\n");
//     return (0);
// }

// // Function to create a pipe node
// t_tree *create_pipe_node(t_tree *left, t_tree *right)
// {
//     t_tree *node;
    
//     node = malloc(sizeof(t_tree));
//     if (!node)
//         return (NULL);
    
//     node->type = NODE_PIPE;
//     node->cmd_type = OTHER;
//     node->left = left;
//     node->right = right;
//     node->argc = 0;
//     node->argv = NULL;
//     node->input_file = NULL;
//     node->output_file = NULL;
    
//     return (node);
// }

// // Simplified pipe test function
// int test_pipe_with_redir(char *cmd1, char **args1, char *cmd2, char **args2,
//                         char *input_file, char *output_file, int append, char **envp)
// {
//     t_tree *cmd1_node;
//     t_tree *cmd2_node;
//     t_tree *pipe_node;
//     t_tree *redir_node;
//     char *new_args1[2] = {NULL, NULL};
    
//     // Just create the command node normally:
//     cmd1_node = create_command_node(cmd1, args1);
    
//     char *output_str = "";
//     if (output_file)
//         output_str = append ? " >> " : " > ";
    
//     printf("\n--- Testing: %s%s%s%s%s | %s%s%s%s%s ---\n",
//            cmd1,
//            new_args1[0] ? " " : "",
//            new_args1[0] ? new_args1[0] : "",
//            input_file ? " < " : "",
//            input_file ? input_file : "",
//            cmd2,
//            args2[0] ? " " : "",
//            args2[0] ? args2[0] : "",
//            output_str,
//            output_file ? output_file : "");
    
//     if (!cmd1_node)
//     {
//         printf("Error: Failed to create first command node\n");
//         return (-1);
//     }
    
//     cmd2_node = create_command_node(cmd2, args2);
//     if (!cmd2_node)
//     {
//         printf("Error: Failed to create second command node\n");
//         free_tree(cmd1_node);
//         return (-1);
//     }
    
//     pipe_node = create_pipe_node(cmd1_node, cmd2_node);
//     if (!pipe_node)
//     {
//         printf("Error: Failed to create pipe node\n");
//         free_tree(cmd1_node);
//         free_tree(cmd2_node);
//         return (-1);
//     }
    
//     if (input_file || output_file)
//     {
//         redir_node = create_input_redir_node(pipe_node, input_file, output_file, append);
//         if (!redir_node)
//         {
//             printf("Error: Failed to create redir node\n");
//             free_tree(pipe_node);
//             return (-1);
//         }
//     }
//     else
//         redir_node = pipe_node;
    
//     printf("DEBUG: Executing command...\n");
//     exec(redir_node, envp);
//     printf("DEBUG: Command executed\n");
    
//     if (output_file)
//     {
//         printf("DEBUG: Checking output file...\n");
//         int fd = open(output_file, O_RDONLY);
//         if (fd != -1)
//         {
//             char buffer[1024];
//             ssize_t bytes_read;
            
//             printf("\nOutput file contents:\n");
//             while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
//             {
//                 buffer[bytes_read] = '\0';
//                 printf("%s", buffer);
//             }
//             printf("\n");
//             close(fd);
//         }
//     }
    
//     if (redir_node != pipe_node)
//         free_tree(redir_node);
//     else
//         free_tree(pipe_node);
    
//     printf("--- Test complete ---\n");
//     return (0);
// }

// int main(int argc, char **argv, char **envp)
// {
//     (void)argc;
//     (void)argv;
// 	char	**shell_env;
// 	shell_env = copy_environment(envp);
    
//     // Command arguments
//     char *cat_args[] = {NULL};
//     char *grep_args[] = {"Hello", NULL};
//     char *sort_args[] = {NULL};
//     char *wc_args[] = {"-l", NULL};
    
//     // Create first test input file
//     int fd = open("test_input1.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         perror("Error creating first test file");
//         return (1);
//     }
//     const char *content1 = "Hello, World!\nThis is a test file.\nHello again!\nLast line\n";
//     write(fd, content1, strlen(content1));
//     close(fd);
    
//     // Create second test input file
//     fd = open("test_input2.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
//     if (fd == -1)
//     {
//         perror("Error creating second test file");
//         return (1);
//     }
//     const char *content2 = "Different Hello\nAnother line\nHello there\nEnd line\n";
//     write(fd, content2, strlen(content2));
//     close(fd);
    
//     printf("\n=== TESTING PIPES WITH REDIRECTIONS ===\n");
    
//     // Test 1: Basic pipe with input redirection (using < operator)
//     printf("\nTest 1: Basic pipe with input redirection (using <)\n");
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input1.txt", NULL, 0, shell_env);
    
//     // Test 1b: Basic pipe with cat argument
//     printf("\nTest 1b: Basic pipe with cat argument\n");
//     char *cat_with_file[] = {"test_input1.txt", NULL};
//     test_pipe_with_redir("cat", cat_with_file, "grep", grep_args,
//                         NULL, NULL, 0, shell_env);
    
//     // Test 2: Pipe with output redirection (using < operator)
//     printf("\nTest 2: Pipe with output redirection (using <)\n");
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input1.txt", "output1.txt", 0, shell_env);
    
//     // Test 2b: Pipe with output redirection (using cat argument)
//     printf("\nTest 2b: Pipe with output redirection (using cat argument)\n");
//     test_pipe_with_redir("cat", cat_with_file, "grep", grep_args,
//                         NULL, "output1b.txt", 0, shell_env);
    
//     // Test 3: Pipe with both input and output redirection
//     printf("\nTest 3: Pipe with both input and output redirection\n");
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input1.txt", "output2.txt", 0, shell_env);
    
//     // Test 4: Pipe with sort and output
//     printf("\nTest 4: Pipe with sort\n");
//     test_pipe_with_redir("cat", cat_args, "sort", sort_args,
//                         "test_input1.txt", "sorted1.txt", 0, shell_env);
    
//     // Test 5: Multiple files through pipe
//     printf("\nTest 5: Different input file\n");
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input2.txt", "output3.txt", 0, shell_env);
    
//     // Test 6: Count lines through pipe
//     printf("\nTest 6: Counting lines through pipe\n");
//     test_pipe_with_redir("cat", cat_args, "wc", wc_args,
//                         "test_input1.txt", "count1.txt", 0, shell_env);
    
//     // Test 7: Sort and grep combination
//     printf("\nTest 7: Sort and grep combination\n");
//     test_pipe_with_redir("sort", sort_args, "grep", grep_args,
//                         "test_input2.txt", "sorted_grep.txt", 0, shell_env);
    
//     // Test 8: Nonexistent input file (should show error)
//     printf("\nTest 8: Nonexistent input file\n");
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "nonexistent.txt", "error_out.txt", 0, shell_env);
    
//     // Test 9: Write to same output file (should overwrite)
//     printf("\nTest 9: Overwriting output file\n");
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input1.txt", "same_output.txt", 0, shell_env);
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input2.txt", "same_output.txt", 0, shell_env);
    
//     // Test 10: Test append redirection
//     printf("\nTest 10: Append output\n");
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input1.txt", "append_output.txt", 1, shell_env);
//     test_pipe_with_redir("cat", cat_args, "grep", grep_args,
//                         "test_input2.txt", "append_output.txt", 1, shell_env);
    
//     printf("\n=== ALL PIPE TESTS COMPLETED ===\n");
    
//     // Display all output files
//     printf("\n=== FINAL OUTPUT FILES CONTENTS ===\n");
//     char *output_files[] = {"output1.txt", "output2.txt", "output3.txt", 
//                            "sorted1.txt", "count1.txt", "sorted_grep.txt", 
//                            "same_output.txt", "append_output.txt", NULL};
    
//     for (int i = 0; output_files[i]; i++)
//     {
//         printf("\nContents of %s:\n", output_files[i]);
//         fd = open(output_files[i], O_RDONLY);
//         if (fd != -1)
//         {
//             char buffer[1024];
//             ssize_t bytes_read;
//             while ((bytes_read = read(fd, buffer, sizeof(buffer) - 1)) > 0)
//             {
//                 buffer[bytes_read] = '\0';
//                 printf("%s", buffer);
//             }
//             close(fd);
//         }
//         else
//         {
//             printf("(File not created or error opening file)\n");
//         }
//     }
    
//     return (0);
// }