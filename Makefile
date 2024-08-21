NAME	= fdf
CC		= cc
CFLAGS	= -Wextra -Wall -Werror
LIBMLX	= ./MLX42

LIBFT = libft/libft.a
LIBFT_MAKEFILE = libft/Makefile
LIBFT_DIR = ./libft

HEADERS	= -I ./include -I $(LIBMLX)/include
#linux
LIBS	= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
#mac
#LIBS	= $(LIBMLX)/build/libmlx42.a -framework Cocoa -framework OpenGL -framework IOKit -Iinclude -lglfw -L"/opt/homebrew/Cellar/glfw/3.3.8/lib/"
SRCS	= main.c \
	parse_map.c \
	linear_transformations.c \
	hooks.c \
	pixels_to_img.c \
	pixels_to_img_utils.c \
	view.c \
	exit.c \
	utils.c

OBJS	= ${SRCS:.c=.o}

all: $(LIBMLX) $(LIBFT) $(NAME)

$(LIBMLX):
	git clone https://github.com/codam-coding-college/MLX42.git $(LIBMLX)
	cd $(LIBMLX)
	cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS) libft
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(HEADERS) $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJS)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf $(LIBMLX)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all, clean, fclean, re, libmlx
