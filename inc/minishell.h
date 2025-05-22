/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cde-migu <cde-migu@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:02:42 by cde-migu          #+#    #+#             */
/*   Updated: 2025/05/22 15:31:41 by cde-migu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				ft_get_exit_code(t_cmd *cmd);
int				ft_change_path(t_cmd_table *table, char *arg);
int				cd_home(t_cmd_table *table);
int				bi_exit(t_cmd_table *table, t_cmd *cmd);
int				bi_moon(t_cmd_table *table, t_cmd *cmd);
int				bi_karol(t_cmd_table *table, t_cmd *cmd);
int				bi_star(t_cmd_table *table, t_cmd *cmd);
int				bi_weather(t_cmd_table *table, t_cmd *cmd);
int				bi_echo(t_cmd_table *table, t_cmd *cmd);
int				bi_cd(t_cmd_table *table, t_cmd *cmd);
int				bi_env(t_cmd_table *table, t_cmd *cmd);
int				bi_export(t_cmd_table *table, t_cmd *cmd);
int				bi_pwd(t_cmd_table *table, t_cmd *cmd);
int				bi_unset(t_cmd_table *table, t_cmd *cmd);
int				bi_uwu(t_cmd_table *table, t_cmd *cmd);
int				executor(t_cmd_table *table);
int				quotes_are_closed(const char *input);
int				pipex_proccess(t_cmd *cmd, t_cmd_table *table);
int				try_fullpath(char *path, \
				char **full_cmd, char *const *envp, t_cmd_table *s_cmd_table);
int				last_command_exec(t_cmd *cmd, t_cmd_table *table);
int				handle_command(t_cmd *cmd, t_cmd_table *table, int *cmd_index);
int				ft_wait_table(t_cmd_table *table);
int				execute_cmd_table(t_cmd_table *table);
int				open_here_doc(t_cmd_table *table);
int				manage_here_doc(t_redir redir, t_cmd_table *table);
int				count_quotes(char *str);
int				count_char(char *str, char c);
int				size_redir(char *value);
int				(*builtin_arr(char *str))(t_cmd_table *table, t_cmd *cmd);
int				unset_error(t_cmd_table *table);
int				execute_kntxesi(t_cmd_table *table);
int				export_manage_inter(t_env *env, t_cmd_table *table);
bool			is_kntxesi(t_cmd cmd);
bool			ft_is_strnum(char *str);
bool			is_n_option(char *str);
bool			is_heredoc(t_list *list);
bool			set_redir_type(t_redir *redir, \
				const char *val, t_cmd_table *table);
bool			set_redir_direction(t_redir *red, \
				t_list *tok_l, t_cmd_table *table);
bool			process_token(t_cmd **current_cmd, \
				t_list *curr_t, t_cmd_table **table);
bool			need_new_cmd(t_cmd *current_cmd, int tok_type);
bool			is_quote(char c);
bool			is_separator(char c);
bool			is_command(t_cmd cmd);
bool			is_str(t_cmd cmd);
bool			is_pipe(t_cmd cmd);
bool			is_redir(t_cmd cmd);
bool			token_exists(t_list *env_list, char *str);
bool			is_inside_kntxesi(int argc, char **argv);
void			ft_error_str(t_cmd_table *table, char *str);
void			ft_error_export(t_cmd_table *table, char *str);
void			ft_wrong_access_error(t_cmd_table *table, char *cmd, int code);
void			print_lines(t_list *tok, int out, bool n_opt);
void			ft_change_old_pwd(t_cmd_table *table);
void			purge_equal(char *str, t_env **env);
void			change_token(t_list *env_list, t_env *env);
void			manage_empty_export(t_cmd_table *table);
void			del_env(void *value);
void			handle_signal(int signal);
void			handle_interact(int signal);
void			purge_input(t_token_list *list, const char *str);
void			lexer_split(char *line, t_token_list *list);
void			add_cmds(t_token_list *tok, t_cmd_table **table);
void			count_pipes(t_cmd_table *table);
void			path_exec(t_cmd *cmd, t_cmd_table *table);
void			free_all(char **arr);
void			save_original_fd(t_cmd_table *table);
void			restore_and_close_fds(t_cmd_table *table);
void			write_here_doc(char *limit, t_cmd_table *table);
void			manage_redir_out(t_cmd_table *table, t_redir out_redir);
void			manage_redir_in(t_cmd_table *table, t_redir in_redir);
void			fill_redirs(t_cmd *cmd, t_cmd_table *table);
void			redir_dup(t_cmd_table *table);
void			close_red_fd(int files[2]);
void			free_token_list(t_list *tokens);
void			free_redir_list(t_list *lst);
void			free_cmd_list(t_list *lst);
void			free_env(t_list *lst);
void			free_cmd_table(t_cmd_table *table);
void			attach_cmd_to_table(t_cmd *cmd, t_cmd_table **table);
void			add_token(t_token_list *list, char *value, bool expand);
void			update_quote_state(char c, bool *in_quote, char *quote_char);
void			handle_token_segment(char *line, \
				t_token_list *list, int *start, int i);
void			handle_last_token(char *line, \
				t_token_list *list, int start, int end);
void			error_handler(int code);
void			check_error(int value, int to_check, t_cmd_table *table);
void			debug_parser(t_cmd_table *table);
void			attach_redir(t_cmd *cmd, t_redir *redir, t_cmd_table *table);
char			*ft_strjoin_free(char *s1, char *s2);
char			*get_value(void *token);
char			*get_direction(t_tok *tok);
char			*expand_variable(char *token, int *i, t_cmd_table *table);
char			*append_plain_text(char *token, int *i);
char			*check_expansion(char *token, t_cmd_table *table, t_tok *tok);
char			*ft_new_limit(char *limit, t_cmd_table *table);
char			*ft_getenv_value(t_cmd_table *table, char *str);
char			**get_cmd(t_list *origin);
// char			**get_paths(void);
char			**get_paths(t_cmd_table *table, char *cmd);
t_env			*mini_get_env(t_cmd_table *table, char *var);
t_list			*check_n_flag(t_list *next, bool *n_opt);
t_list			*ft_make_env(char *str);
t_list			*env_init(char **orig_envp, char *shlvl);
// t_list			*env_init(char **orig_envp);
t_cmd			*alloc_cmd(void);
t_cmd			*add_redir(t_list *tok_list, t_cmd_table **table);
t_cmd			*create_or_redir_cmd(t_list *current_token, \
				t_cmd_table **table);
t_tok			*copy_and_expand(t_tok *orig, t_cmd_table *table);
t_redir			*get_redir_in(t_list *list);
t_redir			*get_redir_out(t_list *list);
t_redir			*alloc_redir(void);
t_tok_type		get_ttype(char *tok);
t_tok_type		get_token_type(t_list *cmd);
t_error_code	lexer(char *input, t_list **envl);
t_error_code	parser(t_token_list *list, t_list **envl);

//MINICOPIA
int	is_input_valid(const char *input);
int	has_non_supported_one(const char *input, char *test, char *err_message);
int	has_quotes_open(const char *input, char *err_message);
int	is_input_valid_not_supported(const char *input, char *err_message);
int	has_non_supported(const char *input, char *test, char *err_message);
int	is_input_valid_unexpected_token(const char *input, char *err_message);
int	has_spaces_between_char(const char *input, char c, char *err_message);
int	has_forbidden_sequence(const char *input, char *test, char *err_message);
int	has_char_at_end(const char *input, char c, char *err_message);
int	has_char_at_beginning(const char *input, char c, char *err_message);
int	ft_strisspace(char *str);
t_cmd_table	*get_cmd_table(const char *input, int *curr_pos);
void	skip_spaces(const char *input, int *curr_pos);
void	skip_quotes(const char *input, int *curr_pos);
int	ft_isspace(char c);
char	*ft_strncpy(char *dest, char *src, size_t n);
t_cmd	*get_cmds(const char *input, int *curr_pos);
void	replace_envs(t_list **tokens, t_list *redirs, t_cmd_table *table);
int	is_token_delimiter(char c);
char	*ft_strcpy(char *dest, const char *src);
void	debug_table(t_cmd_table *table);
t_env	*ft_create_env(char *key, char *value);
#endif
