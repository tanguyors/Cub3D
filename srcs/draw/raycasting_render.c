#include "../includes/cub3d.h"

void	draw_floor_ceiling(t_game *g)
{
	t_rect	floor;
	t_rect	ceiling;

	floor.x = 0;
	floor.y = g->win_height / 2;
	floor.width = g->win_width;
	floor.height = g->win_height / 2;
	fill_image_rect(g, g->map.floor_color, floor);
	ceiling.x = 0;
	ceiling.y = 0;
	ceiling.width = g->win_width;
	ceiling.height = g->win_height / 2;
	fill_image_rect(g, g->map.ceiling_color, ceiling);
}

void	render_3d(t_game *g)
{
	int	x;

	draw_floor_ceiling(g);
	x = 0;
	while (x < g->win_width)
	{
		cast_ray(g, x);
		x++;
	}
}
