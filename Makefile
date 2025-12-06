CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
INCLUDES = -I$(LIBFT_DIR)

SRCS = main.c \
       parse_input.c \
       is_valid_input.c \
       stack_utilis.c \
       normalize.c \
       push.c \
       swap.c \
       rotate.c \
       reverse.c \
       push_swap.c

OBJS = $(SRCS:.c=.o)
NAME = push_swap

.PHONY: all clean fclean re libft

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	rm -f $(LIBFT)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all