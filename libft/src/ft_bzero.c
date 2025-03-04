/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:25:19 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/22 13:45:39 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*str;
	size_t			i;

	str = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return ;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}

// #include <stdio.h>
// #include <strings.h>

// int	main(void)
// {
// 	char s1[50] = "Hello, World!";
// 	char s2[50] = "Hello, World!";
// 	size_t n = 14;

// 	ft_bzero(s1, n);
// 	bzero(s2, n);

// 	if (memcmp(s1, s2, n) == 0)
// 	{
// 		printf("ft_bzero works correctly\n");
// 	}
// 	else
// 	{
// 		printf("ft_bzero does not work correctly\n");
// 	}

// 	return (0);
// }