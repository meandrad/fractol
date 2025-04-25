NAME = fractol
CC = cc
CFLAGS = -g -I/minilibx -Wall -Wextra -Werror
MLXFLAGS = -L./minilibx-linux -lmlx -lXext -lX11 -lm

SRC = \
	src/handlers.c \
	src/init.c \
	src/lib_utils.c \
	src/main.c \
	src/math.c \
	src/render.c \

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

clean:
		rm -f $(OBJ)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re