/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:08 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/12/03 12:49:34 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	purge_input(t_token_list *list, const char *str)
{
	char	*aux;
	int		i;
	int		start;

	i = 0;
	start = 0;
	while (str[i])
	{
		while (str[i] != '|' && str[i] != '<' && str[i] != '>' && str[i])
			i++;
		if (i != 0 && i != start)
		{
			aux = ft_substr(str, start, i - start);
			add_token(list, aux);
		}
		start = i;
		while (str[i] == '|' || str[i] == '<' || str[i] == '>')
			i++;
		if (i != start)
		{
			aux = ft_substr(str, start, i - start);
			add_token(list, aux);
		}
		start = i;
	}
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
		if (ft_strchr(sp[i], '|') || ft_strchr(sp[i], '<') \
			|| ft_strchr(sp[i], '>'))
			purge_input(list, sp[i]);
		else
			add_token(list, sp[i]);
		i++;
	}
	return (parser(list));
}
