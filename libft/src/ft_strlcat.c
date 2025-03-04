/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:41:51 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/25 13:11:08 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	space_left;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	space_left = dstsize - i - 1;
	if (space_left == 0 || i == dstsize)
		return (i + ft_strlen(src));
	while (src[j] != '\0' && j < space_left)
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}

// #include <stdio.h>

// int	main(void)
// {
// 	char		dst[20] = "Hello";
// 	const char	*src = " World";
// 	size_t		dstsize;
// 	size_t		result;

// 	dstsize = sizeof(dst);
// 	result = ft_strlcat(dst, src, dstsize);
// 	printf("After strlcat, dst: %s\n", dst);
// 	printf("Return value: %zu\n", result);
// 	return (0);
// }
