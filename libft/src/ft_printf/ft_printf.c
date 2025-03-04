/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samcasti <samcasti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:30:59 by samcasti          #+#    #+#             */
/*   Updated: 2024/06/10 16:59:22 by samcasti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		written_chars;

	va_start(ap, format);
	written_chars = 0;
	while (*format)
	{
		if (*format == '%')
			written_chars += print_args(ap, *(++format));
		else
			written_chars += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (written_chars);
}

int	print_args(va_list ap, char specifier)
{
	int	chars_written;

	chars_written = 0;
	if (specifier == 'c')
		chars_written += write_char(va_arg(ap, int));
	else if (specifier == 's')
		chars_written += write_str(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		chars_written += write_digit(va_arg(ap, int));
	else if (specifier == 'u')
		chars_written += write_unsigned(va_arg(ap, int), 10, 0);
	else if (specifier == 'x')
		chars_written += write_unsigned(va_arg(ap, int), 16, 0);
	else if (specifier == 'X')
		chars_written += write_unsigned(va_arg(ap, int), 16, 1);
	else if (specifier == '%')
		chars_written += write_char('%');
	else if (specifier == 'p')
		chars_written += write_ptr(va_arg(ap, void *));
	else
		chars_written += write(1, &specifier, 1);
	return (chars_written);
}
