/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:47:27 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/25 17:44:59 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*new;

	i = 0;
	new = NULL;
	while (s[i])
	{
		if (s[i] == (char)c)
			new = ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		new = ((char *)&s[i]);
	return (new);
}

// #include <stdio.h>
// #include <string.h>

// int	main(void)
// {
// 	char	*str;
// 	int		c;

// 	str = "stringsing";
// 	c = 'x';
// 	printf("%s\n", ft_strrchr(str, c));
// 	printf("%s\n", strrchr(str, c));
// 	return (0);
// }
