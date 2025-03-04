/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_letters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:31:41 by samcasti          #+#    #+#             */
/*   Updated: 2024/06/10 16:31:43 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	write_char(int c)
{
	return (write(1, &c, 1));
}

int	write_str(char *str)
{
	if (str == NULL)
		return (write(1, "(null)", 6));
	else
		return (write(1, str, ft_strlen(str)));
}
