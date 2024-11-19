#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libimp/libft.h"
# include "./structs.h"
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

void	debug(t_token_list *list);
int	main(void);
t_tok_type	get_ttype(char *tok);
void	add_token(t_token_list *list, char *value);
void	add_cmds(t_token_list *tok, t_cmd_table *table);
t_cmd_table	*parser(t_token_list *list);
t_token_list	*lexer(char *input);
#endif
