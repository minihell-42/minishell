/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:39:55 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/22 14:43:46 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*buf;
	size_t	i;

	i = 0;
	buf = malloc(count * size);
	if (buf == NULL)
		return (NULL);
	while (i < count * size)
	{
		((char *)buf)[i] = 0;
		i++;
	}
	return (buf);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	size_t	size;
// 	size_t	count;
// 	void	*buf1;
// 	void	*buf2;

// 	size = 7;
// 	count = 7;
// 	buf1 = ft_calloc(count, size);
// 	buf2 = calloc(count, size);
// 	if (memcmp(buf1, buf2, count * size) == 0)
// 	{
// 		printf("works\n");
// 	}
// 	else
// 	{
// 		printf("does not work correctly\n");
// 	}
// 	free(buf1);
// 	free(buf2);
// 	return (0);
// }
