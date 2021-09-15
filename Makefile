NAME = minishell

FLAGS = -Wall -Wextra -Werror -lreadline -L $(HOME)/.brew/opt/readline/lib -I$HOME/.brew/opt/readline/include

LIB = lib/libft

CC = @gcc -I includes

SRCS =	srcs/prompt/main.c\
		srcs/prompt/tabdup.c\
		srcs/parser/parser.c\
		srcs/parser/av.c\
		srcs/parser/bin.c\
		srcs/parser/cut.c\
		srcs/parser/tools.c\
		srcs/parser/tools2.c\
		srcs/parser/tools3.c\
		srcs/parser/tools4.c\
		srcs/parser/fornorm.c\
		srcs/parser/skip.c\
		srcs/built_in/cd.c\
		srcs/built_in/echo.c\
		srcs/built_in/env.c\
		srcs/built_in/exit.c\
		srcs/built_in/export.c\
		srcs/built_in/pwd.c\
		srcs/built_in/unset.c\
		srcs/exec/pipe_arch.c\
		srcs/exec/pipe_open_close.c\
		srcs/exec/execution.c\
		srcs/utils/exit_error.c\

OBJ = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
			@make -C $(LIB)
			$(CC) $(FLAGS) -L$(LIB) -lft $(OBJ) -o $(NAME)
			@echo "\033[32mCOMPILATION OK\033[0m"
			
clean:
		@rm -rf $(OBJ)
		@make clean -C $(LIB)
		@echo "\033[36mCLEAN OK\033[0m"

fclean: clean
		@rm -rf $(NAME)
		@make fclean -C $(LIB)
		@echo "\033[36mFCLEAN OK\033[0m"

lib:
		@make re -C $(LIB)

re: fclean all

.PHONY: all fclean clean re lib
