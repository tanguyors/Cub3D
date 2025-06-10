#include "../includes/cub3d.h"

typedef struct s_map_vars
{
	int			tile_size;
	t_point		center;
	double		scale;
	int			radius;
}				t_map_vars;

static double	get_rotation_angle(t_game *g)
{
	double	angle;

	angle = atan2(g->player.dir_y, g->player.dir_x);
	if (angle > 3.14159265358979323846)
		angle -= 2 * 3.14159265358979323846;
	else if (angle < -3.14159265358979323846)
		angle += 2 * 3.14159265358979323846;
	return (angle);
}

static void	init_map_vars(t_game *g, t_map_vars *vars)
{
	vars->tile_size = fmin(MINIMAP_WIDTH / g->map.width, MINIMAP_HEIGHT
			/ g->map.height);
	vars->center.x = MINIMAP_WIDTH / 2;
	vars->center.y = MINIMAP_HEIGHT / 2;
	vars->radius = MINIMAP_WIDTH / 2 - 2;
	vars->scale = 0.8;
}

static void	calculate_wall_coords(t_game *g, t_map_vars *vars, int x, int y,
		t_point *rotated)
{
	double	rel_x;
	double	rel_y;
	double	angle;

	rel_x = (x - g->player.pos_x) * vars->tile_size;
	rel_y = (y - g->player.pos_y) * vars->tile_size;
	angle = get_rotation_angle(g);
	rotated->x = rel_x * cos(angle) - rel_y * sin(angle);
	rotated->y = rel_x * sin(angle) + rel_y * cos(angle);
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
			+ wall_rect.height / 2, vars->center.x, vars->center.y,
			vars->radius))
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

void	draw_map(t_game *g)
{
	t_map_vars	vars;

	init_map_vars(g, &vars);
	draw_minimap_background(g, vars.center, vars.radius);
	draw_map_walls(g, &vars);
}
