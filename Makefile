
CFILES = pipex.c pipex_utils.c execute_command.c more_pipex_utils.c

MANDATORYFILES = pipex_utils_mandatory.c

BONUSFILES = pipex_utils.c execute_command.c pipex_bonus.c pipex_utils_bonus.c 

CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address,leak 

CC = cc

OFILES = $(CFILES:.c=.o)

OMANDATORYFILES = $(MANDATORYFILES:.c=.o)

OBONUSFILES = $(BONUSFILES:.c=.o)

NAME = pipex

LIBFT_DIR = Libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME):$(OFILES) $(OMANDATORYFILES) $(LIBFT) pipex_mandatory.h
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) $(OFILES) $(OMANDATORYFILES) $(LIBFT) -o $(NAME)

bonus:$(OFILES) $(OBONUSFILES) $(LIBFT) pipex_bonus.h
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) $(OFILES) $(OBONUSFILES) $(LIBFT) -o $(NAME)_bonus

%.o: %.c
	@$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c $< -o $@

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OFILES) $(OMANDATORYFILES) $(OBONUSFILES)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re:	fclean all

.PHONY: all bonus clean fclean re
