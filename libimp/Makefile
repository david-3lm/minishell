SHELL := /bin/zsh
NAME = libft.a
SRC = ft_printf.c ft_print_string.c ft_print_nbr_dec.c ft_print_unsigned.c ft_print_hex.c ft_print_ptr.c \
ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_putstr_fd.c ft_split.c ft_split_set.c ft_strchr.c ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c
OBJ = $(SRC:.c=.o)
SRCBONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c
OBJBONUS = $(SRCBONUS:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f

# COLORES
COLOREND = \033[0m
GREEN = \033[1;32m
RED = \e[1;31m
YELLOW = \e[1;33m
BLUE = \033[0;34m
CIAN = \e[7;36m

# Barra de progreso
TOTAL_FILES = $(words $(OBJ) + $(OBJBONUS)) # Total de archivos
CURRENT_FILE = 0 # Contador de archivos procesados
BAR_WIDTH = 40

define progress_bar
	$(eval CURRENT_FILE=$(shell echo $$(($(CURRENT_FILE)+1))))
	@progress=$$(($(CURRENT_FILE) * $(BAR_WIDTH) / $(TOTAL_FILES))); \
	empty=$$(($(BAR_WIDTH) - $$progress)); \
	printf "\r$(YELLOW)["; \
	for i in $$(seq 1 $$progress); do printf "#"; done; \
	for i in $$(seq 1 $$empty); do printf "."; done; \
	printf "] $(CURRENT_FILE)/$(TOTAL_FILES)$(COLOREND)";
endef

define ascii_art
	@printf "$(RED)░█▀▀░█▀▄░█▀▀░░░░░█▄█░▀█▀░█▀▀░█░█\n"
	@printf "$(RED)░█░░░█░█░█▀▀░▄▄▄░█░█░░█░░█░█░█░█\n"
	@printf "$(RED)░▀▀▀░▀▀░░▀▀▀░░░░░▀░▀░▀▀▀░▀▀▀░▀▀▀\n"
	@printf "$(BLUE)░█▀▄░█░░░█▀█░█▀█░█▀▀░▀▀█░░░░░█░░\n"
	@printf "$(BLUE)░█░█░█░░░█░█░█▀▀░█▀▀░▄▀░░▄▄▄░█░░\n"
	@printf "$(BLUE)░▀▀░░▀▀▀░▀▀▀░▀░░░▀▀▀░▀▀▀░░░░░▀▀▀\n"
endef



all: $(NAME)

$(NAME): $(OBJ) $(OBJBONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJBONUS)
	@echo "$(GREEN)ft_printf compilado!$(COLOREND)\n"
	$(ascii_art)

%.o: %.c
	@$(call progress_bar)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJBONUS)
	clear
	@echo "$(BLUE)Limpio$(COLOREND)"

fclean: clean
	$(RM) $(NAME)
	clear
	@echo "$(BLUE)Limpio$(COLOREND)"

re: fclean all

bonus: $(OBJBONUS)
	ar rcs $(NAME) $(OBJBONUS)

.PHONY: all clean fclean re bonus
