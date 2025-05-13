/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:23:56 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/13 15:31:43 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	copy_vars_to_new_env(char ***envp, char **new_env, char *name, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], name, len) != 0
				|| ((*envp)[i][len] != '=' && (*envp)[i][len] != '\0'))
		{
			new_env[j] = ft_strdup((*envp)[i]);
			if (!new_env[j])
			{
				while (j > 0)
					free(new_env[--j]);
				free(new_env);
				return ;
			}
			j++;
		}
		i++;
	}
	new_env[j] = NULL;
	ft_free_array(*envp);
	*envp = new_env;
}

void	unset_env_var(char *name, char ***envp)
{
	int		i;
	int		len;
	char	**new_env;

	if (!name || !envp || !(*envp))
		return ;
	len = ft_strlen(name);
	i = 0;
	while ((*envp)[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (!new_env)
		return ;
	copy_vars_to_new_env(envp, new_env, name, len);
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	**copy_environment(char **original_env)
{
	char	**new_env;
	int		i;

	if (!original_env)
		return (NULL);
	i = 0;
	while (original_env[i])
		i++;
	new_env = malloc(sizeof(char *) * (400));
	if (!new_env)
		return (NULL);
	i = 0;
	while (original_env[i])
	{
		new_env[i] = ft_strdup(original_env[i]);
		if (!new_env[i])
		{
			ft_free_array(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}
