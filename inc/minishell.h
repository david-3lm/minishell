#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libimp/libft.h"
# include "./structs.h"
# include "./defines.h"
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
# include <fcntl.h>
# include <sys/wait.h>

void	print_lines(t_list *tok, int out, bool n_opt);
bool	is_n_option(char *str);
t_list	*check_n_flag(t_list *next, bool *n_opt);
int	bi_echo(t_cmd_table *table, t_cmd *cmd);
int	bi_unset(t_cmd_table *table, t_cmd *cmd);
int	bi_pwd(t_cmd_table *table, t_cmd *cmd);
int	cd_home(t_cmd_table *table);
int	bi_cd(t_cmd_table *table, t_cmd *cmd);
void	ft_change_old_pwd(t_cmd_table *table);
int	ft_change_path(t_cmd_table *table, char *arg);
void	purge_equal(char *str, t_env **env);
bool	token_exists(t_list *env_list, char *str);
void	change_token(t_list *env_list, t_env *env);
void	manage_empty_export(t_cmd_table *table);
int	bi_export(t_cmd_table *table, t_cmd *cmd);
int	bi_weather(t_cmd_table *table, t_cmd *cmd);
int	bi_star(t_cmd_table *table, t_cmd *cmd);
int	bi_karol(t_cmd_table *table, t_cmd *cmd);
bool	ft_is_strnum(char *str);
int	ft_get_exit_code(t_cmd *cmd);
int	bi_exit(t_cmd_table *table, t_cmd *cmd);
int	bi_env(t_cmd_table *table, t_cmd *cmd);
t_env	*mini_get_env(t_cmd_table *table, char *var);
void	debug_parser(t_cmd_table *table);
int	main(int argc, char **argv, char **envp);
void	error_handler(int code);
void	check_error(int value, int to_check, t_cmd_table *table);
bool	need_new_cmd(t_cmd *current_cmd, int tok_type);
t_cmd	*create_or_redir_cmd(t_list *current_token, t_cmd_table **table);
void	attach_cmd_to_table(t_cmd *cmd, t_cmd_table **table);
t_tok	*copy_and_expand(t_tok *orig, t_cmd_table *table);
bool	process_token(t_cmd **current_cmd, t_list *curr_t, t_cmd_table **table);
void	add_token(t_token_list *list, char *value);
void	update_quote_state(char c, bool *in_quote, char *quote_char);
void	handle_token_segment(char *line, t_token_list *list, int *start, int i);
void	handle_last_token(char *line, t_token_list *list, int start, int end);
t_tok_type	get_ttype(char *tok);
bool	is_quote(char c);
bool	is_separator(char c);
int	count_quotes(char *str);
int	count_char(char *str, char c);
char	*get_env_value(char *var_name, t_list *env_lst);
char	*expand_variable(char *token, int *i, t_cmd_table *table);
char	*append_plain_text(char *token, int *i);
char	*check_expansion(char *token, t_cmd_table *table, t_tok *tok);
t_redir	*alloc_redir(void);
void	attach_redir(t_cmd *cmd, t_redir *redir, t_cmd_table *table);
char	*get_direction(t_tok *tok);
int	size_redir(char *value);
t_tok_type	get_token_type(t_list *cmd);
bool	is_command(t_cmd cmd);
bool	is_str(t_cmd cmd);
bool	is_pipe(t_cmd cmd);
bool	is_redir(t_cmd cmd);
int	executor(t_cmd_table *table);
void	handle_signal(int signal);
void	handle_interact(int signal);
char	*ft_strjoin_free(char *s1, char *s2);
void	add_cmds(t_token_list *tok, t_cmd_table **table);
void	count_pipes(t_cmd_table *table);
void	clean_table(t_cmd_table *table);
t_error_code	parser(t_token_list *list, t_list *envl);
int	quotes_are_closed(const char *input);
void	purge_input(t_token_list *list, const char *str);
void	lexer_split(char *line, t_token_list *list);
t_error_code	lexer(char *input, t_list *envl);
void	save_original_fd(t_cmd_table *table);
void	restore_and_close_fds(t_cmd_table *table);
int	pipex_proccess(t_cmd *cmd, t_cmd_table *table);
int	try_fullpath(char *path, char **full_cmd, char * const *envp);
char	*get_value(void *token);
char	**get_cmd(t_list *origin);
char	**get_paths(void);
void	path_exec(t_cmd *cmd, t_cmd_table *table);
void	free_all(char **arr);
int	last_command_exec(t_cmd *cmd, t_cmd_table *table);
void	redir_manager(t_cmd_table *table, int type);
int	handle_command(t_cmd *cmd, t_cmd_table *table, int *cmd_index);
int	execute_cmd_table(t_cmd_table *table);
t_list	*get_env(char *str);
t_list	*env_init(char **orig_envp);
int	manage_redir_in(t_cmd_table *table, t_redir in_redir);
int	manage_redir_out(t_cmd_table *table, t_redir out_redir);
t_redir	*get_redir_in(t_list *list);
t_redir	*get_redir_out(t_list *list);
void	close_red_files(int files[2]);
t_cmd	*alloc_cmd(void);
bool	set_redir_type(t_redir *redir, const char *val, t_cmd_table *table);
bool	set_redir_direction(t_redir *red, t_list *tok_l, t_cmd_table *table);
t_cmd	*add_redir(t_list *tok_list, t_cmd_table **table);
char	*ft_new_limit(char *limit, t_cmd_table *table);
void	write_here_doc(char *limit, t_cmd_table *table);
int	open_here_doc(t_cmd_table *table);
int	manage_here_doc(t_redir redir, t_cmd_table *table);
bool	is_heredoc(t_list *redir_lst);
int	(*builtin_arr(char *str))(t_cmd_table *table, t_cmd *cmd);
#endif
