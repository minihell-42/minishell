CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes

SRC_DIR = srcs
OBJ_DIR = obj
NAME = minishell

SRCS = srcs/execution/exec.c \
       srcs/execution/exec_command.c \
       srcs/execution/exec_pipe.c \
       srcs/execution/exec_sequence.c \
       srcs/parser/parser.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re