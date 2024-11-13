/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 12:10:11 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/23 18:09:54 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	i = 0;
	src_len = ft_strlen(src);
	dst_len = ft_strlen(dst);
	if (dstsize < dst_len + 1)
		return (src_len + dstsize);
	if (dstsize > dst_len + 1)
	{
		i = 0;
		while (src[i] && i + dst_len < dstsize - 1)
		{
			dst[i + dst_len] = src[i];
			i++;
		}
		dst[i + dst_len] = '\0';
	}
	return (dst_len + src_len);
}
