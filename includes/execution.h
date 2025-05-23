/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 13:36:27 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/12 19:18:57 by dgomez-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "parser.h"

typedef struct s_tree	t_tree;

# define FORKED_CHILD 0
# define FORKED_ERROR -1
# define ENV_BUFFER 400

typedef struct s_tree	t_tree;
typedef struct s_context
{
	char	*last_failed_file;
	int		fd[2];
	int		fd_close;
}		t_context;

typedef struct s_expand_vars
{
	char	*result;
	char	*var_start;
	char	*var_end;
	char	*var_name;
	char	*var_value;
}		t_expand_vars;

// EXECUTION
void	exec(t_tree *tree, char ***envp);
int		exec_tree(t_tree *tree, t_context *ctx, char ***envp);
int		exec_command(t_tree *tree, t_context *ctx, char ***envp);
int		exec_pipe(t_tree *tree, t_context *ctx, char ***envp);
int		exec_redir(t_tree *tree, t_context *ctx, char ***envp);

// COMMANDS UTILS
int		handle_command_not_found(t_tree *tree);
int		handle_is_directory(t_tree *tree, char *program_path);
int		handle_builtin_with_fd(t_tree *tree, t_context *ctx, char ***envp);
void	clean_empty_argv(t_tree *tree);
int		handle_fork_error(char *program_path);
void	write_cmd_error(t_tree *tree);

// PROGRAM PATH
char	*get_program_path(char *cmd, char **envp);
char	*path_access(char *cmd, char *cmd_copy);

// BUILTINS
int		handle_builtins(t_tree *tree, t_context *ctx, char ***envp);
int		builtin_echo(int argc, char **argv);
int		builtin_cd(int argc, char **argv, char ***envp);
int		builtin_pwd(void);
int		builtin_export(int argc, char **argv, char ***envp);
int		builtin_unset(int argc, char **argv, char ***envp);
int		builtin_env(char **envp);
int		builtin_exit(t_tree *tree, char ***envp);

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
char	*expand_env_var(char *var, char **envp);
void	expand_env_vars_in_tree(t_tree *tree, char **envp);
char	*expand_vars_in_string(char *str, char **envp);
int		contains_env_var(char *str);
int		is_pure_variable(const char *str);
void	append_prefix(t_expand_vars *vars, char *str, int i);
void	append_remainder(t_expand_vars *vars, char *str, int i);
int		process_variable(t_expand_vars *vars, char *str, char **envp);

// HEREDOC
void	process_heredocs(t_tree *root, char **envp);
#endif
