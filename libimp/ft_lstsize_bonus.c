/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 23:45:58 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/30 13:17:41 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*aux;

	i = 1;
	aux = lst;
	if (!aux)
		return (0);
	while (aux->next != NULL)
	{
		aux = aux->next;
		i++;
	}
	return (i);
}
