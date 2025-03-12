CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes
LDFLAGS = -lreadline

SRC_DIR = srcs
OBJ_DIR = obj
NAME = minishell

LIBFT = libft/libft.a
# SRCS = $(shell find $(SRC_DIR) -name "*.c") --> find all files in srcs
SRCS = srcs/main.c \
       srcs/execution/exec.c \
       srcs/execution/exec_command.c \
       srcs/execution/exec_pipe.c \
       srcs/execution/program_path.c \
       srcs/execution/exec_redir.c \
       srcs/execution/built-ins/exec_builtins.c \
       srcs/execution/built-ins/echo.c \
       srcs/execution/built-ins/exit.c \
       srcs/execution/built-ins/cd.c \
       srcs/execution/built-ins/pwd.c \
       srcs/execution/built-ins/export.c \
       srcs/execution/built-ins/unset.c \
       srcs/execution/built-ins/env.c \
       srcs/execution/built-ins/utils.c \
       srcs/execution/built-ins/utils2.c \
       srcs/execution/built-ins/utils3.c \
       srcs/parser/lexer.c \
       srcs/parser/lexer_utils.c \
       srcs/parser/parser.c \
       srcs/parser/parser_utils.c \
       srcs/parser/tokens.c \
       srcs/parser/ast.c \

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
