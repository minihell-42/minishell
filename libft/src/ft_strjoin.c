/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:38:36 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/25 13:08:02 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*buf;

	i = 0;
	j = 0;
	buf = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (buf == NULL)
		return (NULL);
	while (s1[i])
	{
		buf[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		buf[i] = s2[j];
		i++;
		j++;
	}
	buf[i] = '\0';
	return (buf);
}

// int	main(void)
// {
// 	char *s1 = "This, ";
// 	char *s2 = "That.";

// 	printf("%s", ft_strjoin(s1, s2));
// 	return (0);
// }
