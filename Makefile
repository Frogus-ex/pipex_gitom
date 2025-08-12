NAME    = pipex
SRC     = src/main.c \
			src/parsing.c \

OBJ     = $(SRC:.c=.o)
CFLAGS  = -Wall -Wextra -Werror -ggdb
CC      = cc
LIBFT   = ./libft/libft.a
PRINTF  = ./printf/libftprintf.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF)
	@echo "COMPILATION DONE ! 👍"

$(LIBFT):
	@make -C ./libft > /dev/null 2>&1

$(PRINTF):
	@make -C ./printf > /dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) -Iinclude -Ilibft -Iprintf -c $< -o $@

clean:
	@rm -f $(OBJ)
	@make -C ./libft clean > /dev/null 2>&1
	@make -C ./printf clean > /dev/null 2>&1

fclean: clean
	@rm -f $(NAME)
	@make -C ./libft fclean > /dev/null 2>&1
	@make -C ./printf fclean > /dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re