CC = cc
CFLAGS = -Wall -Wextra -Werror -I./includes

SRC_DIR = srcs
OBJ_DIR = obj
NAME = minishell

LIBFT = libft/libft.a

SRCS = srcs/execution/exec.c \
       srcs/execution/program_path.c \
       srcs/execution/exec_command.c \
       srcs/execution/exec_pipe.c \
       srcs/execution/exec_sequence.c \
       srcs/execution/exec_redir.c \
       srcs/execution/built-ins/exec_builtins.c \
       srcs/execution/built-ins/echo.c \
       srcs/execution/built-ins/cd.c \
       srcs/execution/built-ins/pwd.c \
       srcs/execution/built-ins/utils.c \
       srcs/execution/built-ins/utils2.c \
       srcs/execution/testing_cmd.c \
      #  srcs/execution/testing_all.c \
      #  srcs/execution/testing_redir.c \
      #  srcs/execution/testing_sequence.c \
      #  srcs/execution/testing_pipe.c \
      #  srcs/parser/parser.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	make -C libft

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

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