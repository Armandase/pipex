NAME		= pipex
SRCS		= pipex_main.c pipex_parsing.c
CC			= clang
CFLAGS		= -Wall -Werror -Wextra
LIBS		= -Llibft -lft
OBJS		= ${SRCS:.c=.o}

all: ${NAME}

$(NAME): ${OBJS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS} -g 

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
	make clean -C ./libft
	rm -f ${OBJS}

fclean : clean
	make fclean -C ./libft
	rm -f ${NAME}

re: fclean all


.PHONY: all clean fclean re makelibft
