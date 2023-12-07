NAME		= philo

SRC			= philosophers.c \
			  del_obj.c \
			  init_obj.c \
			  file_work.c \
			  convert_str.c	\
			  additional_func.c \
			  game_manager.c \
			  add_func_manager.c

SRCDIR		= ./project/philosophers/
OBJ			= ${addprefix ${SRCDIR}, ${SRC:.c=.o}}

CC			= cc
FLAGS		= -fsanitize=address

.c.o:		
			@$(CC) -c $(FLAGS) -o $@ $<

all:		${NAME} clean

${NAME}:	${OBJ}
			@${CC} ${FLAGS} ${OBJ} -o ${NAME}
			@echo "Done"

re:			${NAME} clean

clean:		
			@rm -f ${OBJ}

fclean:		clean
			@rm -f ${NAME}

.Phony:		all ${NAME} clean fclean re