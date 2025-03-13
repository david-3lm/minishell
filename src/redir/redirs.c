/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 10:52:37 by cde-migu          #+#    #+#             */
/*   Updated: 2025/03/13 14:48:10 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	manage_redir_in(t_cmd_table *table, t_redir in_redir)
{
	if (in_redir.type == RD_SIN)
	{
		table->red_files[READ_E] = open(in_redir.direction, O_RDONLY);
		if (table->red_files[READ_E] == -1)
			perror("open infile");
		else
			dup2(table->red_files[READ_E], STDIN_FILENO);
		printf(PINK "el infile se ha abierto en --> %i %s \n", table->red_files[READ_E], RESET_COLOR);
		// aqui abro el red files pero lo estoy cerrando luego en algun sitio?
	}
	else if (in_redir.type == RD_HD)
		table->red_files[READ_E] = manage_here_doc(in_redir, table);
	return (table->red_files[READ_E]);
}

int	manage_redir_out(t_cmd_table *table, t_redir out_redir)
{
	if (out_redir.type == RD_SOUT)
		table->red_files[WRITE_E] = open(out_redir.direction, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (out_redir.type == RD_SOUT2)
		table->red_files[WRITE_E] = open(out_redir.direction, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (table->red_files[WRITE_E] == -1)
		perror("open outfile");
	else
		dup2(table->red_files[WRITE_E], STDOUT_FILENO);
	printf(PINK "el outfile se ha abierto en --> %i %s \n", table->red_files[WRITE_E], RESET_COLOR);
	return (table->red_files[WRITE_E]);
}

t_redir	*get_redir_in(t_list *list)
{
	t_list	*lst_copy;
	t_redir	*redir;
	
	redir = NULL;
	if (ft_lstsize(list) != 0)
	{
		lst_copy = list;
		while (lst_copy != NULL)
		{
			redir = (t_redir *)lst_copy->content;
			if (redir->type == RD_SIN || redir->type == RD_HD)
			{
				printf("redirection type ==> %i \n", redir->type);
				return (redir);
			}
			lst_copy = lst_copy->next;
		}
	}
	return (NULL);
}

t_redir	*get_redir_out(t_list *list)
{
	t_list	*lst_copy;
	t_redir	*redir;
	
	redir = NULL;
	if (ft_lstsize(list) != 0)
	{
		lst_copy = list;
		while (lst_copy != NULL)
		{
			redir = (t_redir *)lst_copy->content;
			printf(PINK "EN OUT lst copy ---> %s %s \n", redir->direction, RESET_COLOR);
			if (redir->type == RD_SOUT || redir->type == RD_SOUT2)
				return (redir);
			lst_copy = lst_copy->next;
		}
	}
	return (NULL);
}

void	close_red_files(int files[2])
{
	int	i;

	i = 0;
	while (i < 2)
	{
		if (files[i] != 0)
		{
			close(files[i]);
			printf(PINK "he cerrado el file con fd %i %s \n \n", files[i], RESET_COLOR);
		}
		i++;
	}
}

/* t_redir	*get_redir(t_list *redir_list)
{
	t_redir *redir;
	int		num_redir;
	
	num_redir =  ft_lstsize(redir);
	
} */