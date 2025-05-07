/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:24:40 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:24:42 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static char	*handle_absolute_path(char *cmd)
{
	char	*path;

	if (access(cmd, F_OK | X_OK) == 0)
	{
		path = ft_strdup(cmd);
		return (path);
	}
	return (NULL);
}

static char	*get_env_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*get_relative_path(char **paths_array, char *cmd)
{
	char	*path;
	char	*relative_path;
	int		i;

	i = 0;
	while (paths_array[i])
	{
		path = ft_strjoin(paths_array[i], "/");
		if (!path)
			return (NULL);
		relative_path = ft_strjoin(path, cmd);
		free(path);
		if (!relative_path)
			return (NULL);
		if (access(relative_path, F_OK | X_OK) == 0)
			return (relative_path);
		free(relative_path);
		i++;
	}
	return (NULL);
}

static char	*handle_relative_path(char *cmd, char **envp)
{
	char	*path_env;
	char	**paths_array;
	char	*relative_path;
	int		i;

	path_env = get_env_path(envp);
	if (!path_env)
		return (NULL);
	paths_array = ft_split(path_env, ':');
	if (!paths_array)
		return (NULL);
	relative_path = get_relative_path(paths_array, cmd);
	i = 0;
	while (paths_array[i])
		free(paths_array[i++]);
	free(paths_array);
	return (relative_path);
}

char	*get_program_path(char *cmd, char **envp)
{
	char	*program_path;
	char	*cmd_copy;

	cmd_copy = ft_strdup(cmd);
	if (!cmd_copy)
		return (NULL);
	if (cmd_copy[0] == '/')
	{
		program_path = handle_absolute_path(cmd_copy);
		free(cmd_copy);
		return (program_path);
	}
	else
	{
		program_path = handle_relative_path(cmd_copy, envp);
		free(cmd_copy);
		return (program_path);
	}
}
