// #include "../../includes/execution.h"

// #define GREEN "\033[0;32m"
// #define RED "\033[0;31m"
// #define YELLOW "\033[0;33m"
// #define RESET "\033[0m"

// // /*
// // ** Creates a controlled environment for testing builtins
// // */
// // static char	**create_test_env(void)
// // {
// // 	char	**test_env;

// // 	test_env = malloc(sizeof(char *) * 4);
// // 	if (!test_env)
// // 		return (NULL);
// // 	test_env[0] = ft_strdup("PATH=/bin:/usr/bin");
// // 	test_env[1] = ft_strdup("HOME=/home");
// // 	test_env[2] = ft_strdup("PWD=/current/dir");
// // 	test_env[3] = NULL;
// // 	return (test_env);
// // }

// /*
// ** Prints a formatted test header
// */
// static void	print_test_header(char *test_name)
// {
// 	printf("\n%s==== Testing %s ====%s\n", YELLOW, test_name, RESET);
// }

// /*
// ** Prints formatted test result
// */
// static void	print_result(char *test_name, int result)
// {
// 	if (result == 0)
// 		printf("%s✓ %s passed%s\n", GREEN, test_name, RESET);
// 	else
// 		printf("%s✗ %s failed (return (code: %d)%s\n", RED, test_name, result,
// 			RESET);
// }

// /*
// ** Tests the echo builtin command
// */
// static void	test_echo(void)
// {
// 	int		ret;
// 	char	*args1[] = {"echo", "Hello World", NULL};
// 	char	*args2[] = {"echo", "-n", "No newline", NULL};

// 	print_test_header("echo");
// 	printf("Test 1 (regular echo): ");
// 	ret = builtin_echo(2, args1);
// 	print_result("regular echo", ret);
// 	printf("Test 2 (echo -n): ");
// 	ret = builtin_echo(3, args2);
// 	printf("\n"); // Add newline after -n test
// 	print_result("echo -n", ret);
// }

// /*
// ** Tests the pwd builtin command
// */
// static void	test_pwd(void)
// {
// 	int	ret;

// 	print_test_header("pwd");
// 	printf("Test 1 (pwd): ");
// 	ret = builtin_pwd();
// 	print_result("pwd", ret);
// }

// /*
// ** Tests the cd builtin command
// */
// static void	test_cd(char ***envp)
// {
// 	int		ret;
// 	char	*args1[] = {"cd", "..", NULL};
// 	char	*args2[] = {"cd", "/tmp", NULL};
// 	char	*args3[] = {"cd", NULL};
// 	char	cwd_before[PATH_MAX];
// 	char	cwd_after[PATH_MAX];

// 	print_test_header("cd");
// 	// Test relative path
// 	getcwd(cwd_before, PATH_MAX);
// 	printf("Test 1 (cd ..): ");
// 	ret = builtin_cd(2, args1, envp);
// 	getcwd(cwd_after, PATH_MAX);
// 	printf("Changed from %s to %s\n", cwd_before, cwd_after);
// 	print_result("cd ..", ret);
// 	// Test absolute path
// 	getcwd(cwd_before, PATH_MAX);
// 	printf("Test 2 (cd /tmp): ");
// 	ret = builtin_cd(2, args2, envp);
// 	getcwd(cwd_after, PATH_MAX);
// 	printf("Changed from %s to %s\n", cwd_before, cwd_after);
// 	print_result("cd /tmp", ret);
// 	// Test HOME
// 	getcwd(cwd_before, PATH_MAX);
// 	printf("Test 3 (cd to HOME): ");
// 	ret = builtin_cd(1, args3, envp);
// 	getcwd(cwd_after, PATH_MAX);
// 	printf("Changed from %s to %s\n", cwd_before, cwd_after);
// 	print_result("cd to HOME", ret);
// }

// /*
// ** Tests the export builtin command
// */
// static void	test_export(char ***envp)
// {
// 	int		ret;
// 	char	*args1[] = {"export", "TEST_VAR=test_value", NULL};
// 	char	*args2[] = {"export", "PATH=/custom/path", NULL};
// 	char	*args3[] = {"export", NULL};

// 	print_test_header("export");
// 	printf("Test 1 (export new var): ");
// 	ret = builtin_export(2, args1, envp);
// 	printf("Value after export: %s\n", ft_getenv("TEST_VAR", *envp));
// 	print_result("export new var", ret);
// 	printf("Test 2 (export existing var): ");
// 	ret = builtin_export(2, args2, envp);
// 	printf("PATH after export: %s\n", ft_getenv("PATH", *envp));
// 	print_result("export existing var", ret);
// 	printf("Test 3 (export with no args): \n");
// 	ret = builtin_export(1, args3, envp);
// 	print_result("export with no args", ret);
// }

// /*
// ** Tests the unset builtin command
// */
// static void	test_unset(char ***envp)
// {
// 	int		ret;
// 	char	*args1[] = {"unset", "TEST_VAR", NULL};
// 	char	*args2[] = {"unset", "TEMP_VAR", NULL};  // Changed from PATH to TEMP_VAR

// 	print_test_header("unset");
	
// 	// First make sure TEST_VAR exists
// 	set_env_var("TEST_VAR=for_unset_test", envp);
// 	// Add a temporary variable to unset
// 	set_env_var("TEMP_VAR=temporary", envp);
	
// 	printf("Test 1 (unset TEST_VAR): ");
// 	printf("Before unset: %s\n", ft_getenv("TEST_VAR", *envp));
// 	ret = builtin_unset(2, args1, envp);
// 	printf("After unset: %s\n", ft_getenv("TEST_VAR", *envp));
// 	print_result("unset TEST_VAR", ret);
	
// 	printf("Test 2 (unset TEMP_VAR): ");  // Changed from PATH to TEMP_VAR
// 	printf("Before unset: %s\n", ft_getenv("TEMP_VAR", *envp));  // Changed from PATH to TEMP_VAR
// 	ret = builtin_unset(2, args2, envp);
// 	printf("After unset: %s\n", ft_getenv("TEMP_VAR", *envp));  // Changed from PATH to TEMP_VAR
// 	print_result("unset TEMP_VAR", ret);  // Changed from PATH to TEMP_VAR
// }

// /*
// ** Tests the env builtin command
// */
// static void	test_env_builtin(char **envp)
// {
// 	int	ret;

// 	print_test_header("env");
// 	printf("Test 1 (env): \n");
// 	ret = builtin_env(envp);
// 	print_result("env", ret);
// }

// /*
// ** Runs all the builtin command tests
// */
// static void	run_builtin_tests(char	**test_env)
// {

// 	printf("%s==== BUILTIN COMMAND TESTS ====%s\n", YELLOW, RESET);
	
// 	if (!test_env)
// 	{
// 		printf("%sError: Failed to create test environment%s\n", RED, RESET);
// 		return ;
// 	}
	
// 	test_echo();
// 	test_pwd();
// 	test_cd(&test_env);
// 	test_export(&test_env);
// 	test_unset(&test_env);
// 	test_env_builtin(test_env);
	
// 	printf("\n%s==== All tests completed ====%s\n", YELLOW, RESET);
	
// 	// Safely clean up each item
// 	if (test_env)
// 	{
// 		int i = 0;
// 		while (test_env[i])
// 		{
// 			free(test_env[i]);
// 			i++;
// 		}
// 		free(test_env);
// 	}
// }

// /*
// ** Main function to run all tests
// */
// int	main(int argc, char **argv, char **envp)
// {
// 	char	**shell_env;

// 	(void)argc;
// 	(void)argv;
// 	shell_env = copy_environment(envp);
// 	if (!shell_env)
// 		return (1);
// 	run_builtin_tests(shell_env);
// 	return (0);
// }
