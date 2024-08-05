
CFILES = pipex.c pipex_utils.c execute_command.c

BONUSFILES = pipex_utils.c execute_command.c pipex_bonus.c pipex_utils_bonus.c 

CFLAGS = -Wall -Wextra -Werror -fsanitize=address,leak -g

CC = cc

OFILES = $(CFILES:.c=.o)

OBONUSFILES = $(BONUSFILES:.c=.o)

NAME = pipex

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME):$(OFILES) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) $(OFILES) $(LIBFT) -o $(NAME)

bonus:$(OFILES) $(OBONUSFILES) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBONUSFILES) $(LIBFT) -o $(NAME)_bonus

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OFILES)
	rm -f $(OBONUSFILES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
