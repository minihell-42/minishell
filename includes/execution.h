/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:36:27 by samcasti          #+#    #+#             */
/*   Updated: 2025/03/04 17:23:17 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

# define FORKED_CHILD 0
# define FORKED_ERROR -1

typedef struct s_context
{
	int	fd[2];
	int	fd_close;
}		t_context;

// EXECUTION
void	exec(t_tree *tree, char **envp);
int		exec_tree(t_tree *tree, t_context *ctx, char **envp);
int		exec_command(t_tree *tree, t_context *ctx, char **envp);
int		exec_pipe(t_tree *tree, t_context *ctx, char **envp);
int		exec_sequence(t_tree *tree, t_context *ctx, char **envp);
int		exec_redir(t_tree *tree, t_context *ctx, char **envp);

// PROGRAM PATH
char	*get_program_path(char *cmd, char **envp);

// BUILTINS
int		handle_builtins(t_tree *tree, t_context *ctx, char ***envp);

#endif
