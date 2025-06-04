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

t_env	*mini_get_env(t_cmd_table *table, char *var);
int	bi_env(t_cmd_table *table, t_cmd *cmd);
int	bi_karol(t_cmd_table *table, t_cmd *cmd);
int	bi_moon(t_cmd_table *table, t_cmd *cmd);
int	bi_pwd(t_cmd_table *table, t_cmd *cmd);
int	bi_star(t_cmd_table *table, t_cmd *cmd);
void	del_env(void *value);
int	bi_unset(t_cmd_table *table, t_cmd *cmd);
int	export_manage_inter(t_env *env, t_cmd_table *table);
void	manage_empty_export(t_cmd_table *table);
int	bi_weather(t_cmd_table *table, t_cmd *cmd);
void	ft_change_env(t_cmd_table *table, char *key, char *path, bool is_path);
int	cd_home(t_cmd_table *table);
int	ft_change_path(t_cmd_table *table, char *arg);
int	bi_cd(t_cmd_table *table, t_cmd *cmd);
void	print_lines(t_list *tok, int out, bool n_opt);
bool	is_n_option(char *str);
t_list	*check_n_flag(t_list *next, bool *n_opt);
int	bi_echo(t_cmd_table *table, t_cmd *cmd);
bool	ft_is_strnum(char *str);
int	ft_get_exit_code(t_cmd *cmd);
int	bi_exit(t_cmd_table *table, t_cmd *cmd);
void	purge_equal(char *str, t_env **env);
bool	token_exists(t_list *env_list, char *str);
void	change_token(t_list *env_list, t_env *env);
int	manage_correct_export(t_cmd_table *table, t_cmd *cmd, t_env *env);
int	bi_export(t_cmd_table *table, t_cmd *cmd);
void	quita_owo(int sig);
int	bi_owo(t_cmd_table *table, t_cmd *cmd);
void	quita_uwu(int sig);
int	bi_uwu(t_cmd_table *table, t_cmd *cmd);
int	get_builtin_idx(char *str, void *builtins[][2]);
void	handle_signal(int signal);
void	handle_interact(int signal);
void	review_token(t_cmd_table *table);
int	executor(t_cmd_table *table);
int	is_input_valid(const char *input);
char	*get_token(const char *input, int *curr_pos);
t_redir	*get_redir(const char *input, int *curr_pos);
t_cmd	*get_cmds(const char *input, int *curr_pos);
t_cmd_table	*get_cmd_table(const char *input, int *curr_pos);
t_list	*ft_make_env(char *str);
t_env	*ft_create_env(char *key, char *value);
void	generate_env(t_list **list, char *shlvl);
t_list	*env_init(char **orig_envp, char *shlvl);
char	*ft_new_limit(char *limit, t_cmd_table *table);
void	write_here_doc(char *limit, t_cmd_table *table);
int	open_here_doc(t_cmd_table *table);
int	manage_here_doc(t_redir *redir, t_cmd_table *table);
bool	is_heredoc(t_list *list);
void	set_redir(t_cmd *cmd, t_list *new_n, const char *input, int *curr_pos);
void	set_redir_type(t_redir *redir, const char *input, int curr_pos);
int	ft_init_pipes(t_cmd_table *table);
void	set_redir_pipes(t_list *redirs, t_cmd_table *table, int index);
void	close_all_pipes(t_cmd_table *table);
void	free_pipes(int **pipes);
bool	ft_check_redirs(t_cmd *cmd);
bool	is_redirs(t_list *redirs, t_redir_type type);
int	open_file(t_redir *redir, int prev_fd, int flags, mode_t permissions);
int	open_all_files(t_list *redirs, t_cmd_table *table);
void	close_red_fd(int files[2]);
t_redir	*alloc_redir(void);
void	attach_redir(t_cmd *cmd, t_redir *redir, t_cmd_table *table);
char	*get_direction(t_tok *tok);
int	size_redir(char *value);
t_tok_type	get_token_type(t_list *cmd);
bool	is_command(t_cmd cmd);
bool	is_str(t_cmd cmd);
bool	is_redir(t_cmd cmd);
t_tok_type	get_ttype(char *tok);
bool	is_quote(char c);
bool	is_separator(char c);
int	count_quotes(char *str);
int	count_char(char *str, char c);
int	is_cmd_delimiter(char c);
int	is_token_delimiter(char c);
void	skip_quotes(const char *input, int *curr_pos);
void	skip_spaces(const char *input, int *curr_pos);
void	delete_quotes(char *token);
void	concat(char *dest, char **strs);
char	*ft_strstr_quotes(char *str, char *to_find);
int	is_input_valid_unexpected_token(const char *input, char *err_message);
int	is_input_valid_not_supported(const char *input, char *err_message);
void	free_arr(void **ptr);
int	ft_strisspace(char *str);
size_t	get_length(char **strs);
char	*ft_strtrim_all(const char *s1, const char *set);
char	*ft_strncat(char *dest, char *src, unsigned int nb);
int	has_char_at_beginning(const char *input, char c, char *err_message);
int	has_char_at_end(const char *input, char c, char *err_message);
int	has_spaces_between_char(const char *input, char c, char *err_message);
void	free_token_list(t_list *tokens);
void	free_redir_list(t_list *lst);
void	free_cmd_list(t_list *lst);
void	free_env(t_list *lst);
void	free_cmd_table(t_cmd_table *table);
int	ft_strnstr_iterator(char *haystack, char *needle, size_t len);
void	skip_letters(const char *input, int *curr_pos);
char	*replace_midstring(char *original, char *old_substr, char *new_substr, int replace_i);
char	*get_var_name(char *str);
void	error_handler(int code);
void	check_error(int value, int to_check, t_cmd_table *table);
void	ft_lstdel_first(t_list **lst, void (*del)(void*));
void	ft_lstclear_if(t_list **lst, int (*cmp)(void *), void (*del)(void *));
void	ft_lstdel_safe(void *content);
int	unset_error(t_cmd_table *table);
void	ft_wrong_access_error(t_cmd_table *table, char *cmd, int code);
void	ft_error_str(t_cmd_table *table, char *str);
void	ft_error_export(t_cmd_table *table, char *str);
void	replace_status_env(char **str, int last_status);
void	replace_vars_with_values(char **str, t_cmd_table *table);
void	replace_one_var(char **str, t_cmd_table *table);
void	replace_env_single_token(char **token, t_cmd_table *table);
void	replace_envs(t_list **tokens, t_list *redirs, t_cmd_table *table);
bool	is_kntxesi(t_cmd cmd);
bool	is_inside_kntxesi(int argc, char **argv);
char	*ft_getenv_value(t_cmd_table *table, char *str);
int	execute_kntxesi(t_cmd_table *table);
int	has_forbidden_sequence(const char *input, char *test, char *err_message);
int	has_non_supported(const char *input, char *test, char *err_message);
int	has_non_supported_one(const char *input, char *test, char *err_message);
int	has_quotes_open(const char *input, char *err_message);
int	get_new_token_size(t_list *split_token);
char	*join_split_token(t_list *split_token);
int	is_token_empty(void *content);
t_list	*get_split_token(char *token);
void	save_original_fd(t_cmd_table *table);
void	restore_and_close_fds(t_cmd_table *table);
int	try_fullpath(char *path, char **full_cmd, char *const *envp, t_cmd_table *table);
int	last_command_exec(t_cmd *cmd, t_cmd_table *table);
int	command_exec(t_cmd *cmd, t_cmd_table *table, int i);
char	*get_value(void *token);
char	**get_cmd(t_list *origin);
char	**get_paths(t_cmd_table *table, char *cmd);
void	path_exec(t_cmd *cmd, t_cmd_table *table);
void	free_all(char **arr);
int	handle_command(t_cmd *cmd, t_cmd_table *table,  int *cmd_index);
int	ft_wait_table(t_list **pids);
int	table_executor(t_cmd_table *table);
void	debug_parser(t_cmd_table *table);
void	print_tokens(t_list *tokens);
void	print_redirs(t_list *redirs);
void	debug_table(t_cmd_table *table);
int	main(int argc, char **argv, char **envp);
int	(*builtin_arr(char *str))(t_cmd_table *table, t_cmd *cmd);
#endif
