/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:27 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:22:33 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	builtin_echo(int argc, char **argv)
{
	int i;
	int n_flag;

	i = 1;
	n_flag = 0;
	if (argc > 1 && !ft_strncmp(argv[1], "-n", 3))
	{
		n_flag = 1;
		i = 2;
	}
	while (i < argc)
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < argc - 1)
			ft_putchar_fd(' ', STDOUT_FILENO);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
