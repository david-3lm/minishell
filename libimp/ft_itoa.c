/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:24:12 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/18 17:04:12 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_units(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	check_neg(int n)
{
	return (n < 0);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				is_neg;
	int				units;
	unsigned int	nbr;

	is_neg = check_neg(n);
	if (is_neg)
		nbr = n * -1;
	else
		nbr = n;
	units = count_units(nbr) + is_neg;
	res = malloc(units + 1);
	if (!res)
		return (0);
	res[units] = 0;
	units--;
	while (units >= is_neg)
	{
		res[units] = nbr % 10 + '0';
		nbr /= 10;
		units--;
	}
	if (is_neg)
		res[0] = '-';
	return (res);
}
