#include "../../includes/execution.h"

static int	exec_builtins(t_tree *tree, t_context *ctx, char ***envp)
{
	int	children;

	if (tree->cmd_type == ECHO)
		children = builtin_echo(tree->argc, tree->argv);
	else if (tree->cmd_type == CD)
		children = builtin_cd(tree->argc, tree->argv, envp);
	else if (tree->cmd_type == PWD)
		children = builtin_pwd();
	else if (tree->cmd_type == EXPORT)
		children = builtin_export(tree->argc, tree->argv, envp);
	else if (tree->cmd_type == UNSET)
		children = builtin_unset(tree->argc, tree->argv, envp);
	else if (tree->cmd_type == ENV)
		children = builtin_env(*envp);
	else if (tree->cmd_type == EXIT)
		children = builtin_exit(tree->argc, tree->argv);
	else
		children = 1;
	return (children);
}
int	handle_builtins(t_tree *tree, t_context *ctx, char ***envp)
{
	int	stdin_backup;
	int	stdout_backup;
	int	children;

	stdin_backup = dup(STDIN_FILENO);
	stdout_backup = dup(STDOUT_FILENO);
	dup2(ctx->fd[STDIN_FILENO], STDIN_FILENO);
	dup2(ctx->fd[STDOUT_FILENO], STDOUT_FILENO);
	if (ctx->fd_close >= 0)
		close(ctx->fd_close);
	children = exec_builtins(tree, ctx, envp);
	dup2(stdin_backup, STDIN_FILENO);
	dup2(stdout_backup, STDOUT_FILENO);
	close(stdin_backup);
	close(stdout_backup);
	return (children);
}
