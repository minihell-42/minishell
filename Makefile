CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes

SRC_DIR = srcs
OBJ_DIR = obj
NAME = minishell

LIBFT = libft/libft.a

# SRCS = $(shell find $(SRC_DIR) -name "*.c") --> find all files in srcs
SRCS = srcs/main.c \
			 srcs/execution/exec.c \
       srcs/execution/exec_command.c \
       srcs/execution/exec_pipe.c \
       srcs/execution/exec_sequence.c \
       srcs/execution/program_path.c \
			 srcs/parser/lexer.c \
			 srcs/parser/lexer_utils.c \
			 srcs/parser/parser.c \
			 srcs/parser/parser_utils.c \
			 srcs/parser/token.c \
			 srcs/parser/ast.c \
#      srcs/execution/testing_sequence.c \
#      srcs/execution/testing_pipe.c \
#      srcs/execution/testing_cmd.c \
#      srcs/parser/parser.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -L/opt/homebrew/lib -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C libft clean

fclean: clean
	rm -f $(NAME)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re