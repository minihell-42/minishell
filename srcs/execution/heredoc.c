#include "execution.h"

static int	open_heredoc_pipe(char *delimiter, t_quote_type quote, char **envp)
{
	int		fds[2];
	char	*line;
	char	*exp;

	if (pipe(fds) == -1)
		return (perror("minishell: pipe"), -1);
	while (1)
	{
		ft_putstr_fd("heredoc> ", STDERR_FILENO);
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
		if (quote != QUOTE_SINGLE)
		{
			exp = expand_vars_in_string(line, envp);
			ft_putendl_fd(exp, fds[1]);
			free(exp);
		}
		else
			ft_putendl_fd(line, fds[1]);
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}

void	process_heredocs(t_tree *root, char **envp)
{
	if (!root)
		return ;
	if (root->type == NODE_REDIR && root->redir_type == HERE_DOC)
	{
		root->here_doc_fd = open_heredoc_pipe(root->input_file,
				root->input_quote, envp);
	}
	process_heredocs(root->left, envp);
	process_heredocs(root->right, envp);
}
