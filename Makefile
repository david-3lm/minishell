NAME = minishell
SRC = ./src/built-ins/bi_exit.c ./src/built-ins/bi_karol.c ./src/built-ins/bi_moon.c ./src/built-ins/bi_star.c ./src/built-ins/bi_weather.c ./src/built-ins/bi_echo.c ./src/built-ins/builtins.c ./src/built-ins/bi_cd.c ./src/built-ins/bi_env.c ./src/built-ins/bi_export.c ./src/built-ins/bi_pwd.c ./src/built-ins/bi_unset.c ./src/core/actions.c ./src/core/executor.c ./src/core/lexer.c ./src/core/parser.c ./src/env/envv.c ./src/pipex/utils.c ./src/pipex/proccess.c ./src/pipex/table_executor.c ./src/redir/here_doc.c ./src/redir/redir_parse.c ./src/redir/redirs_manager.c ./src/redir/redirs_fd.c ./src/utils/cleaner.c ./src/utils/cmd_handler.c ./src/utils/lexer_utils.c ./src/utils/redir_utils.c ./src/utils/tokenizer.c ./src/utils/cmd_types.c ./src/utils/kntxesi_exec.c  ./src/utils/error_handler.c ./src/utils/expansion_utils.c ./src/main.c 
OBJ = $(SRC:.c=.o)
LIB_DIR = ./libimp
LIB = $(LIB_DIR)/libft.a
MAIN_HEADER = ./inc/minishell.h
HEADERS = ./inc/defines.h ./inc/minishell.h ./inc/structs.h 
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g3 
RM = rm -f

# COLORES
COLOREND = \033[0m
GREEN = \033[1;32m
RED = \e[1;31m
YELLOW = \e[1;33m
BLUE = \033[0;34m
CIAN = \e[7;36m


all: $(NAME) $(CLIN)
#-fsanitize=address
$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) $(LIB) -fsanitize=address -o $(NAME) -lreadline

$(LIB):
	@$(MAKE) -C $(LIB_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -fsanitize=address -c $< -o $@

clean:
	$(RM) $(OBJ)
	@$(MAKE) clean -C $(LIB_DIR)
	@clear
	@echo "$(BLUE)Limpio$(COLOREND)"

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIB_DIR)
	@clear
	@echo "$(BLUE)Limpio$(COLOREND)"

re: fclean all

exec:
	./$(NAME)

norma:
	@echo "$(CIAN)SCRIPTS\n$(COLOREND)"
	@for file in $(SRC); do \
		norminette $$file | grep "OK!" > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$file: OK!$(COLOREND)"; \
		else \
			echo "$(RED)"; \
			norminette $$file; \
			echo "$(COLOREND)"; \
		fi \
	done
	@echo "$(CIAN)\nHEADERS\n$(COLOREND)"
	@for header in $(HEADERS); do \
		norminette $$header | grep "OK!" > /dev/null; \
		if [ $$? -eq 0 ]; then \
			echo "$(GREEN)$$header: OK!$(COLOREND)"; \
		else \
			echo "$(RED)"; \
			norminette $$header; \
			echo "$(COLOREND)"; \
		fi \
	done

debug: CFLAGS += -g3 -O0
debug: re
# gdb 

light: CFLAGS = 
light: re

update:
	./update_make.sh
	./update_header.sh $(MAIN_HEADER)


.PHONY: all clean fclean re exec norma debug
