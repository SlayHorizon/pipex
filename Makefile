NAME = pipex

SRC = pipex.c utils.c string_utils.c ft_split.c

OBJ = $(SRC:%.c=%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -O3

RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) -r $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
