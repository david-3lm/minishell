/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:57:34 by dlopez-l          #+#    #+#             */
/*   Updated: 2024/01/26 12:01:55 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*aux;

	aux = lst;
	if (aux)
	{
		while (aux->next)
		{
			if (aux->content)
				(*f)(aux->content);
			aux = aux->next;
		}
		(*f)(aux->content);
	}
}
