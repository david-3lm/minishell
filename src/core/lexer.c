/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:08 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/26 20:54:11 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	count_delims(char *str)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '|')
			count ++;
		if (str[i] == '<')
		{
			if (str[i + 1] == '<')
				i++;
			count++;
		}
		if (str[i] == '>')
		{
			if (str[i + 1] == '>')
				i++;
			count++;
		}
		i++;
	}
	return (count);
}

char	**check_split(char **sp)
{
	char	**aux;
	int		i;
	int		delims;

	delims = 0;
	while (sp[i])
	{
		delims += count_delims(sp[i]);
		i++;
	}
	aux = (char **) ft_calloc(i + delims, sizeof(char *));
	if (!aux)
		return (NULL);
	return (NULL);
}

t_error_code	lexer(char *input)
{
	t_token_list	*list;
	char			**sp;
	int				i;

	sp = ft_split_set(input, " 	\n");
	i = 0;
	list = ft_calloc(1, sizeof(t_token_list));
	if (!list)
		return (MEM_ALLOC_ERROR);
	while (sp[i])
	{
		add_token(list, sp[i]);
		i++;
	}
	return (parser(list));
}
