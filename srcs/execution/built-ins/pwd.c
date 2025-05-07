/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:23:14 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:23:16 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_pwd(void)
{
	char cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		ft_putendl_fd(cwd, STDOUT_FILENO);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell: pwd: ", STDERR_FILENO);
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
		return (1);
	}
}
