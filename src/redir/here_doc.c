/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:21:37 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/08 19:39:14 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_heredoc;

char	*ft_new_limit(char *limit, t_cmd_table *table)
{
	size_t	limit_len;
	char	*new_limit;

	limit_len = ft_strlen(limit);
	new_limit = malloc(limit_len + 2);
	if (!new_limit)
	{
		table->error_code = MEM_ALLOC_ERROR;
		error_handler(table->error_code);
	}
	ft_strlcpy(new_limit, limit, limit_len + 1);
	new_limit[limit_len] = '\n';
	new_limit[limit_len + 1] = '\0';
	return (new_limit);
}

void	write_here_doc(char *limit, t_cmd_table *table)
{
	int		read_bytes;
	int		infile;
	char	buf[1024];
	char	*new_limit;

	infile = open(TMP_FILE, O_RDWR | O_CREAT | O_TRUNC, 0777);
	check_error(infile, CHECK_OPEN, table);
	new_limit = ft_new_limit(limit, table);
	while (1)
	{
		write(1, "> ", 2);
		read_bytes = read(STDIN_FILENO, buf, 1024);
		if (read_bytes == 0)
			break ;
		else if (read_bytes < 0 && !g_heredoc)
			check_error(close(infile), CHECK_CLOSE, table);
		if (g_heredoc == 1 || (ft_strncmp(new_limit, buf, read_bytes) == 0))
			break ;
		write(infile, buf, read_bytes);
	}
	check_error(close(infile), CHECK_CLOSE, table);
}

int	open_here_doc(t_cmd_table *table)
{
	int	infile;

	infile = open(TMP_FILE, O_RDONLY);
	check_error(infile, CHECK_OPEN, table);
	return (infile);
}

int	manage_here_doc(t_redir redir, t_cmd_table *table)
{
	char	*limit;
	int		value;

	limit = redir.direction;
	g_heredoc = 0;
	write_here_doc(limit, table);
	table->red_fd[READ_E] = open_here_doc(table);
	value = dup2(table->red_fd[READ_E], STDIN_FILENO);
	check_error(value, CHECK_DUP, table);
	return (table->red_fd[READ_E]);
}

bool	is_heredoc(t_list *list)
{
	t_redir	*redir;

	if (list != NULL)
	{
		redir = (t_redir *)list->content;
		if (redir->type == RD_HD)
			return (true);
	}
	return (false);
}
