#include "cub3d.h"

static void	init_mlx_window(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_with_error(g, "MLX init failed");
	g->win_width = MAIN_WIN_WIDTH;
	g->win_height = MAIN_WIN_HEIGHT;
	g->win = mlx_new_window(g->mlx, g->win_width, g->win_height, "Cub3D");
	if (!g->win)
		exit_with_error(g, "Window creation failed");
}

static void	init_screen_image(t_game *g)
{
	g->screen.img_ptr = mlx_new_image(g->mlx, g->win_width, g->win_height);
	if (!g->screen.img_ptr)
		exit_with_error(g, "Image creation failed");
	g->screen.img_data = mlx_get_data_addr(g->screen.img_ptr,
			&g->screen.bits_per_pixel, &g->screen.line_length,
			&g->screen.endian);
}

static void	load_texture(t_game *g, int i)
{
	int	w;
	int	h;

	if (!g->textures[i].path)
		exit_with_error(g, "Missing texture path");
	g->textures[i].img = mlx_xpm_file_to_image(g->mlx, g->textures[i].path, &w,
			&h);
	if (!g->textures[i].img)
		exit_with_error(g, "Failed to load texture");
	g->textures[i].width = w;
	g->textures[i].height = h;
	g->textures[i].img_data = mlx_get_data_addr(g->textures[i].img,
			&g->textures[i].bits_per_pixel, &g->textures[i].line_length,
			&g->textures[i].endian);
	printf("Loaded texture %d: %s (%dx%d)\n", i, g->textures[i].path, w, h);
}

void	init_game(t_game *g)
{
	init_mlx_window(g);
	init_screen_image(g);
	for (int i = 0; i < 4; i++)
		load_texture(g, i);
	g->move_speed = MOVE_SPEED;
	g->rot_speed = ROT_SPEED;
	ft_memset(&g->keys, 0, sizeof(t_keys));
}
