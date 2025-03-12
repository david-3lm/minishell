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

void	debug(t_token_list *list);
int	main(void);
t_tok_type	get_ttype(char *tok);
int	count_quotes(char *str);
void	add_token(t_token_list *list, char *value);
t_tok_type	get_next_type(t_list *cmd);
t_tok_type get_token_type(t_list *cmd);
bool	is_command(t_cmd cmd);
bool	is_pipe(t_cmd cmd);
bool	is_redir(t_cmd cmd);
t_tok_type	get_ttype(char *tok);
int	count_quotes(char *str);
void	add_token(t_token_list *list, char *value);
char	*get_value(void *token);
char	**get_cmd(t_list *origin);
char	**get_paths();
void	path_exec(t_cmd *cmd);
void	free_all(char **arr);
void	ft_usage(void);
int	last_command_exec(t_cmd *cmd);
t_error_code	run_pipex(t_cmd_table *table, t_cmd *cmd, int cmd_index);
t_error_code	recorrer_table(t_cmd_table *table);
char	*ft_new_limit(char *limit);
int	ft_write_here_doc(char *limit);
void	create_here_doc(char *limit);
int	ft_open_here_doc(void);
void	here_doc(char *limit, int argc);
bool	is_heredoc(t_list *redir_lst);
int	ft_error(char *str);
void	save_original_fd(int fd[2]);
void	restore_fds(int fd[2]);
int	pipex_proccess(t_cmd *cmd, t_cmd_table *table);
int	last_command_exec(t_cmd *cmd);
t_error_code	run_pipex(t_cmd_table *table, t_cmd *cmd, int cmd_index);
t_error_code	recorrer_table(t_cmd_table *table);
int	manage_redir_in(t_cmd_table *table, t_redir in_redir);
int	manage_redir_out(t_cmd_table *table, t_redir out_redir);
t_redir	*get_redir_in(t_list *list);
t_redir	*get_redir_out(t_list *list);
void	close_red_files(int files[2]);
void	debug(t_token_list *list);
int	main(void);
#endif
