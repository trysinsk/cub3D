NAME = cub3D

CFLAGS = -Wall -Werror -Wextra -I./include

CC = cc

SRCS = src/cub3D.c \
		src/map_checking/map_checking_1.c \


OBJS = ${SRCS:.c=.o}

%.o : %.c
	${CC} ${CFLAGS} -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

${NAME}: ${OBJS}
		${CC} ${OBJS} -Lminilibx-linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
