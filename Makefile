NAME = minishell
FLAGS = -Wall -Wextra -Werror -I includes -lreadline  -I/Users/viforget/.brew/opt/readline/include
CC = @gcc
LIBDIR = libft
SRCS = srcs/prompt/main.c\
		srcs/parser/parser.c\
		srcs/exec/pipe_arch.c\
		srcs/utils/print_struct.c\

OBJ = $(SRCS:%.c=%.o)

all: $(NAME)

$(NAME) : $(O_FILES)
			