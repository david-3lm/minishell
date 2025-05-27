/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 23:36:35 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/05/22 15:18:31 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H
//PA DEFINIR MACROS Y ESAS COSAS WAPAS
# define RED     "\033[1;31m"
# define GREEN   "\033[1;32m"
# define YELLOW  "\033[1;33m"
# define BLUE    "\033[1;34m"
# define MAGENTA "\033[1;35m"
# define CYAN    "\033[1;36m"
# define RESET   "\033[0m"
# define RESET_COLOR "\033[0m"
# define TMP_FILE "/tmp/shell_temp"
# define IN_REDIR 0
# define OUT_REDIR 1

# define NO_ERROR 0
# define MAIN_ERROR 1
# define UNKNOWN_ERROR 1
# define REDIR_ERROR 2
# define MEM_ALLOC_ERROR 3
# define WRONG_CMD_ERROR 127
# define DUP_ERROR 10
# define FORK_ERROR 11
# define OPEN_ERROR 12
# define CLOSE_ERROR 13
# define EXECVE_ERROR 20
# define PERMISSION_ERROR 126
# define PIPE_ERROR 22
# define EXIT_ERROR 255

// pipex
# define ERROR_E 2
# define WRITE_E 1
# define READ_E	 0

# define SPACE ' '

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define R_BYTES 1

# define EXIT_DEFAULT_O 2
# define EXIT_HEREDOC_O 3

# define CHECK_VALUE -1
# define CHECK_DUP 0
# define CHECK_CLOSE 1
# define CHECK_PIPE 2
# define CHECK_FORK 3
# define CHECK_OPEN 4
# define CHECK_CMD 5
# define CHECK_MEM 6

# define WHITE_SPACE " \t\n\v\f\r"
# define K_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"

# define UWU "⠀⠀⠀⠀⠀⣠⣾⡗⠁⢂⠐⡉⠐⠠⢁⠂⠌⠡⠐⠡⠈⠌⣁⠂⠄⡑⠠⠌⠒⠠⠌⡐⢁⠢⢈⠁⢢⢈⠐⡀⠉⠻⣷⣄⠀⠀⠀⠀⠀⠀\n⠀⠀⠀⢀⣾⡽⠋⡀⠎⠠⠁⢄⣡⡾⠀⠌⢂⠡⢃⠡⢉⡐⠈⠻⣷⣤⣁⣂⣡⠈⠔⡈⠄⠒⡈⠌⣀⠢⢁⠤⢁⠂⠒⢾⢧⡀⠀⠈⠀⠀\n⠀⠀⣠⣿⡟⠁⡐⢠⣨⣤⡷⠿⠋⠠⢁⡘⢀⠢⠄⠂⠅⡠⢁⠂⠄⡈⢉⠉⡉⢁⠂⡐⠌⠡⢐⠂⠄⢂⠄⠢⢐⠈⡐⠈⠡⣳⡀⠀⠀⠀\n⢠⣴⣿⠟⢠⠂⠄⢋⠉⠠⠐⠠⢈⠄⠡⠐⡀⠢⢈⠒⠠⢁⠢⢈⢐⣤⣦⡶⠷⠾⠶⢦⣌⡐⠈⠄⡉⠤⢈⡐⠨⠐⠄⡁⢂⠡⠹⡄⠀⠀\n⣿⢟⡾⠀⠂⠌⡐⠠⠈⠄⡁⠂⠄⡈⠆⣁⠂⡑⠠⢈⢂⡁⢂⣶⣿⣵⣶⣶⡶⠀⠀⠀⠈⠛⢾⣄⠄⠡⠂⠤⢁⡘⢀⠒⠠⢀⠡⠀⠀⠀\n⣿⣾⠃⡈⢐⣠⡶⠷⢛⣷⣺⣷⣤⡐⠈⢄⠒⣈⠁⢂⠤⢘⣵⣿⣿⢿⣿⠏⠀⠀⠀⠀⠀⠀⠀⠉⢷⣆⠡⠌⢠⠐⠂⠌⢒⠠⠀⠀⢣⡄\n⣿⡇⠐⢠⡾⠋⢀⣴⣿⣿⣿⡟⠉⠻⣆⡀⠒⡄⠨⠄⠒⣼⣿⣿⢯⣿⣿⠀⠀⠀⠂⠄⠀⠀⠀⠀⠀⠹⣦⠐⠠⠌⢂⢁⠢⠄⠡⠀⠰⣿\n⢻⡅⢨⡿⠁⢠⣿⣿⣿⡿⣽⣿⠀⠀⠙⣧⠐⠠⠑⡈⣼⣿⣿⣯⣿⣟⣿⣧⡀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠹⣧⠐⡈⠄⢂⠰⢈⠐⡀⡆⡿\n⢻⡄⣿⠁⠀⣼⣿⣿⡿⣽⣿⢿⣷⣄⣀⣹⣇⠠⠑⡄⣿⣿⣿⣾⣯⣿⢯⣿⣿⣿⣷⣿⣿⠄⠀⠀⠀⠀⠀⢹⡇⠠⠈⠄⠂⡄⠡⠀⡇⡇\n⣹⢾⡇⠀⠀⣿⣿⣿⡿⣿⣽⣿⣻⣿⣿⣿⣿⣀⠣⢰⣿⣿⡟⠉⠛⢿⣿⣯⣿⣿⣿⣿⣿⠀⠐⠀⠀⡐⠀⠰⣟⠠⢁⠊⡐⠠⢁⠂⡄⣇\n⣿⡞⡇⠀⠀⢻⣿⣿⠿⠿⣿⣾⣟⣷⣿⣿⡏⣷⢉⡚⣧⢻⣧⡀⠀⣸⣿⣿⣿⣿⣿⣿⠇⠀⠠⠀⡀⢀⠀⢘⣏⠀⢂⡐⢈⠁⢂⠀⠐⣿\n⣿⣧⡷⠀⠀⠈⣿⣧⡀⠀⣼⣿⣿⣿⣿⡿⠁⣿⠢⠉⣿⡀⠻⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀⠀⠁⠀⠀⠀⠀⢸⡇⠈⢄⡐⠠⢊⠀⠀⢸⠷\n⣿⣹⣿⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⠟⠁⠀⣿⠀⠁⠘⣧⠀⠀⠙⠛⠛⠛⠛⠁⣠⣀⠀⠀⠀⠀⠀⠀⢀⣾⠃⠈⡀⠠⢁⠂⢨⣴⡏⠁\n⠉⢿⡽⣆⠀⠀⠀⢀⡶⣯⠉⠛⠉⠀⠀⠀⢰⡏⠀⠌⠐⠘⣧⠀⠀⠀⠀⠀⠀⣾⠉⠉⢷⡄⠀⠀⠀⠀⣾⠁⢄⠣⠌⡑⢠⣸⢟⡞⠀⠀\n⠀⠸⣿⡹⣦⡀⣠⡟⠁⢸⡇⠀⠀⠀⠀⢠⡟⠀⠠⠁⠂⢀⠘⢳⣄⠀⠀⠀⠀⣿⡀⢀⠀⠛⢦⣄⡀⣼⠇⡈⢆⡑⢂⡁⢢⢯⡟⠀⠀⠀\n⠀⠀⣾⣿⣿⠿⠋⢀⠐⣺⣧⣤⠶⠶⠶⠛⠈⠳⣶⠋⠉⠁⠉⠀⠉⠛⠛⠛⠒⠛⠻⠀⠄⢂⠀⠈⠙⠻⣦⡈⠔⡈⠄⣼⣻⡟⠈⠀⠀⠀\n⣬⣿⣻⠏⠁⡀⠤⠀⠄⠀⡀⠀⡀⢀⠀⠄⣐⣠⠿⢦⣄⣂⣈⡀⢁⡠⠀⠄⢂⠐⢀⠈⠠⠀⠌⡐⠠⢀⠈⠻⣦⡘⣛⣽⠋⠀⠀⠀⠀⠀\n⣿⣷⠏⠀⠐⡀⠂⠌⢀⠂⠄⠁⢰⡶⠾⠛⠋uwu⠈⠉⠁⠉⠉⢹⡇⠀⠂⠌⡀⠄⠁⡐⠠⠀⡁⠂⠄⠀⠉⣿⣻⡇⠀⠀⠀⠀⠀⠀\n⣿⡇⠀⠄⠒⡀⢁⠂⠠⢈⠀⠌⣼⡗⠀⠐⠠⠁⡐⠂⠠⠁⡘⠠⠐⠈⢿⡄⠐⠠⢀⠂⠁⡐⠀⡁⠐⠈⡐⠈⢀⢸⣿⡇⠀⠀⠀⠀⠀⠀\n⣼⡅⠀⠌⠐⡀⢂⠀⠡⢀⠂⠀⣽⣿⣶⢤⣆⣐⠀⠀⡁⠠⠀⠄⠁⠠⠘⣧⠈⠐⠠⢀⠁⠄⡐⢀⠁⠂⠄⠁⢀⣾⣻⡇⠀⠀⠀⠀⠀⠀\n⣿⣷⡀⠈⠐⡀⢂⠈⠄⠠⠀⢡⣿⣿⠉⠳⠾⢭⣿⣻⣶⣶⡶⠦⡼⠴⢦⣾⣄⠉⠀⠂⠈⡀⠐⠀⠈⠠⣐⣨⣾⣻⠏⠀⠀⠀⠀⠀⠀⠀\n"

extern int	g_heredoc;

#endif