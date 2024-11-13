/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:29:17 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/30 13:23:14 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

static void	move(unsigned char *a, unsigned char *b, size_t len)
{
	size_t	i;

	if (a < b)
	{
		i = 0;
		while (i < len)
		{
			a[i] = b[i];
			i++;
		}
	}
	else
	{
		while (len > 0)
		{
			len--;
			a[len] = b[len];
		}
	}
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (!dst && !src)
		return (dst);
	move(a, b, len);
	return (dst);
}
