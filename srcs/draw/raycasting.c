#include <cub3d.h>

typedef struct s_ray_vars
{
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		tex_num;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		tex_y;
}	t_ray_vars;

typedef struct s_floor_vars
{
	float	ray_dir_x0;
	float	ray_dir_y0;
	float	ray_dir_x1;
	float	ray_dir_y1;
	float	pos_z;
	float	row_distance;
	float	floor_step_x;
	float	floor_step_y;
	float	floor_x;
	float	floor_y;
	int		cell_x;
	int		cell_y;
	int		tx;
	int		ty;
	int		color;
	t_rect	pixel;
}	t_floor_vars;

static void	init_ray_vars(t_game *g, int x, t_ray_vars *vars)
{
	vars->camera_x = 2 * x / (double)g->win_width - 1;
	vars->ray_dir_x = g->player.dir_x + g->player.plane_x * vars->camera_x;
	vars->ray_dir_y = g->player.dir_y + g->player.plane_y * vars->camera_x;
	vars->map_x = (int)g->player.pos_x;
	vars->map_y = (int)g->player.pos_y;
	vars->delta_dist_x = fabs(1 / vars->ray_dir_x);
	vars->delta_dist_y = fabs(1 / vars->ray_dir_y);
	vars->hit = 0;
}

static void	calculate_step_and_side_dist(t_game *g, t_ray_vars *vars)
{
	if (vars->ray_dir_x < 0)
	{
		vars->step_x = -1;
		vars->side_dist_x = (g->player.pos_x - vars->map_x) * vars->delta_dist_x;
	}
	else
	{
		vars->step_x = 1;
		vars->side_dist_x = (vars->map_x + 1.0 - g->player.pos_x) * vars->delta_dist_x;
	}
	if (vars->ray_dir_y < 0)
	{
		vars->step_y = -1;
		vars->side_dist_y = (g->player.pos_y - vars->map_y) * vars->delta_dist_y;
	}
	else
	{
		vars->step_y = 1;
		vars->side_dist_y = (vars->map_y + 1.0 - g->player.pos_y) * vars->delta_dist_y;
	}
}

static void	perform_dda(t_game *g, t_ray_vars *vars)
{
	while (vars->hit == 0)
	{
		if (vars->side_dist_x < vars->side_dist_y)
		{
			vars->side_dist_x += vars->delta_dist_x;
			vars->map_x += vars->step_x;
			vars->side = 0;
		}
		else
		{
			vars->side_dist_y += vars->delta_dist_y;
			vars->map_y += vars->step_y;
			vars->side = 1;
		}
		if (vars->map_y >= 0 && vars->map_y < g->map.height && vars->map_x >= 0
			&& vars->map_x < g->map.width)
		{
			if (g->map.grid[vars->map_y][vars->map_x] == '1')
				vars->hit = 1;
		}
	}
}

static void	calculate_wall_height(t_game *g, t_ray_vars *vars)
{
	if (vars->side == 0)
		vars->perp_wall_dist = (vars->side_dist_x - vars->delta_dist_x);
	else
		vars->perp_wall_dist = (vars->side_dist_y - vars->delta_dist_y);
	vars->line_height = (int)(g->win_height / vars->perp_wall_dist);
	vars->draw_start = -vars->line_height / 2 + g->win_height / 2;
	if (vars->draw_start < 0)
		vars->draw_start = 0;
	vars->draw_end = vars->line_height / 2 + g->win_height / 2;
	if (vars->draw_end >= g->win_height)
		vars->draw_end = g->win_height - 1;
}

static void	calculate_texture_coords(t_game *g, t_ray_vars *vars)
{
	if (vars->side == 0)
		vars->tex_num = vars->ray_dir_x > 0 ? 3 : 2;
	else
		vars->tex_num = vars->ray_dir_y > 0 ? 1 : 0;
	if (vars->side == 0)
		vars->wall_x = g->player.pos_y + vars->perp_wall_dist * vars->ray_dir_y;
	else
		vars->wall_x = g->player.pos_x + vars->perp_wall_dist * vars->ray_dir_x;
	vars->wall_x -= floor(vars->wall_x);
	vars->tex_x = (int)(vars->wall_x * g->textures[vars->tex_num].width);
	if (vars->side == 0 && vars->ray_dir_x > 0)
		vars->tex_x = g->textures[vars->tex_num].width - vars->tex_x - 1;
	if (vars->side == 1 && vars->ray_dir_y < 0)
		vars->tex_x = g->textures[vars->tex_num].width - vars->tex_x - 1;
	vars->step = 1.0 * g->textures[vars->tex_num].height / vars->line_height;
	vars->tex_pos = (vars->draw_start - g->win_height / 2 + vars->line_height / 2) * vars->step;
}

static void	draw_wall_stripe(t_game *g, t_ray_vars *vars, int x)
{
	t_rect	wall_stripe;
	int		color;
	int		y;

	wall_stripe.x = x;
	wall_stripe.width = 1;
	y = vars->draw_start;
	while (y < vars->draw_end)
	{
		vars->tex_y = (int)vars->tex_pos & (g->textures[vars->tex_num].height - 1);
		vars->tex_pos += vars->step;
		color = *(int *)(g->textures[vars->tex_num].img_data + (vars->tex_y
					* g->textures[vars->tex_num].line_length + vars->tex_x
					* (g->textures[vars->tex_num].bits_per_pixel / 8)));
		if (vars->side == 1)
			color = (color >> 1) & 8355711;
		wall_stripe.y = y;
		wall_stripe.height = 1;
		fill_image_rect(g, color, wall_stripe);
		y++;
	}
}

void	cast_ray(t_game *g, int x)
{
	t_ray_vars	vars;

	init_ray_vars(g, x, &vars);
	calculate_step_and_side_dist(g, &vars);
	perform_dda(g, &vars);
	calculate_wall_height(g, &vars);
	calculate_texture_coords(g, &vars);
	draw_wall_stripe(g, &vars, x);
}

static void	init_floor_vars(t_game *g, t_floor_vars *vars)
{
	vars->ray_dir_x0 = g->player.dir_x - g->player.plane_x;
	vars->ray_dir_y0 = g->player.dir_y - g->player.plane_y;
	vars->ray_dir_x1 = g->player.dir_x + g->player.plane_x;
	vars->ray_dir_y1 = g->player.dir_y + g->player.plane_y;
	vars->pos_z = 0.5 * g->win_height;
	vars->pixel.height = 1;
	vars->pixel.width = 1;
}

static void	calculate_floor_steps(t_game *g, t_floor_vars *vars, int y)
{
	int	p;

	p = y - g->win_height / 2;
	vars->row_distance = vars->pos_z / p;
	vars->floor_step_x = vars->row_distance * (vars->ray_dir_x1 - vars->ray_dir_x0) / g->win_width;
	vars->floor_step_y = vars->row_distance * (vars->ray_dir_y1 - vars->ray_dir_y0) / g->win_width;
	vars->floor_x = g->player.pos_x + vars->row_distance * vars->ray_dir_x0;
	vars->floor_y = g->player.pos_y + vars->row_distance * vars->ray_dir_y0;
}

static void	draw_floor_pixel(t_game *g, t_floor_vars *vars, int x, int y)
{
	vars->pixel.x = x;
	vars->pixel.y = y;
	vars->color = *(int *)(g->textures[4].img_data + (vars->ty
				* g->textures[4].line_length + vars->tx
				* (g->textures[4].bits_per_pixel / 8)));
	fill_image_rect(g, vars->color, vars->pixel);
	vars->pixel.y = g->win_height - y - 1;
	vars->color = *(int *)(g->textures[5].img_data + (vars->ty
				* g->textures[5].line_length + vars->tx
				* (g->textures[5].bits_per_pixel / 8)));
	fill_image_rect(g, vars->color, vars->pixel);
}

static void	draw_floor_line(t_game *g, t_floor_vars *vars, int y)
{
	int	x;

	x = 0;
	while (x < g->win_width)
	{
		vars->cell_x = (int)vars->floor_x;
		vars->cell_y = (int)vars->floor_y;
		vars->tx = (int)(g->textures[4].width * (vars->floor_x - vars->cell_x)) 
			& (g->textures[4].width - 1);
		vars->ty = (int)(g->textures[4].height * (vars->floor_y - vars->cell_y)) 
			& (g->textures[4].height - 1);
		vars->floor_x += vars->floor_step_x;
		vars->floor_y += vars->floor_step_y;
		draw_floor_pixel(g, vars, x, y);
		x++;
	}
}

void	draw_floor_ceiling(t_game *g)
{
	t_floor_vars	vars;
	int			y;

	init_floor_vars(g, &vars);
	y = g->win_height / 2;
	while (y < g->win_height)
	{
		calculate_floor_steps(g, &vars, y);
		draw_floor_line(g, &vars, y);
		y++;
	}
}

void	render_3d(t_game *g)
{
	int x;

	if (g->textures[4].img && g->textures[5].img)
		draw_floor_ceiling(g);
	else
	{
		fill_image_rect(g, g->map.ceiling_color, (t_rect){0, 0, g->win_width,
			g->win_height / 2});
		fill_image_rect(g, g->map.floor_color, (t_rect){0, g->win_height / 2,
			g->win_width, g->win_height / 2});
	}
	x = 0;
	while (x < g->win_width)
	{
		cast_ray(g, x);
		x++;
	}
}