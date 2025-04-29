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

typedef struct s_tree t_tree;

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
int		builtin_echo(int argc, char **argv);
int		builtin_cd(int argc, char **argv, char ***envp);
int		builtin_pwd(void);
int		builtin_export(int argc, char **argv, char ***envp);
int		builtin_unset(int argc, char **argv, char ***envp);
int		builtin_env(char **envp);
int		builtin_exit(int argc, char **argv);

// BUILTIN UTILS
char	*ft_getenv(char *name, char **envp);
void	update_pwd(char *old_pwd, char ***envp);
int		set_env_var(char *var_string, char ***envp);
void	*ft_realloc(void *ptr, size_t new_size);
int		is_valid_identifier(char *str);
int		print_sorted_env(char **envp);
void	sort_env(char **env, int count);
void	print_export_format(char **env);
void	unset_env_var(char *name, char ***envp);
void	ft_free_array(char **array);
int		is_numeric(char *str);

// ENVIRONMENT MANAGEMENT
char	**copy_environment(char **original_env);

#endif
