/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 19:16:08 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/24 17:27:27 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	quotes_are_closed(const char *input)
{
	int	i = 0;
	char	open_quote = '\0';

	while (input[i])
	{
		if (!open_quote && (input[i] == '\'' || input[i] == '"'))
			open_quote = input[i];
		else if (open_quote && input[i] == open_quote)
			open_quote = '\0';
		i++;
	}
	return (open_quote == '\0');
}

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


t_error_code	lexer(char *input, t_list *envl)
{
	t_token_list	*list;
	char			**sp;
	int				i;

	if (!quotes_are_closed(input))
	{
		ft_putendl_fd("Error: comillas sin cerrar", 2);	
		return (2);
	}
	sp = ft_split_set(input, " 	\n");
	i = 0;
	list = ft_calloc(1, sizeof(t_token_list));
	if (!list)
		return (MEM_ALLOC_ERROR);
	while (sp[i])
	{
		if (ft_strchr(sp[i], '|') || ft_strchr(sp[i], '<')
			|| ft_strchr(sp[i], '>'))
			purge_input(list, sp[i]);
		else
			add_token(list, sp[i]);
		i++;
	}
	return (parser(list, envl));
}
