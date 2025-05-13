/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:23:42 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/13 14:53:41 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

static int	get_size(int old_size, int new_size)
{
	if (old_size < new_size)
		return (new_size);
	else
		return (old_size);
}

void	*ft_realloc(void *ptr, size_t new_size)
{
	void	*new_ptr;
	size_t	old_size;
	char	**old_array;
	int		size;

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
	size = get_size(old_size, new_size);
	ft_memcpy(new_ptr, ptr, size); 
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
