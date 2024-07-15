NAME = fdf

SRCS = main.c
OBJS = $(SRCS:.c=.o)

MLX = minilibx_mac

CC = cc
CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

#mac
$(NAME): $(OBJ)
	$(CC) $(OBJ) -L$(MLX) -l$(MLX) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I$(MLX) -c $< -o $@

#linux
#$(NAME): $(OBJ)
#	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

#%.o: %.c
#	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@
