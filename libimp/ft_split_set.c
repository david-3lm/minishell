/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 12:30:34 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/19 15:30:05 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find(char s, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (s == c[i])
			return (1);
		i++;
	}
	return (0);
}

static int	count_words(char const *s, char *c)
{
	int	i;
	int	count;
	int	in_word;

	i = 0;
	count = 0;
	if (!*s)
		return (count);
	in_word = !find(*s, c);
	while (s[i])
	{
		if (find(s[i], c) && in_word)
		{
			count++;
			in_word = 0;
		}
		else if (!find(s[i], c))
			in_word = 1;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

static int	idxnsize_next_word(char const *s, char *c, int start, int *size)
{
	int	i;
	int	siz;
	int	idx;

	i = start;
	siz = 0;
	while (find(s[i], c))
		i++;
	while (!find(s[i + siz], c) && s[i + siz])
		siz++;
	if (s[i] == '"' || s[i] == '\'')
	{
		siz = 0;
		idx = i + 1;
		while (s[idx] != '"' && s[idx] != '\'' && s[idx])
			idx++;
		*size = idx - i + 1;
		return (i);
	}
	*size = siz;
	return (i);
}

static int	compute_array(char const *s, char *c, char **pptr, int words)
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
			while (0 <= i)
			{
				free(pptr[i]);
				i--;
			}
			free(pptr);
			return (0);
		}
		ft_strlcpy(pptr[i], &s[idx], (int) size + 1);
		i++;
	}
	return (1);
}

char	**ft_split_set(char *str, char *c)
{
	char	**res;
	int		words;

	words = count_words(str, c) + 1;
	res = (char **) ft_calloc(words, sizeof(char *));
	if (!res)
		return (NULL);
	if (!compute_array(str, c, res, words))
		return (0);
	res[words - 1] = 0;
	return (res);
}
