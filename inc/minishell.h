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

int	cd_home(t_cmd_table *table);
int	bi_cd(t_cmd_table *table, t_cmd *cmd);
void	ft_change_old_pwd(t_cmd_table *table);
int	ft_change_path(t_cmd_table *table, char *arg);
void	print_lines(t_list *tok, int out);
int	bi_echo(t_cmd_table *table, t_cmd *cmd);
int	bi_env(t_cmd_table *table, t_cmd *cmd);
t_env	*mini_get_env(t_cmd_table *table, char *var);
bool ft_is_strnum(char *str);
int	ft_get_exit_code(t_cmd *cmd);
int	bi_exit(t_cmd_table *table, t_cmd *cmd);
void	purge_equal(char *str, t_env **env);
bool	token_exists(t_list *env_list, char *str);
void	change_token(t_list *env_list, t_env *env);
void	manage_empty_export(t_cmd_table *table);
int    bi_export(t_cmd_table *table, t_cmd *cmd);
int	bi_pwd(t_cmd_table *table, t_cmd *cmd);
int	bi_unset(t_cmd_table *table, t_cmd *cmd);
void	handle_signal(int signal, siginfo_t *info, void *ctx);
void	purge_input(t_token_list *list, const char *str);
t_error_code	lexer(char *input, t_list *envl);
void debug_pink(char *str);
int	executor(t_cmd_table *table);
void	debug_parser(t_cmd_table *table);
char	*get_direction(t_tok *tok);
int		size_redir(char *value);
t_cmd	*add_redir(t_list *tok_list, t_cmd_table **table);
char	*check_expansion(char *token, t_cmd_table *table, t_tok *tok);
void	add_cmds(t_token_list *tok, t_cmd_table **table);
void	count_pipes(t_cmd_table *table);
t_error_code	parser(t_token_list *list, t_list *envl);
void	debug_env(t_list *env);
t_list	*get_env(char *str);
t_list	*env_init(char **orig_envp);
char	*get_value(void *token);
char	**get_cmd(t_list *origin);
char	**get_paths();
void	path_exec(t_cmd *cmd);
void	free_all(char **arr);
void	ft_usage(void);
int	last_command_exec(t_cmd *cmd);
t_error_code	run_pipex(t_cmd_table *table, t_cmd *cmd, int cmd_index);
t_error_code	redir_manager(t_cmd_table *table, int type);
void	handle_command(t_cmd *cmd, t_cmd_table *table, int *cmd_index, t_error_code *res);
t_error_code	execute_cmd_table(t_cmd_table *table);
int	ft_error(char *str);
void	save_original_fd(t_cmd_table *table);
void	restore_and_close_fds(t_cmd_table *table);
int	pipex_proccess(t_cmd *cmd, t_cmd_table *table);
char	*ft_new_limit(char *limit);
int	write_here_doc(char *limit);
void	create_here_doc(char *limit);
int	open_here_doc(void);
int	manage_here_doc(t_redir redir, t_cmd_table *table);
bool	is_heredoc(t_list *redir_lst);
int	manage_redir_in(t_cmd_table *table, t_redir in_redir);
int	manage_redir_out(t_cmd_table *table, t_redir out_redir);
t_redir	*get_redir_in(t_list *list);
t_redir	*get_redir_out(t_list *list);
void	close_red_files(int files[2]);
t_tok_type	get_next_type(t_list *cmd);
t_tok_type get_token_type(t_list *cmd);
bool	is_command(t_cmd cmd);
bool	is_pipe(t_cmd cmd);
bool	is_redir(t_cmd cmd);
t_tok_type	get_ttype(char *tok);
int	count_quotes(char *str);
void	add_token(t_token_list *list, char *value);
void error_handler(t_cmd_table *table);
void	debug(t_token_list *list);
int	main(int argc, char **argv, char **envp);
int	(*builtin_arr(char *str))(t_cmd_table *table, t_cmd *cmd);
#endif
