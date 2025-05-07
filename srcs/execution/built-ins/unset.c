/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:23:20 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:23:22 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_unset(int argc, char **argv, char ***envp)
{
	int	i;
	int	result;

	result = 0;
	i = 1;
	while (i < argc)
	{
		if (is_valid_identifier(argv[i]))
			unset_env_var(argv[i], envp);
		else
		{
			ft_putstr_fd("minishell: unset: `", STDERR_FILENO);
			ft_putstr_fd(argv[i], STDERR_FILENO);
			ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
			result = 1;
		}
		i++;
	}
	return (result);
}
