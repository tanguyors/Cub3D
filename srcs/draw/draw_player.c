#include "../includes/cub3d.h"

int	is_in_circle(t_point point, t_point center, int radius)
{
	int	dx;
	int	dy;

	dx = point.x - center.x;
	dy = point.y - center.y;
	return (dx * dx + dy * dy <= radius * radius);
}

void	draw_player(t_game *g)
{
	t_point	dir_end;
	t_point	center;
	int		radius;
	double	dir_length;

	center.x = MINIMAP_WIDTH / 2;
	center.y = MINIMAP_HEIGHT / 2;
	radius = MINIMAP_WIDTH / 2 - 2;
	fill_image_circle(g, 0xFF0000, center, 3);
	dir_length = 20.0;
	dir_end.x = center.x + (int)(g->player.dir_x * dir_length);
	dir_end.y = center.y + (int)(g->player.dir_y * dir_length);
	if (is_in_circle(dir_end, center, radius))
	{
		draw_line(g, center, dir_end, 0x00FF00);
	}
}
