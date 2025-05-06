/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 13:38:23 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/06 11:13:13 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_redir	*alloc_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	return (redir);
}

void	attach_redir(t_cmd *cmd, t_redir *redir, t_cmd_table *table)
{
	t_redir	*aux;

	aux = ft_calloc(1, sizeof(t_redir));
	aux->direction = ft_strdup(redir->direction);
	aux->type = redir->type;
	ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
	ft_lstadd_back(&table->redirs, ft_lstnew(aux));
}

/// @brief Esta funcion devuelve la direccion de la redireccion
/// @param tok el token siguiente al que esta trabajando
/// @return char * de la direccion
char	*get_direction(t_tok *tok)
{
	char	*ret;

	if (!tok)
		return (NULL);
	if (tok->type != COMMAND && tok->type != STRING)
		return (NULL);
	ret = ft_strdup(tok->value);
	return (ret);
}

/// @brief Da el tamaño del redir
/// @param value el string del redir
/// @return cuantos '<' o '>' tiene el redir
int	size_redir(char *value)
{
	int		i;
	char	redir;

	i = 0;
	redir = '\0';
	while (value[i])
	{
		if (!redir && (value[i] == '<' || value[i] == '>'))
		{
			if (value[i] == '<')
				redir = value[i];
			else if (value[i] == '>')
				redir = value[i];
		}
		i++;
	}
	if (count_char(value, '<') && count_char(value, '>'))
		return (-1);
	return (count_char(value, redir));
}
