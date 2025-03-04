/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:21:14 by samcasti          #+#    #+#             */
/*   Updated: 2025/02/05 18:21:35 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	result;

	result = 0;
	while (*s1 || *s2)
	{
		if (*s1 == *s2)
			result = 0;
		else
		{
			result = *s1 - *s2;
			break ;
		}
		s1++;
		s2++;
	}
	return (result);
}
