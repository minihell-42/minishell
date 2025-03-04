/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:37:43 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/22 13:40:32 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*destination;
	const unsigned char	*source;

	i = 0;
	destination = (unsigned char *)dst;
	source = (const unsigned char *)src;
	if (dst == (void *)0 && src == (void *)0)
		return (dst);
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (dst);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char	*src = "Hello World";
// 	char		dst[12];

// 	ft_memcpy(dst, src, 11);
// 	dst[11] = '\0';
// 	printf("After memcpy, dst: %s\n", dst);
// 	return (0);
// }
