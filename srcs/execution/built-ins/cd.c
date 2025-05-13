/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:20 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:22:22 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	print_dir_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

char	*get_path(int argc, char ***envp, char **argv)
{
	char	*path;

	if (argc > 2)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", STDERR_FILENO);
		return (NULL);
	}
	else if (argc == 1)
	{
		path = ft_getenv("HOME", *envp);
		if (!path)
		{
			ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
			return (NULL);
		}
	}
	else
		path = argv[1];
	return (path);
}

int	builtin_cd(int argc, char **argv, char ***envp)
{
	char	*path;
	char	cwd[PATH_MAX];
	char	*old_pwd;

	old_pwd = getcwd(cwd, PATH_MAX);
	path = get_path(argc, envp, argv);
	if (!path)
		return (1);
	if (chdir(path) != 0)
	{
		print_dir_error(path);
		return (1);
	}
	if (old_pwd)
		update_pwd(old_pwd, envp);
	return (0);
}
