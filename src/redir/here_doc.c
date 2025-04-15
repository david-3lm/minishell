/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlopez-l <dlopez-l@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:21:37 by cde-migu          #+#    #+#             */
/*   Updated: 2025/04/15 18:50:36 by dlopez-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int g_heredoc;

char	*ft_new_limit(char *limit)
{
	size_t	limit_len;
	char	*new_limit;

	limit_len = ft_strlen(limit);
	new_limit = malloc(limit_len + 2);
	ft_strlcpy(new_limit, limit, limit_len + 1);
	new_limit[limit_len] = '\n';
	new_limit[limit_len + 1] = '\0';
	return (new_limit);
}

int	write_here_doc(char *limit)
{
	int		read_bytes;
	int		infile;
	char	buf[1024];
	char	*new_limit;

	infile = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	new_limit = ft_new_limit(limit);
	while (1)
	{
		write(1, "> ", 2);
		read_bytes = read(STDIN_FILENO, buf, 1024);
		if (read_bytes == 0)
			break ;
		else if (read_bytes < 0 && !g_heredoc)
		{
			close(infile);
			printf("SALGOOO \n");
			return (1);
		}
		if (g_heredoc == 1 || (ft_strncmp(new_limit, buf, read_bytes) == 0 ))
			break ;
		write(infile, buf, read_bytes);
	}
	close(infile);
	return (0);
}

void	create_here_doc(char *limit)
{
	if (write_here_doc(limit))
	{
		perror("Error creating tmp file");
		exit(EXIT_FAILURE);
	}
}

int	open_here_doc(void)
{
	int	infile;

	infile = open(TMP_FILE, O_RDONLY);
	if (infile < 0)
	{
		perror("open here_doc");
		exit(EXIT_FAILURE);
	}
	return (infile);
}

int	manage_here_doc(t_redir redir, t_cmd_table *table)
{
	char	*limit;

	limit = redir.direction;
	g_heredoc = 0;
	create_here_doc(limit);
	table->red_files[READ_E] = open_here_doc();
	dup2(table->red_files[READ_E], STDIN_FILENO);
	// close(infile);
	return (table->red_files[READ_E]);
}

bool	is_heredoc(t_list *redir_lst)
{
	t_redir *redir;
	t_list	*copy;
	
	copy = redir_lst;
	while (copy != NULL)
	{
		redir = (t_redir *)copy->content;
		if (redir->type == RD_HD)
			return (true);
		copy = copy->next;
	}
	return (false);
}
