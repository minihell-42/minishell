/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:23:06 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:23:07 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_export(int argc, char **argv, char ***envp)
{
	int i;
	int result;

	result = 0;
	if (argc == 1)
		return (print_sorted_env(*envp));
	i = 1;
	while (i < argc)
	{
		if (is_valid_identifier(argv[i]))
		{
			if (set_env_var(argv[i], envp) != 0)
				result = 1;
		}
		else
		{
			ft_putstr_fd("minishell: export: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			result = 1;
		}
		i++;
	}
	return (result);
}
