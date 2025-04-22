/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:36:35 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/04/22 14:37:54 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
//PA DEFINIR MACROS Y ESAS COSAS WAPAS
# define PINK "\e[0;35m"
# define RESET_COLOR "\033[0m"
# define TMP_FILE "/tmp/shell_temp"
# define IN_REDIR 0
# define OUT_REDIR 1

# define NO_ERROR 0
# define MAIN_ERROR 1
# define MEM_ALLOC_ERROR 2
# define WRONG_CMD_ERROR 3
# define DUP_ERROR 10
# define FORK_ERROR 11
# define OPEN_ERROR 12
# define CLOSE_ERROR 13
# define EXECVE_ERROR 20
# define PATH_ERROR 21
# define PIPE_ERROR 22
# define UNKNOWN_ERROR ;
# define EXIT_ERROR 255

extern int g_heredoc;

#endif