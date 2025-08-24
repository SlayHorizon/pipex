NAME = pipex
NAME_BONUS = pipex_bonus

INCLUDE_DIR = include

SRC_DIR = src
SRC_BONUS_DIR = src_bonus

OBJ_DIR = obj
OBJ_BONUS_DIR = obj_bonus
STR_DIR = string_funcs

SRC = $(addprefix $(SRC_DIR)/, \
	pipex.c utils.c error.c) \
	$(addprefix $(SRC_DIR)/$(STR_DIR)/, \
	string_utils.c ft_split.c)

SRC_BONUS = $(addprefix $(SRC_BONUS_DIR)/, \
	pipex.c utils.c error.c here_doc.c) \
	$(addprefix $(SRC_BONUS_DIR)/$(STR_DIR)/, \
	string_utils.c ft_split.c)

OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
OBJ_BONUS = $(SRC_BONUS:$(SRC_BONUS_DIR)/%.c=$(OBJ_BONUS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Werror -Wextra -g -O3 -I$(INCLUDE_DIR)

RM = rm -f

all: $(NAME)

$(OBJ): | $(OBJ_DIR)

$(OBJ_BONUS): | $(OBJ_BONUS_DIR)

$(OBJ_BONUS): $(OBJ_BONUS_DIR)/%.o : $(SRC_BONUS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_BONUS_DIR):
	mkdir -p $(OBJ_BONUS_DIR)/$(STR_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)/$(STR_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	${CC} ${CFLAGS} -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)

re: fclean all

bonus: $(NAME_BONUS)

$(NAME_BONUS): $(OBJ_BONUS)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -o $(NAME_BONUS)

.PHONY: all clean fclean re bonus
