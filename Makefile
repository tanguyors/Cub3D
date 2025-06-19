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
			  srcs/parsing/parse_map_init.c \
			  srcs/parsing/parse_map_player.c \
			  srcs/parsing/parse_map_validation_chars.c \
			  srcs/parsing/parse_map_validation_borders.c \
			  srcs/parsing/parse_map_line.c \
			  srcs/parsing/parse_file.c \
			  srcs/parsing/parse_map_content.c \
			  srcs/parsing/parse_utils.c \
			  srcs/parsing/parse_textures.c \
			  srcs/parsing/parse_textures_utils1.c \
			  srcs/parsing/parse_textures_utils2.c \
			  srcs/parsing/parse_colors.c \
			  srcs/utils/free.c \
			  srcs/graphics/init_graphics.c \
			  srcs/events/handle_events.c \
			  srcs/movement/movement_check.c \
			  srcs/movement/movement_translate.c \
			  srcs/movement/movement_rotate.c \
			  srcs/draw/draw_basic.c \
			  srcs/draw/draw_map.c \
			  srcs/draw/draw_player.c \
			  srcs/draw/raycasting_core.c \
			  srcs/draw/raycasting_wall.c \
			  srcs/draw/raycasting_render.c \
			  srcs/exit.c \
			  srcs/game/game_init.c \
			  srcs/game/game_direction.c \
			  srcs/game/game_render.c \
			  srcs/parsing/parse_map_normalize.c \
			  srcs/parsing/parse_map_borders_utils.c \
			  srcs/parsing/parse_map_spaces.c \
			  srcs/parsing/parse_map_spaces_utils.c \
			  srcs/parsing/parse_map_content_pre.c \
			  srcs/parsing/parse_map_content_utils.c \
			  srcs/draw/draw_map_utils.c \
			  srcs/draw/draw_basic_utils.c

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
