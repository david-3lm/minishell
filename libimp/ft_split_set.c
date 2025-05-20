/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:30:34 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/20 15:53:51 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	concat_all(char *dest, char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		ft_strcat(dest, strs[i]);
		i++;
	}
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

char	**ft_split_set(char *str, char *charset)
{
	char	**strs;
	int		i;
	int		j;
	int		k;

	j = 0;
	k = 0;
	if (str == 0)
		return (0);
	strs = malloc((find_length(str, charset) + 1) * sizeof(char *));
	if (!strs)
		return (0);
	while (str[j] != '\0')
	{
		i = j;
		while (!ft_strchr(charset, str[j]) && str[j] != '\0')
			j++;
		if (i != j)
			import_str(&strs[k++], &str[i], i, j);
		else
			j++;
	}
	strs[k] = 0;
	return (strs);
}
