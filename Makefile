NAME    = pipex
NAME_BONUS = pipex_bonus

SRC     = src/main.c \
			src/parsing.c \
			src/utils.c

SRC_BONUS = src_bonus/main_bonus.c \
			src_bonus/parsing_bonus.c \
			src_bonus/utils_bonus.c \
			$(GNL)

OBJ     = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

CFLAGS  = -Wall -Wextra -Werror -ggdb
CC      = cc
LIBFT   = ./libft/libft.a
PRINTF  = ./printf/libftprintf.a
GNL     = ./GNL/get_next_line.c ./GNL/get_next_line_utils.c

all: $(NAME)

bonus: $(NAME_BONUS)

$(NAME): $(OBJ) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF)
	@echo "COMPILATION DONE ! 👍"

$(NAME_BONUS): $(OBJ_BONUS) $(LIBFT) $(PRINTF)
	@$(CC) $(CFLAGS) -o $(NAME_BONUS) $(OBJ_BONUS) $(LIBFT) $(PRINTF)
	@echo "BONUS COMPILATION DONE ! 🎉"

$(LIBFT):
	@make -C ./libft > /dev/null 2>&1

$(PRINTF):
	@make -C ./printf > /dev/null 2>&1

%.o: %.c
	@$(CC) $(CFLAGS) -Iinclude -Ilibft -Iprintf -IGNL -c $< -o $@

clean:
	@rm -f $(OBJ) $(OBJ_BONUS)
	@make -C ./libft clean > /dev/null 2>&1
	@make -C ./printf clean > /dev/null 2>&1

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS)
	@make -C ./libft fclean > /dev/null 2>&1
	@make -C ./printf fclean > /dev/null 2>&1

re: fclean all

re_bonus: fclean bonus

.PHONY: all bonus clean fclean re re_bonus