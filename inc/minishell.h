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

void	parser(t_token_list *list);
t_tok_type	get_ttype(char *tok);
void	add_token(t_token_list *list, char *value);
t_token_list	*lexer(char *input);
void	debug(t_token_list *list);
int	main(void);
void	create_token(void);
#endif
