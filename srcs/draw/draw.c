#include <cub3d.h>

void	fill_image_circle(t_game *g, int color, t_point center, int radius)
{
	int	px;
	int	py;
	int	pixel;

	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
			{
				px = center.x + x;
				py = center.y + y;
				if (px >= 0 && px < g->win_width && py >= 0
					&& py < g->win_height)
				{
					pixel = py * g->screen.line_length + px
						* (g->screen.bits_per_pixel / 8);
					*(int *)(g->screen.img_data + pixel) = color;
				}
			}
		}
	}
}

void	fill_image_rect(t_game *g, int color, t_rect rect)
{
	int	pixel;

	for (int y = rect.y; y < rect.y + rect.height; y++)
	{
		for (int x = rect.x; x < rect.x + rect.width; x++)
		{
			if (x >= 0 && x < g->win_width && y >= 0 && y < g->win_height)
			{
				pixel = y * g->screen.line_length + x
					* (g->screen.bits_per_pixel / 8);
				*(int *)(g->screen.img_data + pixel) = color;
			}
		}
	}
}

static int	is_in_circle(int x, int y, int center_x, int center_y, int radius)
{
	int	dx;
	int	dy;

	dx = x - center_x;
	dy = y - center_y;
	return (dx * dx + dy * dy <= radius * radius);
}

void	draw_map(t_game *g)
{
	int		x;
	int		y;
	int		tile_size;
	t_point	center;
	t_point	rotated;
	double	angle;
	double	scale;
	int		radius;
	t_rect	wall_rect;
	double	rel_x;
	double	rel_y;

	tile_size = fmin(MINIMAP_WIDTH / g->map.width, MINIMAP_HEIGHT
			/ g->map.height);
	center.x = MINIMAP_WIDTH / 2;
	center.y = MINIMAP_HEIGHT / 2;
	radius = MINIMAP_WIDTH / 2 - 2;
	for (y = 0; y < MINIMAP_HEIGHT; y++)
	{
		for (x = 0; x < MINIMAP_WIDTH; x++)
		{
			if (is_in_circle(x, y, center.x, center.y, radius))
				fill_image_rect(g, 0x202020, (t_rect){x, y, 1, 1});
		}
	}
	angle = atan2(g->player.dir_y, g->player.dir_x);
	scale = 0.8;
	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == '1')
			{
				rel_x = (x - g->player.pos_x) * tile_size;
				rel_y = (y - g->player.pos_y) * tile_size;
				rotated.x = rel_x * cos(-angle) - rel_y * sin(-angle);
				rotated.y = rel_x * sin(-angle) + rel_y * cos(-angle);
				rotated.x = center.x + rotated.x * scale;
				rotated.y = center.y + rotated.y * scale;
				wall_rect.x = rotated.x - (tile_size * scale) / 2;
				wall_rect.y = rotated.y - (tile_size * scale) / 2;
				wall_rect.width = tile_size * scale;
				wall_rect.height = tile_size * scale;
				if (is_in_circle(wall_rect.x + wall_rect.width / 2, wall_rect.y
						+ wall_rect.height / 2, center.x, center.y, radius))
				{
					fill_image_rect(g, 0x505050, wall_rect);
				}
			}
			x++;
		}
		y++;
	}
}

void	draw_line(t_game *g, t_point start, t_point end, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	pixel;
	int	e2;

	dx = abs(end.x - start.x);
	dy = -abs(end.y - start.y);
	sx = start.x < end.x ? 1 : -1;
	sy = start.y < end.y ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (start.x >= 0 && start.x < g->win_width && start.y >= 0
			&& start.y < g->win_height)
		{
			pixel = start.y * g->screen.line_length + start.x
				* (g->screen.bits_per_pixel / 8);
			*(int *)(g->screen.img_data + pixel) = color;
		}
		if (start.x == end.x && start.y == end.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			start.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			start.y += sy;
		}
	}
}

void	draw_player(t_game *g)
{
	t_point	dir_end;
	int		center_x;
	int		center_y;
	int		radius;

	center_x = MINIMAP_WIDTH / 2;
	center_y = MINIMAP_HEIGHT / 2;
	radius = MINIMAP_WIDTH / 2 - 2;
	fill_image_circle(g, 0xFF0000, (t_point){center_x, center_y}, 3);
	dir_end.x = center_x;
	dir_end.y = center_y - 20;
	if (is_in_circle(dir_end.x, dir_end.y, center_x, center_y, radius))
	{
		draw_line(g, (t_point){center_x, center_y}, dir_end, 0x00FF00);
	}
}
