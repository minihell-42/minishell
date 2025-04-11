#include "../../includes/execution.h"

static void	run_heredoc(int pipe_fd[2], char *delimiter)
{
	char	*line;

	ft_putstr_fd("heredoc> ", STDERR_FILENO);
	while (1)
	{
		line = readline("");
		if (!line)
		{
			ft_putendl_fd("\nminishell: warning: here-document delimited by end-of-file",
				STDERR_FILENO);
			break ;
		}
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break ;
		}
		ft_putendl_fd(line, pipe_fd[STDOUT_FILENO]);
		free(line);
		ft_putstr_fd("heredoc> ", STDERR_FILENO);
	}
}

static int	create_heredoc(char *delimiter)
{
	int	pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe failed");
		return (-1);
	}
	run_heredoc(pipe_fd, delimiter);
	close(pipe_fd[STDOUT_FILENO]);
	return (pipe_fd[STDIN_FILENO]);
}

static int	exec_input_redir(t_tree *tree, t_context *ctx)
{
	int	infile;

	if (tree->redir_type == TKN_HERE_DOC)
	{
		infile = create_heredoc(tree->input_file);
		if (infile == -1)
			return (-1);
	}
	else
	{
		if ((infile = open(tree->input_file, O_RDONLY)) == -1)
		{
			perror("minishell: open file failed");
			return (-1);
		}
	}
	if (ctx->fd[STDIN_FILENO] != STDIN_FILENO)
		close(ctx->fd[STDIN_FILENO]);
	ctx->fd[STDIN_FILENO] = infile;
	return (0);
}

static int	exec_output_redir(t_tree *tree, t_context *ctx)
{
	int	outfile;
	int	flags;

	if (!tree->output_file)
		return (0);
	flags = O_WRONLY | O_CREAT;
	if (tree->redir_type == TKN_REDIR_APPEND)
		flags |= O_APPEND;
	else if (tree->redir_type == TKN_REDIR_OUT)
		flags |= O_TRUNC;
	if ((outfile = open(tree->output_file, flags, 0644)) == -1)
	{
		perror("minishell: open output file failed");
		return (-1);
	}
	if (ctx->fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(ctx->fd_close);
	ctx->fd[STDOUT_FILENO] = outfile;
	return (0);
}

int	exec_redir(t_tree *tree, t_context *ctx, char **envp)
{
	int			children;
	t_context	redir_ctx;

	redir_ctx = *ctx;
	if (tree->input_file)
	{
		if (exec_input_redir(tree, &redir_ctx) == -1)
			return (-1);
	}
	if (tree->output_file)
	{
		if (exec_output_redir(tree, &redir_ctx) == -1)
		{
			if (tree->input_file && redir_ctx.fd[STDIN_FILENO] != STDIN_FILENO)
				close(redir_ctx.fd[STDIN_FILENO]);
			return (-1);
		}
	}
	redir_ctx.fd_close = -1;
	children = exec_tree(tree->left, &redir_ctx, envp);
	if (tree->input_file && redir_ctx.fd[STDIN_FILENO] != STDIN_FILENO)
		close(redir_ctx.fd[STDIN_FILENO]);
	if (tree->output_file && redir_ctx.fd[STDOUT_FILENO] != STDOUT_FILENO)
		close(redir_ctx.fd[STDOUT_FILENO]);
	return (children);
}
