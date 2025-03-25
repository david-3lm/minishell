/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 15:27:01 by cde-migu          #+#    #+#             */
/*   Updated: 2025/03/25 15:27:27 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_index(t_list *lst, int index)
{
	int		i;
	t_list	*aux;
	t_list	*to_delete;

	i = 0;
	aux = lst;
	while (i < index - 1)
	{
		aux = aux->next;
		i++;
	}
	to_delete = aux->next;
	aux->next = aux->next->next;
	free(to_delete);
}
