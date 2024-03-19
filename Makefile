NAME = pipex

INCLUDE_DIR = include
SRC_DIR = src
STR_DIR = $(SRC_DIR)/string_funcs
OBJ_DIR = obj


SRC = $(addprefix $(SRC_DIR)/, \
	pipex.c utils.c) \
	$(addprefix $(STR_DIR)/, \
	string_utils.c ft_split.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -O3 -I$(INCLUDE_DIR)

RM = rm -f

all: $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/string_funcs

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
