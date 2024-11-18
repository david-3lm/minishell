#ifndef STRUCTS_H
# define STRUCTS_H
# include "../libimp/libft.h"


//this .h inspired from https://github.com/DimitriDaSilva/42_minishell

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
	t_list	*pids;
	int		return_val;
}			t_cmd_table;

/*
tokens: splits the tokens of the command
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
	char	*direction;
	char	type[2];
}			t_redir;


#endif