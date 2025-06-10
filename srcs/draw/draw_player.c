#include "../includes/cub3d.h"

int	is_in_circle(int x, int y, int center_x, int center_y, int radius)
{
	int	dx;
	int	dy;

	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy <= radius * radius);
}

void	draw_player(t_game *g)
{
	t_point	dir_end;
	int		center_x;
	int		center_y;
	int		radius;
	double	dir_length;

	center_x = MINIMAP_WIDTH / 2;
	center_y = MINIMAP_HEIGHT / 2;
	radius = MINIMAP_WIDTH / 2 - 2;
	fill_image_circle(g, 0xFF0000, (t_point){center_x, center_y}, 3);
	dir_length = 20.0;
	dir_end.x = center_x + (int)(g->player.dir_x * dir_length);
	dir_end.y = center_y + (int)(g->player.dir_y * dir_length);
	if (is_in_circle(dir_end.x, dir_end.y, center_x, center_y, radius))
	{
		draw_line(g, (t_point){center_x, center_y}, dir_end, 0x00FF00);
	}
}
