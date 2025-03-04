/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:44:38 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/24 17:36:50 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*str;

	str = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		str[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	buffer[10];

// 	// ft_memset(buffer, 'a', sizeof(buffer) - 1);
// 	memset(buffer, 'a', sizeof(buffer) - 1);
// 	buffer[sizeof(buffer) - 1] = '\0'; // Null-terminate the buffer
// 	printf("Buffer after memset: %s\n", buffer);
// 	return (0);
// }
