/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 14:29:53 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/25 15:30:30 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!ft_strlen(little))
		return ((char *)big);
	while (*big && j < len)
	{
		i = 0;
		while (big[i] == little[i] && little[i] && i + j < len)
			i++;
		if (!little[i])
			return ((char *)big);
		big++;
		j++;
	}
	return (0);
}
