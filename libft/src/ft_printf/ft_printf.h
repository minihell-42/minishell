/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 16:15:57 by samcasti          #+#    #+#             */
/*   Updated: 2024/06/10 16:38:39 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../include/libft.h"
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	print_args(va_list ap, char specifier);
int	write_char(int c);
int	write_str(char *str);
int	write_digit(long int n);
int	write_unsigned(unsigned int n, unsigned int base, int is_upper);
int	write_ptr(void *ptr);

#endif
