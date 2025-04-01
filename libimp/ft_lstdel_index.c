/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:27:01 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/01 15:02:17 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_index(t_list **lst, int index)
{
	int		i;
	t_list	*aux;
	t_list	*to_delete;


	if (index >= ft_lstsize(*lst))
		return ;
	i = 0;
	to_delete = *lst;
	if (index == 0)
	{
		*lst = (*lst)->next;
		free(to_delete->content);
		return ;
	}
	aux = NULL;
	while (to_delete)
	{
		if (i == index)
			break ;
		aux = to_delete;
		to_delete = to_delete->next;
		i++;
	}
	aux->next = to_delete->next;
	free(to_delete->content);
}
