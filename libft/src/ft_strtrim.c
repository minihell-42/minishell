/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:52:40 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/26 14:24:55 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*create_buffer(char *str, int start, int end);

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*buf;

	start = 0;
	end = ft_strlen(s1) - 1;
	if (!s1 || !set)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[end]))
		end--;
	if (end - (start - 1) <= 0 || start >= ft_strlen(s1))
		return (ft_strdup(""));
	buf = create_buffer((char *)s1, start, end);
	if (!buf)
		return (NULL);
	return (buf);
}

char	*create_buffer(char *str, int start, int end)
{
	char	*buf;
	int		i;

	i = 0;
	buf = ft_calloc(end - (start - 1) + 1, sizeof(char));
	if (!buf)
		return (NULL);
	while (start <= end)
	{
		buf[i] = str[start];
		start++;
		i++;
	}
	return (buf);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char const	*s;
// 	char const	*set;

// 	s = "            ";
// 	set = " ";
// 	printf("%s\n", ft_strtrim(s, set));
// 	return (0);
// }
