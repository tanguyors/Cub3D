#include "cub3d.h"

void	init_mlx_window(t_game *g)
{
	g->mlx = mlx_init();
	if (!g->mlx)
		exit_with_error(g, "MLX init failed");
	g->win = mlx_new_window(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D");
	if (!g->win)
		exit_with_error(g, "Window creation failed");
}

void	init_screen_image(t_game *g)
{
	g->img = mlx_new_image(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g->img)
		exit_with_error(g, "Image creation failed");
	g->addr = mlx_get_data_addr(g->img, &g->bits_per_pixel, &g->line_length,
			&g->endian);
}

int	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		game->textures[i].img = mlx_xpm_file_to_image(game->mlx,
				game->textures[i].path, &game->textures[i].width,
				&game->textures[i].height);
		if (!game->textures[i].img)
		{
			ft_printf("Error: Failed to load texture %d\n", i);
			return (0);
		}
		game->textures[i].addr = mlx_get_data_addr(game->textures[i].img,
				&game->textures[i].bits_per_pixel,
				&game->textures[i].line_length, &game->textures[i].endian);
		if (!game->textures[i].addr)
		{
			ft_printf("Error: Failed to get texture data %d\n", i);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (0);
	game->win = mlx_new_window(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D");
	if (!game->win)
		return (0);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (0);
	game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
			&game->line_length, &game->endian);
	if (!game->addr)
		return (0);
	if (!init_textures(game))
		return (0);
	return (1);
}
