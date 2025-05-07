/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:22:44 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/06 17:22:46 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

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
