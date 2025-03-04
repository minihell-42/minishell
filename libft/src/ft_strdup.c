/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:51:36 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/25 13:07:53 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*buf;
	size_t	length;
	size_t	i;

	i = 0;
	length = ft_strlen(s1);
	buf = (char *)malloc(sizeof(char) * (length + 1));
	if (buf == NULL)
		return (NULL);
	while (i < length)
	{
		buf[i] = s1[i];
		i++;
	}
	buf[i] = '\0';
	return (buf);
}
