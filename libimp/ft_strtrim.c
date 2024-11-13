/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 16:13:02 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/25 15:48:26 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_char(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	get_first_char(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && check_char(s1[i], set))
		i++;
	return (i);
}

static int	get_last_char(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i >= 0 && check_char(s1[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		first;
	int		last;
	int		i;
	char	*trim;

	first = get_first_char(s1, set);
	last = get_last_char(s1, set);
	if (first > last)
		last = first - 1;
	trim = malloc(last - first + 2);
	if (!trim)
		return (0);
	i = 0;
	while (first + i <= last)
	{
		trim[i] = s1[first + i];
		i++;
	}
	trim[i] = 0;
	return (trim);
}
