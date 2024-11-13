/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:56:25 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/25 12:13:03 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	size_s1;
	size_t	size_s2;
	size_t	size_ptr;
	char	*ptr;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	size_ptr = size_s1 + size_s2 + 1;
	ptr = malloc(size_ptr);
	if (!ptr)
		return (0);
	ft_strlcpy(ptr, s1, size_s1 + 1);
	ft_strlcat(ptr, s2, size_ptr);
	return (ptr);
}
