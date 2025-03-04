/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 12:44:14 by samcasti          #+#    #+#             */
/*   Updated: 2024/04/24 16:43:16 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		get_sign(int n);
int		get_length(int n);

char	*ft_itoa(int n)
{
	int		sign;
	int		len;
	char	*str;

	sign = get_sign(n);
	len = get_length(n);
	if (sign == -1)
		len++;
	str = ft_calloc((len + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	while (len--)
	{
		str[len] = (n % 10) * sign + '0';
		n = n / 10;
	}
	if (sign == -1)
		str[0] = '-';
	return (str);
}

int	get_sign(int n)
{
	if (n < 0)
		return (-1);
	else
		return (1);
}

int	get_length(int n)
{
	int	len;

	if (n == 0)
		len = 1;
	else
	{
		len = 0;
		while (n != 0)
		{
			n = n / 10;
			len++;
		}
	}
	return (len);
}

// #include <stdio.h>

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(5667574));
// 	return (0);
// }
