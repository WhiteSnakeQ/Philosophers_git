NAME		= philo

SRC			= philosophers.c \
			  del_obj.c \
			  init_obj.c \
			  file_work.c \
			  convert_str.c

SRCDIR		= ./project/philosophers/
OBJ			= ${addprefix ${SRCDIR}, ${SRC:.c=.o}}

CC			= gcc
FLAGS		= -Wall -Wextra -Werror -fsanitize=address

all:		${NAME} clean

${NAME}:	${OBJ}
			@${CC} ${FLAGS} ${OBJ} -o ${NAME}

re:			fclean all

clean:		
			@rm -f ${OBJ}

fclean:		clean
			@rm -f ${NAME}

.Phony:		all ${NAME} clean fclean