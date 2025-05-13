/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:44 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/13 14:45:38 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	print_export_format(char **env)
{
	int		i;
	char	*equals_pos;
	char	*value;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		equals_pos = ft_strchr(env[i], '=');
		if (equals_pos)
		{
			value = ft_strdup(equals_pos + 1);
			*equals_pos = '\0';
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putstr_fd("=\"", STDOUT_FILENO);
			ft_putstr_fd(value, STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
			*equals_pos = '=';
			free(value);
		}
		else
			ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

char	*ft_getenv(char *name, char **envp)
{
	int	i;
	int	len;

	if (!name || !envp)
		return (NULL);
	len = ft_strlen(name);
	i = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], name, len) && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	builtin_env(char **envp)
{
	int	i;

	if (!envp)
		return (1);
	i = 0;
	while (envp[i])
	{
		if (ft_strchr(envp[i], '='))
			ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
