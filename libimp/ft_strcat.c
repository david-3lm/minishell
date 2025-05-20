/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 18:14:03 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/20 18:16:18 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strcat(char *dest, char *src)
{
	char	*sav_d;

	sav_d = dest;
	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = '\0';
	return (sav_d);
}
