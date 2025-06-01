#include <cub3d.h>

typedef struct s_map_vars
{
	int		tile_size;
	t_point	center;
	double	angle;
	double	scale;
	int		radius;
}	t_map_vars;

static void	draw_minimap_background(t_game *g, t_point center, int radius);

static void	draw_pixel(t_game *g, int px, int py, int color)
{
	int	pixel;

	if (px >= 0 && px < g->win_width && py >= 0 && py < g->win_height)
	{
		pixel = py * g->screen.line_length + px * (g->screen.bits_per_pixel / 8);
		*(int *)(g->screen.img_data + pixel) = color;
	}
}

void	fill_image_circle(t_game *g, int color, t_point center, int radius)
{
	int	px;
	int	py;
	int	y;
	int	x;

	y = -radius;
	while (y <= radius)
	{
		x = -radius;
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
			{
				px = center.x + x;
				py = center.y + y;
				draw_pixel(g, px, py, color);
			}
			x++;
		}
		y++;
	}
}

void	fill_image_rect(t_game *g, int color, t_rect rect)
{
	int	pixel;
	int	y;
	int	x;

	y = rect.y;
	while (y < rect.y + rect.height)
	{
		x = rect.x;
		while (x < rect.x + rect.width)
		{
			if (x >= 0 && x < g->win_width && y >= 0 && y < g->win_height)
			{
				pixel = y * g->screen.line_length + x
					* (g->screen.bits_per_pixel / 8);
				*(int *)(g->screen.img_data + pixel) = color;
			}
			x++;
		}
		y++;
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

static void	init_map_vars(t_game *g, t_map_vars *vars)
{
	vars->tile_size = fmin(MINIMAP_WIDTH / g->map.width, MINIMAP_HEIGHT
			/ g->map.height);
	vars->center.x = MINIMAP_WIDTH / 2;
	vars->center.y = MINIMAP_HEIGHT / 2;
	vars->radius = MINIMAP_WIDTH / 2 - 2;
	vars->angle = atan2(g->player.dir_y, g->player.dir_x);
	vars->scale = 0.8;
}

static void	calculate_wall_coords(t_game *g, t_map_vars *vars, int x, int y,
	t_point *rotated)
{
	double	rel_x;
	double	rel_y;

	rel_x = (x - g->player.pos_x) * vars->tile_size;
	rel_y = (y - g->player.pos_y) * vars->tile_size;
	rotated->x = rel_x * cos(-vars->angle) - rel_y * sin(-vars->angle);
	rotated->y = rel_x * sin(-vars->angle) + rel_y * cos(-vars->angle);
	rotated->x = vars->center.x + rotated->x * vars->scale;
	rotated->y = vars->center.y + rotated->y * vars->scale;
}

static void	draw_wall(t_game *g, t_map_vars *vars, int x, int y)
{
	t_point	rotated;
	t_rect	wall_rect;

	calculate_wall_coords(g, vars, x, y, &rotated);
	wall_rect.x = rotated.x - (vars->tile_size * vars->scale) / 2;
	wall_rect.y = rotated.y - (vars->tile_size * vars->scale) / 2;
	wall_rect.width = vars->tile_size * vars->scale;
	wall_rect.height = vars->tile_size * vars->scale;
	if (is_in_circle(wall_rect.x + wall_rect.width / 2, wall_rect.y
			+ wall_rect.height / 2, vars->center.x, vars->center.y, vars->radius))
	{
		fill_image_rect(g, 0x505050, wall_rect);
	}
}

static void	draw_map_walls(t_game *g, t_map_vars *vars)
{
	int	x;
	int	y;

	y = 0;
	while (y < g->map.height)
	{
		x = 0;
		while (x < g->map.width)
		{
			if (g->map.grid[y][x] == '1')
				draw_wall(g, vars, x, y);
			x++;
		}
		y++;
	}
}

void	draw_map(t_game *g)
{
	t_map_vars	vars;

	init_map_vars(g, &vars);
	draw_minimap_background(g, vars.center, vars.radius);
	draw_map_walls(g, &vars);
}

static void	update_line_coords(t_point *start, int *err, int dx, int dy, int sx, int sy)
{
	int	e2;

	e2 = 2 * *err;
	if (e2 >= dy)
	{
		*err += dy;
		start->x += sx;
	}
	if (e2 <= dx)
	{
		*err += dx;
		start->y += sy;
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
		update_line_coords(&start, &err, dx, dy, sx, sy);
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

static void	draw_minimap_background(t_game *g, t_point center, int radius)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINIMAP_HEIGHT)
	{
		x = 0;
		while (x < MINIMAP_WIDTH)
		{
			if (is_in_circle(x, y, center.x, center.y, radius))
				fill_image_rect(g, 0x202020, (t_rect){x, y, 1, 1});
			x++;
		}
		y++;
	}
}
