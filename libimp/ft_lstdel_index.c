/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:27:01 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/07 14:17:01 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>


void	ft_lstdel_index(t_list **lst, int index, void (*del)(void *))
{
	int		i;
	t_list	*prev;
	t_list	*curr;

	if (!lst || !*lst || index < 0 || index >= ft_lstsize(*lst))
		return ;
	curr = *lst;
	if (index == 0)
	{
		*lst = curr->next;
		ft_printf("hola\n");
		printf("content222:%p\n", (*lst)->content);
		ft_lstdelone(curr, del);
		return ;
	}
	i = 0;
	while (curr && i < index)
	{
		prev = curr;
		curr = curr->next;
		i++;
	}
	if (curr)
	{
		prev->next = curr->next;
		ft_lstdelone(curr, del);
	}
}

