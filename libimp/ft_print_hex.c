/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:00:26 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/02/22 15:31:21 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	write_from_string(size_t arg, int cap)
{
	const char	caps[] = "0123456789ABCDEF";
	const char	mins[] = "0123456789abcdef";

	if (cap)
		return (write(1, &caps[arg % 16], 1));
	return (write(1, &mins[arg % 16], 1));
}

int	ft_print_hex(size_t arg, int cap)
{
	int			count;
	int			aux;

	count = 0;
	if (arg < 16)
		return (write_from_string(arg, cap));
	aux = ft_print_hex(arg / 16, cap);
	if (aux == ERROR)
		return (ERROR);
	count += aux;
	aux = ft_print_hex(arg % 16, cap);
	if (aux == ERROR)
		return (ERROR);
	count += aux;
	return (count);
}
