/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/25 18:12:31 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/25 18:26:01 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	free_arr(void **ptr)
{
	int	i;

	if (!ptr)
		return ;
	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int	ft_strisspace(char *str)
{
	int	check;

	if (!str || !(*str))
		return (0);
	check = 1;
	while (*str)
	{
		if (!ft_isspace(*str))
		{
			check = 0;
			break ;
		}
		str++;
	}
	return (check);
}

size_t	get_length(char **strs)
{
	size_t	len;

	len = 0;
	while (*strs)
	{
		len += ft_strlen(*strs);
		strs++;
	}
	return (len);
}

char	*ft_strtrim_all(const char *s1, const char *set)
{
	char	*new_str;
	char	**split;
	size_t	size_new_str;

	if (!s1)
		return (0);
	split = ft_split_set((char *)s1, (char *)set);
	if (!split)
		return (0);
	size_new_str = get_length(split);
	if (size_new_str == 0)
		return (ft_strdup(""));
	new_str = ft_calloc(size_new_str + 1, sizeof(char));
	if (!new_str)
		return (0);
	concat(new_str, split);
	free_arr((void **)split);
	return (new_str);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*sav_d;

	sav_d = dest;
	while (*dest)
		dest++;
	while (nb && *src)
	{
		*dest++ = *src++;
		nb--;
	}
	*dest = '\0';
	return (sav_d);
}
