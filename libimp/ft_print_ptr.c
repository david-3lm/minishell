/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 15:52:33 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/06/27 12:03:46 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_ptr(size_t ptr)
{
	int	aux;

	if (!ptr)
	{
		aux = write(1, "(nil)", 5);
		if (aux == ERROR)
			return (ERROR);
		return (aux);
	}
	if (write(1, "0x", 2) == ERROR)
		return (ERROR);
	aux = ft_print_hex(ptr, 0);
	if (aux == ERROR)
		return (ERROR);
	return (aux + 2);
}
