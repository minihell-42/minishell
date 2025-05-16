/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgomez-a <dgomez-a@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 19:20:33 by dgomez-a          #+#    #+#             */
/*   Updated: 2025/05/12 19:23:51 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"

static void	write_heredoc_output(char *line, t_quote_type quote, char **envp,
		int fd)
{
	char	*exp;

	if (quote != QUOTE_SINGLE)
	{
		exp = expand_vars_in_string(line, envp);
		ft_putendl_fd(exp, fd);
		free(exp);
	}
	else
		ft_putendl_fd(line, fd);
}

static int	open_heredoc_pipe(char *delimiter, t_quote_type quote, char **envp)
{
	int		fds[2];
	char	*line;

	if (pipe(fds) == -1)
		return (perror("minishell: pipe"), -1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || ft_strcmp(line, delimiter) == 0)
		{
			if (!line)
				ft_putendl_fd("\nminishell: warning: here-doc delimited by EOF",
					STDERR_FILENO);
			free(line);
			break ;
		}
		write_heredoc_output(line, quote, envp, fds[1]);
		free(line);
	}
	close(fds[1]);
	return (fds[0]);
}

void	process_heredocs(t_tree *root, char **envp)
{
	if (!root)
		return ;
	process_heredocs(root->left, envp);
	if (root->type == NODE_REDIR && root->redir_type == HERE_DOC)
	{
		root->here_doc_fd = open_heredoc_pipe(root->input_file,
				root->input_quote, envp);
	}
	process_heredocs(root->right, envp);
}
