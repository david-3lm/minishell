/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:29:48 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/23 13:16:37 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char *) s1;
	us2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (us1[i] && us2[i] && i < n - 1)
	{
		if (us1[i] != us2[i])
			return (us1[i] - us2[i]);
		i++;
	}
	return (us1[i] - us2[i]);
}
