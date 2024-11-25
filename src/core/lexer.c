/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:08 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/11/25 11:45:30 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
