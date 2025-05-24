NAME = hotrace

CFLAGS = -Wall -Wextra -Werror -O3

SRCS = \
main.c \
get_next_line.c \
ft_calloc.c \
ft_strchr.c \
ft_strjoin.c \
ft_strdup.c \
ft_strlen.c \
ft_memset.c \
ft_strlcpy.c \
ft_strlcat.c \
ft_strncmp.c \
ft_putchar.c \
ft_putnbr.c

all: $(NAME)

$(NAME): $(SRCS)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS)

clean:

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

gen_file: gen.c
	rm -f gen
	$(CC) $(CFLAGS) -o gen gen.c
	rm -f test.txt
	./gen > test.txt