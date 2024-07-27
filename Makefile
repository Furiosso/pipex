
#COMMON_FILES = pipex.c

CFILES = pipex.c pipex_utils.c execute_command.c

#BONUSFILES =

CFLAGS = -Wall -Wextra -Werror -fsanitize=address,leak -g

CC = cc

#OCOMMONFILES = $(COMMON_FILES:.c=.o)
  
OFILES = $(CFILES:.c=.o)

#OBONUSFILES = $(BONUSFILES:.c=.o)

NAME = pipex

#BONUS_NAME =

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME):$(OFILES) $(LIBFT)
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) $(OFILES) $(LIBFT) -o $(NAME)

#bonus:$(OBONUSFILES) $(OCOMMONFILES) $(LIBFT)
#	@$(CC) $(CFLAGS) $(OCOMMONFILES) $(OBONUSFILES) $(LIBFT) -o $(BONUS_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OFILES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)
	#rm -f $(BONUS_NAME)

re:	fclean all

.PHONY: all clean fclean re
