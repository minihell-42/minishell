/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:42:38 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/22 13:42:31 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while (i + j < len && haystack[i + j] == needle[j] && needle[j] != '\0')
			j++;
		if (needle[j] == '\0')
			return ((char *)&haystack[i]);
		i++;
	}
	return (0);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *haystack = "Hello World";
// 	const char *needle = "World";

// 	char *result = ft_strnstr(haystack, needle, 11);

// 	if (result != NULL)
// 	{
// 		printf("Found needle in haystack: %s\n", result);
// 	}
// 	else
// 	{
// 		printf("Did not find needle in haystack\n");
// 	}

// 	return (0);
// }