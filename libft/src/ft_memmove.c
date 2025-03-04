/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:40:35 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/22 13:40:36 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*destination;
	const unsigned char	*source;
	size_t				i;

	destination = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if (destination < source)
	{
		i = 0;
		while (i < len)
		{
			destination[i] = source[i];
			i++;
		}
	}
	else if (destination > source)
	{
		i = len;
		while (i > 0)
		{
			destination[i - 1] = source[i - 1];
			i--;
		}
	}
	return (dst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char	buffer[11] = "abcdefghij";

// 	printf("Before memmove: %s\n", buffer);
// 	ft_memmove(buffer + 4, buffer, 6);
// 	printf("After memmove: %s\n", buffer);
// 	return (0);
// }
