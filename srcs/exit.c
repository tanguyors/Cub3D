#include <cub3d.h>

int	close_window(t_game *param)
{
	if (param)
		free_game(param);
	exit(0);
	return (0);
}

void	free_map_grid(t_game *g)
{
	int	y;

	y = -1;
	if (g->map.grid)
	{
		while (++y < g->map.height)
			free(g->map.grid[y]);
		free(g->map.grid);
	}
}

int	exit_with_error(t_game *g, const char *msg)
{
	if (msg)
		fprintf(stderr, "Error\n%s\n", msg);
	if (g->screen.img_ptr)
		mlx_destroy_image(g->mlx, g->screen.img_ptr);
	free_textures(g);
	free_map_grid(g);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	if (g->mlx)
		free(g->mlx);
	exit(EXIT_FAILURE);
}