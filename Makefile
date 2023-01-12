NAME		= pipex
SRCS		= pipex_main.c pipex_parsing.c pipex_path.c \
			  ft_open_file.c ft_exit_free.c ft_execution.c \
			  ft_exe_pipe.c 
SRCS_BONUS	= pipex_main_bonus.c pipex_parsing.c pipex_path.c \
			  ft_open_file.c ft_exit_free.c ft_execution.c \
			  ft_exe_pipe.c ft_heredoc_bonus.c
CC			= clang
CFLAGS		= -Wall -Werror -Wextra
LIBS		= -Llibft -lft
OBJS		= ${SRCS:.c=.o}
OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

all: ${NAME}

$(NAME): ${OBJS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${NAME} ${SRCS} ${LIBS} 

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

bonus: ${OBJS_BONUS}
	make -C ./libft
	${CC} ${CFLAGS} -o ${NAME} ${SRCS_BONUS} ${LIBS} 

clean:
	make clean -C ./libft
	rm -f ${OBJS}
	rm -f ${OBJS_BONUS}

fclean : clean
	make fclean -C ./libft
	rm -f ${NAME}

re: fclean all


.PHONY: all clean fclean re bonus
