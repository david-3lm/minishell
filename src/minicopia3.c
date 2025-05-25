/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minicopia3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:02:41 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/25 18:38:32 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_strnstr_iterator(char *haystack, char *needle, size_t len)
{
	size_t	little_len;
	int		iterator;

	iterator = 0;
	little_len = ft_strlen(needle);
	if (little_len == 0)
		return (-1);
	if (len == 0)
		return (-1);
	while (haystack[iterator] && (int)(little_len <= len - iterator))
	{
		if (!ft_strncmp(&haystack[iterator], (char *)needle, little_len))
			return (iterator);
		iterator++;
	}
	return (-1);
}

void	skip_letters(const char *input, int *curr_pos)
{
	if (input[*curr_pos] == '$' || input[*curr_pos] == '/')
		(*curr_pos)++;
	while (input[*curr_pos] && !is_quote(input[*curr_pos])
		&& input[*curr_pos] != '$' && input[*curr_pos] != '/')
		(*curr_pos)++;
}

int	is_token_empty(void *content)
{
	int		check;
	char	*token;

	token = content;
	if (*token == '\0')
		check = 1;
	else
		check = 0;
	return (check);
}

void	ft_lstdel_first(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;

	if (lst == NULL || *lst == NULL)
		return ;
	tmp = *lst;
	tmp = tmp->next;
	del((*lst)->content);
	free(*lst);
	*lst = tmp;
}

void	ft_lstclear_if(t_list **lst, int (*cmp)(void *), void (*del)(void *))
{
	if (!lst)
		return ;
	while (*lst)
	{
		if (cmp((*lst)->content))
			ft_lstdel_first(lst, del);
		else
			lst = &(*lst)->next;
	}
}
