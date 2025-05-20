/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 12:23:06 by samcasti          #+#    #+#             */
/*   Updated: 2025/05/20 12:24:00 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	*path_access(char *cmd, char *cmd_copy)
{
	if (access(cmd, F_OK) != 0)
	{
		free(cmd_copy);
		return (NULL);
	}
	free(cmd_copy);
	return (ft_strdup(cmd));
}
