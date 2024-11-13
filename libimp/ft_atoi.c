/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:29:25 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/10/28 16:02:34 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	else if (c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

long	ft_atoi(const char *nptr)
{
	long	aux;
	int		neg;

	aux = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-')
	{
		neg = -1;
		nptr++;
	}
	else
	{
		neg = 1;
		if (*nptr == '+')
			nptr++;
	}
	if (!ft_isdigit(*nptr))
		return (0);
	while (ft_isdigit(*nptr))
	{
		aux = aux * 10 + (*nptr - '0');
		nptr++;
	}
	return (aux * neg);
}
