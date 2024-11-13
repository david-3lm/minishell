/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 19:00:34 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/06/27 17:44:04 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_print_char(char c)
{
	return (write(1, &c, 1));
}

static int	ft_format(char format, va_list args)
{
	int	print_len;

	print_len = 0;
	if (format == 'c')
		print_len += ft_print_char(va_arg(args, int));
	else if (format == 's')
		print_len += ft_print_string(va_arg(args, char *));
	else if (format == 'd' || format == 'i')
		print_len += ft_print_nbr_dec(va_arg(args, int));
	else if (format == 'u')
		print_len += ft_print_unsigned(va_arg(args, unsigned int));
	else if (format == 'x' || format == 'X')
		print_len += ft_print_hex(va_arg(args, unsigned int), (format == 'X'));
	else if (format == 'p')
		print_len += ft_print_ptr(va_arg(args, size_t));
	else if (format == '%')
		print_len += ft_print_char('%');
	else
		print_len += ft_print_char(format);
	if (print_len == ERROR)
		return (ERROR);
	return (print_len);
}

int	ft_printf(char const *format, ...)
{
	va_list			args;
	int				i;
	int				print_len;
	int				aux;

	va_start(args, format);
	i = 0;
	print_len = 0;
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			aux = ft_format(format[i], args);
		}
		else
			aux = ft_print_char(format[i]);
		if (aux == ERROR)
			return (ERROR);
		print_len += aux;
		i++;
	}
	va_end(args);
	return (print_len);
}
