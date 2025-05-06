/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:23:42 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:23:43 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	old_size;
	char **old_array;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	old_array = (char **)ptr;
	old_size = 0;
	while (old_array[old_size])
		old_size++;
	old_size = (old_size + 1) * sizeof(char *);
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);
	ft_memcpy(new_ptr, ptr, old_size < new_size ? old_size : new_size); 
	free(ptr);
	return (new_ptr);
}

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || !*str || (!ft_isalpha(*str) && *str != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	print_sorted_env(char **envp)
{
	int		i;
	int		count;
	char	**sorted_env;

	count = 0;
	while (envp[count])
		count++;
	sorted_env = malloc(sizeof(char *) * (count + 1));
	if (!sorted_env)
		return (1);
	i = 0;
	while (i < count)
	{
		sorted_env[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted_env[i] = NULL;
	sort_env(sorted_env, count);
	print_export_format(sorted_env);
	ft_free_array(sorted_env);
	return (0);
}

void	sort_env(char **env, int count)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (i < count - 1)
	{
		j = 0;
		while (j < count - i - 1)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i++;
	}
}

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
