#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libimp/libft.h"
# include "./structs.h"
# include "./defines.h"
# include "./pipex.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <termios.h>
# include <curses.h>
# include <unistd.h>
# include <string.h>
# include <dirent.h>
# include <stdio.h>
# include <term.h>
# include <signal.h>

void	handle_signal(int signal, siginfo_t *info, void *ctx);
void prueba_test(void);
bool	is_command(t_cmd cmd);
int	command_exec(t_cmd *cmd);
t_error_code	executor(t_cmd_table *table);
void	purge_input(t_token_list *list, const char *str);
t_error_code	lexer(char *input);
void	debug_parser(t_cmd_table *table);
void	add_cmds(t_token_list *tok, t_cmd_table **table);
t_error_code	parser(t_token_list *list);
t_tok_type	get_ttype(char *tok);
void	add_token(t_token_list *list, char *value);
t_tok_type	get_next_type(t_list *cmd);
t_tok_type get_token_type(t_list cmd);
bool	is_command(t_cmd cmd);
bool	is_pipe(t_cmd cmd);
void	debug(t_token_list *list);
int	main(void);
char	*get_value(void *token);
char	**get_cmd(t_list *origin);
char	**get_paths();
void	path_exec(t_cmd *cmd);
void	free_all(char **arr);
void	ft_usage(void);
char	*ft_new_limit(char *limit);
int	ft_write_here_doc(char *limit);
void	create_here_doc(char *limit);
int	ft_open_here_doc(void);
void	here_doc(char *limit, int argc);
int	pipex(char **argv, int argc);
bool	is_pipe_ok(t_list *current);
int	pipex(t_cmd_table *table);
int	ft_error(char *str);
int	pipex_proccess(char *argv);
int	last_child(char **argv, int argc);
#endif
