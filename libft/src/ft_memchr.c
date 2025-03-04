/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:49:26 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/22 13:40:25 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *buffer = "Hello World";
// 	char c = 'W';

// 	char *result = ft_memchr(buffer, c, 11);

// 	if (result != NULL)
// 	{
// 		printf("Found character in buffer: %s\n", result);
// 	}
// 	else
// 	{
// 		printf("Did not find character in buffer\n");
// 	}

// 	return (0);
// }