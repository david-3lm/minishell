/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 12:49:42 by cde-migu          #+#    #+#             */
/*   Updated: 2024/12/19 15:08:23 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <fcntl.h>
# include <sys/wait.h>

# define ERROR_E 2
# define WRITE_E 1
# define READ_E	 0

# define SPACE ' '

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define R_BYTES 1

# define EXIT_DEFAULT_O 2
# define EXIT_HEREDOC_O 3

typedef struct s_files
{
	int	infile;
	int	outfile;
}	t_files;

#endif