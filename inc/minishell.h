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
void	purge_input(t_token_list *list, const char *str);
t_error_code	lexer(char *input);
void	debug_parser(t_cmd_table *table);
char	*get_direction(t_tok *tok);
t_cmd	*add_redir(t_list *tok_list);
void	add_cmds(t_token_list *tok, t_cmd_table **table);
void	count_pipes(t_cmd_table *table);
t_error_code	parser(t_token_list *list);
void prueba_test(void);
int	last_command_exec(t_cmd *cmd);
t_error_code	pipe_manager(t_cmd_table *table);
t_error_code	executor(t_cmd_table *table);
t_tok_type	get_ttype(char *tok);
void	add_token(t_token_list *list, char *value);
t_tok_type	get_next_type(t_list *cmd);
t_tok_type get_token_type(t_list *cmd);
bool	is_command(t_cmd cmd);
bool	is_pipe(t_cmd cmd);
void	debug(t_token_list *list);
int	main(void);
char	*ft_new_limit(char *limit);
int	ft_write_here_doc(char *limit);
void	create_here_doc(char *limit);
int	ft_open_here_doc(void);
void	here_doc(char *limit, int argc);
char	*get_value(void *token);
char	**get_cmd(t_list *origin);
char	**get_paths();
void	path_exec(t_cmd *cmd);
void	free_all(char **arr);
void	ft_usage(void);
int	ft_error(char *str);
int	pipex_proccess(t_cmd *cmd);
#endif
