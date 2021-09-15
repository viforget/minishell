BLACK           =   \033[0;30m
RED             =   \033[0;31m
GREEN           =   \033[0;32m
ORANGE          =   \033[0;33m
BLUE            =   \033[0;34m
PURPLE          =   \033[0;35m
CYAN            =   \033[0;36m
LIGHT_GRAY      =   \033[0;37m
DARK_GRAY       =   \033[1;30m
LIGHT_RED       =   \033[1;31m
LIGHT_GREEN     =   \033[1;32m
YELLOW          =   \033[1;33m
LIGHT_BLUE      =   \033[1;34m
LIGHT_PURPLE    =   \033[1;35m
LIGHT_CYAN      =   \033[1;33m
WHITE           =   \033[1;37m
NC              =   \033[0m
SRCNAME     =   ft_memset.c         \
                ft_bzero.c          \
                ft_memcpy.c         \
                ft_memccpy.c        \
                ft_memchr.c         \
                ft_memcmp.c         \
                ft_strlen.c         \
                ft_isalpha.c        \
                ft_isdigit.c        \
                ft_isalnum.c        \
                ft_isascii.c        \
                ft_isprint.c        \
                ft_toupper.c        \
                ft_tolower.c        \
                ft_strchr.c         \
                ft_strrchr.c        \
                ft_strcmp.c         \
                ft_strncmp.c        \
                ft_strlcpy.c        \
                ft_strlcat.c        \
                ft_strnstr.c        \
                ft_atoi.c           \
                ft_calloc.c         \
                ft_strdup.c         \
                ft_substr.c         \
                ft_strjoin.c        \
                ft_strtrim.c        \
                ft_itoa.c           \
                ft_strmapi.c        \
                ft_putchar_fd.c     \
                ft_putstr_fd.c      \
                ft_putendl_fd.c     \
                ft_putnbr_fd.c      \
                ft_putnbr_base.c    \
                ft_split.c          \
               	get_next_line.c     \
##               ft_itoa_base.c     \
##               ft_itoa_bases.c    \

OBJS		=	${SRCNAME:.c=.o}
CC			=	@gcc
CFLAGS		=	-Wall -Werror -Wextra

.c.o		:	${CC} ${CFLAGS} -I libft.h -c $< -o ${<:.c=.o}

NAME		=	libft.a
$(NAME):	${OBJS}
	@ar rc ${NAME} ${OBJS}

all:			${NAME}				## Cree la base de la Bibliotheque Statique "libft.a"

clean:                              ## Supprime tout les .o inclus dans la bibliotheque "libft.a"
	@rm -f ${OBJS}

fclean:		clean                   ## Supprime la Bibliotheque Statique et ses fichiers objets
	@rm -f ${NAME}

re:			fclean all              ## Supprime et recompile la Bibliotheque Smaketatique avec ses fichiers objets

complete:   ${OBJS}                 ## Met a jour la libft.a dans sa derniere version
	@ar rc ${NAME} ${OBJS}
	@ranlib ${NAME}

it:         fclean complete         ## recompile completement la libft.a
	@rm ${SRCDIR}*.o
help:                               ## Liste toutes les commandes
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'
man:                                ## Infos Concernant la lib
	@echo "${LIGHT_GRAY}=================================================${NC}"
	@echo "${LIGHT_PURPLE} Project${NC} : ${LIGHT_GREEN}LIBFT${NC}"
	@echo "${LIGHT_PURPLE} Author${NC} : BERTIN Loïc"
	@echo "${LIGHT_GRAY}=================================================${NC}"
.PHONY  =   all clean fclean re
