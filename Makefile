INC_DIR = includes/
SRC_DIR = src/
OBJ_DIR = bin/
LIBFT_DIR = libft/

SRCS = ft_printf.c buffer.c ft_printf_utils.c \
		parser.c print_arg.c utils.c print_arg2.c print_arg_utils.c

OBJS = $(addprefix ${OBJ_DIR}, ${SRCS:.c=.o})

NAME = libftprintf.a

CFLAGS = -Wall -Wextra -Werror

INCPATH = -I ${INC_DIR} -I ${LIBFT_DIR}

all : ${NAME}

${NAME} : libft ${OBJ_DIR} ${OBJS}
	ar rc ${NAME} ${OBJS}

${OBJ_DIR}%.o : ${SRC_DIR}%.c
	gcc ${CFLAGS} ${INCPATH} -c $< -o $@

${OBJ_DIR} : 
	@mkdir -p ${OBJ_DIR}

exe :	libft ${OBJS}
	gcc ${CFALGS} bin/*.o libft/ft_strlen.o \
	libft/ft_isdigit.o libft/ft_atoi.o -o exe 

libft : 
	make -C libft/
	cp libft/libft.a libftprintf.a

clean :
	rm -rf ${OBJ_DIR}
	cd libft && ${MAKE} fclean

fclean : clean
	rm -f ${NAME}

bonus : all

re : fclean all

.PHONY : all clean fclean libft re 
