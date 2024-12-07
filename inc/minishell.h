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

void	handle_signal(int signal, siginfo_t *info, void *ctx);
void prueba_test(void);
t_error_code	executor(t_cmd_table *table);
void	purge_input(t_token_list *list, const char *str);
t_error_code	lexer(char *input);
void	debug_parser(t_cmd_table *table);
void	add_cmds(t_token_list *tok, t_cmd_table **table);
t_error_code	parser(t_token_list *list);
t_tok_type	get_ttype(char *tok);
void	add_token(t_token_list *list, char *value);
void	debug(t_token_list *list);
int	main(void);
#endif
