/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:30:34 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/25 16:29:12 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	if (!*s)
		return (count);
	in_word = (*s != c);
	while (s[i])
	{
		if (s[i] == c && in_word)
		{
			count++;
			in_word = 0;
		}
		else if (s[i] != c)
			in_word = 1;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

static int	idxnsize_next_word(char const *s, char c, int start, int *size)
{
	int	i;
	int	siz;

	i = start;
	siz = 0;
	while (s[i] == c)
		i++;
	while (s[i + siz] != c && s[i + siz])
		siz++;
	*size = siz;
	return (i);
}

static int	free_mem(char **pptr, int i)
{
	while (0 <= i)
	{
		free(pptr[i]);
		i--;
	}
	free(pptr);
	return (0);
}

static int	compute_array(char const *s, char c, char **pptr, int words)
{
	int	i;
	int	idx;
	int	size;

	i = 0;
	idx = 0;
	size = 0;
	while (i < words - 1)
	{
		idx = idxnsize_next_word(s, c, idx + size, &size);
		pptr[i] = (char *) malloc(size + 1);
		if (!pptr[i])
		{
			free_mem(pptr, i);
			return (0);
		}
		ft_strlcpy(pptr[i], &s[idx], (int) size + 1);
		i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**pptr;
	int		words;

	if (!s)
		return (0);
	words = count_words(s, c) + 1;
	pptr = (char **) malloc(sizeof(char *) * (words));
	if (!pptr)
		return (0);
	if (!compute_array(s, c, pptr, words))
		return (0);
	pptr[words - 1] = 0;
	return (pptr);
}
