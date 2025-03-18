NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
MLX_PATH	= mlx_linux
MLX_FLAGS	= -L$(MLX_PATH) -lmlx -L/usr/lib -lXext -lX11 -lm -lz

# Ajout du chemin vers la libft
LIBFT_PATH	= libft
LIBFT		= $(LIBFT_PATH)/libft.a
INCLUDES	= -I includes/ -I $(LIBFT_PATH) -I$(MLX_PATH)

SRCS		= srcs/main.c \
			  srcs/parsing/check_file.c \
			  srcs/parsing/parse_map.c

OBJS		= $(SRCS:.c=.o)

all: $(LIBFT) make_mlx $(NAME)

make_mlx:
	make -C $(MLX_PATH)

$(LIBFT):
	make -C $(LIBFT_PATH)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBFT) $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean
	rm -f $(OBJS)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re make_mlx
