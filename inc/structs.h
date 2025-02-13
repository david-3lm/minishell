/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 12:16:00 by dlopez-l          #+#    #+#             */
/*   Updated: 2025/02/12 11:46:43 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include "../libimp/libft.h"

/* Enum to get he type of the tokens*/
typedef enum tok_type
{
	COMMAND = 0,
	STRING = 1,
	FILES = 2,
	REDIR = 3,
	PIPE = 4,
	VARIABLE = 5
}	t_tok_type;

/*
	STDOUT = >,
	STDOUT2 = >>,
	STDIN = <,
	HEREDOC = <<
*/

typedef enum redir_type
{
	STDOUT = 0,
	STDOUT2 = 1,
	STDIN = 2,
	HEREDOC = 3,
	BADREDIR = 4
}	t_redir_type;

//this .h inspired from https://github.com/DimitriDaSilva/42_minishell

/*
struct used to save a list of the tokens that the lexer calculates
tokens: list of tokens (s_tok *)
 */
typedef struct s_token_list
{
	t_list	*tokens;
}			t_token_list;
/*
token structure to save its type and its value
type: (enum) {COMMAND, STRING, FILES, REDIR, PIPE, VARIABLE}
*/
typedef struct s_tok
{
	t_tok_type	type;
	char		*value;
}				t_tok;

/*
A command table
@fields:
cmds: list of commands (t_cmd *) is the nodes
delimiter: indicates what separates this table with the next
	- NULL: this is the last
	- ";": consecutive execution of the next
	- "||" or "&&" Bonus part
n_cmd: number of comands in cmds
pipes: 2D array of ints, each subarray is a pipe
pids: works as a queue if the pids of the childs
return_val: the return value of each cmd table
*/
typedef struct s_cmd_table
{
	t_list	*cmds;
	char	*delimeter;
	int		n_cmd;
	int		**pipes;
	int		n_pipes;
	t_list	*pids;
	int		return_val;

	// ESTO LO HA TOCADO CAROL
	int		std_backup[2];
	int		pipe_fd[2];
}			t_cmd_table;

/*
tokens: splits the tokens of the command (t_tok *)
redirs: linked list of all redirections (t_redir *) targeting this simple command
*/
typedef struct s_cmd
{
	t_list	*tokens;
	t_list	*redirs;
}			t_cmd;

/*

direction: name of file and delimiter encolsing token
type:
	- ">" stdout
	- ">>" stdout
 	- "<" stdin
*/

typedef struct s_redir
{
	char			*direction;
	t_redir_type	type;
}			t_redir;

/*ERROR CODES*/
typedef enum e_error_code
{
	NO_ERROR = 0,
	MEM_ALLOC_ERROR,
	NULL_POINTER_ERROR,
	UNEXPECTED_EOF,
	SYNTAX_ERROR,
	UNKNOWN_ERROR
}	t_error_code;

#endif