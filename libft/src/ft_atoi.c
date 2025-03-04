/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:13:41 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/30 16:01:31 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	digit;
	int	minus;

	digit = 0;
	minus = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r') || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = 1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		digit = digit * 10 + (*str - '0');
		str++;
	}
	if (minus == 1)
		digit = digit * (-1);
	return (digit);
}

/* #include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char	*str;

	str = "    +3456as34";
	printf("%d\n", ft_atoi(str));
	printf("%d\n", atoi(str));
	return (0);
} */
