#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libimp/libft.h"
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

int	    main(void);
char	**    lexer(char *input);
#endif
