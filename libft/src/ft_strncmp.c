/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:39:10 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/26 11:07:12 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	// char	*s1;
// 	// char	*s2;
// 	// size_t	n;
// 	// s1 = "";
// 	// s2 = "";
// 	// n = 2;
// 	printf("%d", ft_strncmp("abcdef", "abc\375xx", 5));
// 	return (0);
// }
