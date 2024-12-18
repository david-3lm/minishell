CC = cc
NAME := pipex
CFLAGS := -g3 -Wextra -Werror -Wall
RM = rm -f

GREEN := \033[0;32m
RED := \033[0;31m
YELLOW := \033[0;33m
PURPLE := \033[0;35m
BLUE := \033[0;36m
CYAN := \033[1;36m
RESET := \033[0m

LIB_DIR := ../libimp/

HEADERS := -I $(LIB_DIR) \

LIB := $(LIB_DIR)libft.a 


SRCS :=	pipex.c \
    	utils.c \
		proccess.c \
    	here_doc.c \

OBJS :=  $(SRCS:.c=.o)

all: $(NAME)


$(LIB):
	@$(MAKE) -C $(LIB_DIR)


$(NAME): $(OBJS) $(LIB)
	@$(CC) $(OBJS) $(LIBFT) $(PRINTF) -o $(NAME)
	@echo "$(GREEN)Compilación completada con éxito.$(RESET)"

clean:
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean

fclean:
	@echo "$(RED)Limpiando todo...$(RESET)"
	@rm -rf $(NAME)
	@rm -f here_doc
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@echo "$(GREEN) ¡Todo limpio! $(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
